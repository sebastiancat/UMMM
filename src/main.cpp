/*
Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/

#include <Arduino.h>
#include "servo/Servo.h"

void slowdown(int start, int end, int time, Servo servo);


Servo ESC;     // create servo object to control the ESC
int note;
int potValue;  // value from the analog pin
unsigned long startTime;
char key;

void setup() {
    Serial.begin(9600);
    // Attach the ESC on pin 9
    ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds)
    while (true) {
        if (Serial.available() > 0) {
            if(Serial.read() == ' ') {
                startTime = micros();
                Serial.println("Motor Starting...");
                Serial.println("Beginning Calibration:");
                {// Send Z, wait a bit, send A
                }
                break;
            }
        }
    }


}

void loop() {
    key = 0;
    if (Serial.available() > 0) {
        key = Serial.read();
    }
    if (key == '1') {
        note = 0;
    } else if (key == '0') {
        note = 180;
    } else if (key == '2' && note > 0) {
        note--;
    } else if (key == '9' && note < 180) {
        note++;
    }
    if(note <= 180 && note >= 0) {
        ESC.write(note);    // Send the signal to the ESC
        Serial.println(note);
    }
}