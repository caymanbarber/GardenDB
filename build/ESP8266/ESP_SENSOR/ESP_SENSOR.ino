#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266HTTPClient.h>  // Include the HTTP client library
#include <string.h>
#include "DHT.h"
#include <ArduinoJson.h>

#define SSID "wifi name"
#define PSWD "wifi password"
#define DEVICE_NAME "esp1"
#define HTTP_PORT 8000
#define HOST_IP "hostIP"
#define HTTP_ADDR "http://hostIP:8000"

#define TEMP 1 //add additional when using more sensors
#define H2O 2
#define HUMI 3

#define SENSOR_COUNT 5 //Adjust as nessicary
#define DHT11_1PIN 7    //Add more if needed

//DHT dht(DHT11_1PIN, DHT11);   //initializes

typedef enum connectionErrorCode{WifiCode, HostCode}Code;   //add more for error handling
const char *sensorName[SENSOR_COUNT] = {"Temp1", "Humidity1", "Moisture2in", "Moisture4in", "Moisture6in"}; //Add names of sensors here. Helpful to include depth
const unsigned char sensorType[SENSOR_COUNT] = {TEMP, HUMI, H2O, H2O, H2O}; //Add corresponding sensor types to names
const int capacity = JSON_OBJECT_SIZE(SENSOR_COUNT);


int connect() {
    //connect to local wifi network

    Serial.println("\nConnecting to: ");
    Serial.println(SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PSWD);

    unsigned long wifiConnectStart = millis();

    while (WiFi.status() != WL_CONNECTED) {
        if (WiFi.status() == WL_CONNECT_FAILED) {
            Serial.println("Failed to connect to WiFi. Please verify credentials: ");
            delay(10000);
        }

        delay(500);
        Serial.println("...");
        // Only try for 5 seconds.
        if (millis() - wifiConnectStart > 15000) {
            Serial.println("Failed to connect to WiFi");
            return (int)WifiCode; //connection to network failed
        }
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    //connect to host through http port

    WiFiClient client;

    if (!client.connect(HOST_IP,HTTP_PORT)) {
        Serial.println("connection failed");
        return (int)HostCode; //connection to host failed
    }

    //send post request
    HTTPClient http;

    int httpResponseCode;

    for ( int i = 0; i < SENSOR_COUNT; i++) {
        http.begin(HTTP_ADDR);  //create http post request
        http.addHeader("Content-Type", "application/json"); //add additional headers
        httpResponseCode = http.POST(getSensorData(i));

        Serial.println("Response Code: ");
        Serial.println(httpResponseCode);
        http.end();
    }
}


float sampleSensor(int sensor) {  //depends on whats connected
    switch(sensor) {    //add when
        case TEMP:
            return (float)70.2; //for testing
            //return readTemperature();
            break;
        case H2O:
            return (float)15.7; //for testing
            //use AD thing
            break;
        case HUMI:
            return (float)12.4; //for testing
            //return readHumidity();
            break;
    }
}


String getSensorData(int index) {
    StaticJsonDocument<capacity> JSONdoc;
    String output;

    JSONdoc["device"]=String(DEVICE_NAME);
    JSONdoc["sensor"]=String(sensorName[index]);
    JSONdoc["value"]=String(sampleSensor(sensorType[index]));

    serializeJson(JSONdoc, Serial);
    Serial.println("");
    serializeJson(JSONdoc,output);

    return output;
}


void setup() {
    Serial.begin(115200);
    Serial.setTimeout(2000);

    // Wait for serial to initialize.
    while (!Serial) { }

    Serial.println("Device Started");
    Serial.println("-------------------------------------");
    Serial.println("Running Sensor Firmware!");
    Serial.println("-------------------------------------");

    //DHT.begin();

    connect();

    Serial.println("gong to sleep\n");
    ESP.deepSleep(30e6); //30 sec, change to 10 mins or hour
    Serial.println("slept\n");
}



void loop() {}
