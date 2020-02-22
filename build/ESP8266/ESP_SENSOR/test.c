#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TESTSTR "teststr"
const char *sensorName[4] = {"Temp1", "Moisture2in", "Moisture4in", "Moisture6in"};

char *testmethod() {
	char output[128];
	strcpy(output,"hello");
	return output;
}

int main() {
	// char str[64];
	// float f1 = 123.456789;
	// float f2 = -23.456789;
	// snprintf(str, sizeof(str), "{\"SomeField\":\"%.2f\", \"SomeOther\":\"%.3f\"}", f1, f2);
	//
	// "{\"device\": \"esp32\", \"sensor\": \"temperature2\" ,\"value\": 70}""



	printf("%s\n",testmethod());
	return 0;
}
