#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266HTTPClient.h>  // Include the HTTP client library
#include <string.h>
#include <dht.h>
#include <ArduinoJSON.h>

#define SSID "your-ssid"
#define PSWD  "your-password"
#define DEVICE_NAME "devicename"
#define HTTP_PORT 80
#define HOST_ADDR "host-address"

#define TEMP 1 //add additional later
#define H2O 2
#define HUMI 3

#define SENSOR_COUNT 5 //Adjust as nessicary
#define DHT11_1PIN 7    //Add more if needed



typedef enum connectionErrorCode{WifiCode, HostCode}Code;

const char *sensorName[SENSOR_COUNT] = {"Temp1", "Humidity1", "Moisture2in", "Moisture4in", "Moisture6in"}; //Add names of sensors here. Helpful to include depth

const unsigned char sensorType[SENSOR_COUNT] = {TEMP, HUMI, H2O, H2O, H2O}; //Add corresponding sensor types to names

const int capacity = JSON_OBJECT_SIZE(SENSOR_COUNT);


dht DHT;


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

    if (!client.connect(HOST_ADDR,HTTP_PORT)) {
        Serial.println("connection failed");
        return (int)HostCode; //connection to host failed
    }

    //send post request
    HTTPClient http;



    char output[128];
    int httpResponseCode;
    for ( int i = 0; i < SENSOR_COUNT; i++) {
        http.begin(HOST_ADDR);
        http.addHeader("Content-Type", "application/json");
        httpResponseCode = http.PUT(getSensorData(i));
        Serial.println(httpResponseCode);
        Serial.println("\n");
        http.end();
    }




}


float sampleSensor(int sensor) {  //depends on whats connected
    switch(sensor) {
        case TEMP:
            return readTemperature();
            break;
        case H20:
            //use AD thing
            break;
        case HUMI:
            return readHumidity();
            break;
    }
}


char *getSensorData(int index) {
    StaticJsonDocument<capacity> JSONdoc;
    char output[128];

    JSONdoc["device"]=DEVICE_NAME;
    JSONdoc["sensor"]=sensorName[index];
    JSONdoc["value"]=sampleSensor(sensorType[index]);

    serializeJSON(JSONdoc, Serial);
    serializeJSON(JSONdoc,output);

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

    DHT.begin();

    conect();

    ESP.deepSleep(30e6);
}



void loop() {

}
