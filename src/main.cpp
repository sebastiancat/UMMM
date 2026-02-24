/*
Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/

#include <Arduino.h>
#include "servo/Servo.h"

void slowdown(int start, int end, int time);
int getNote(char ch);

int A = 60;
int Ap = 63;
int B = 66;
int C = 71;
int Cp = 75;
int D = 78;
int Dp = 83;
int E = 87;
int F = 91;
int Fp = 96;
int G = 99;
int Gp = 101;


int timeFromLastNote = 0;
int keyNote;



Servo ESC;     // create servo object to control the ESC
int note;
int potValue;  // value from the analog pin
unsigned long startTime;
char key;

void setup() {
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);

    int maxVal = 1023;
    analogWrite(A0, 0);
    analogWrite(A1, (maxVal/5) * 1);
    analogWrite(A2, (maxVal/5) * 2);
    analogWrite(A3, (maxVal/5) * 3);
    analogWrite(A4, (maxVal/5) * 4);
    analogWrite(A5, (maxVal/5) * 5);





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
    timeFromLastNote++;

    if (Serial.available() > 0) {
        key = Serial.read();
    }

    keyNote = getNote(key);
    if (keyNote) {
        note = keyNote;
        timeFromLastNote = 0;
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


int getNote(char ch) {
    switch (ch) {
        case 'a': return A;
        case 's': return B;
        case 'd': return C;
        case 'f': return D;
        case 'g': return E;
        case 'h': return F;
        case 'j': return G;
        case 'q': return Ap;
        case 'e': return Cp;
        case 'r': return Dp;
        case 'y': return Fp;
        case 'u': return Gp;
        default: return NULL;
    }
}
