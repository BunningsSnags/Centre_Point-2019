#include <arduino.h>
#include <lightSensor.h>
#include <Common.h>

//Light define
int frontValue = 0;
int backValue = 0;

//Read and print the light values
int readLight(){
    frontValue = analogRead(frontLight);
    backValue = analogRead(backLight);
    Serial.println("Light 1: " || backValue || "     Light 2:" || frontValue);
    delay(2000);
}