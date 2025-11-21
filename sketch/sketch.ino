// SPDX-FileCopyrightText: Copyright (C) 2025 ARDUINO SA <http://www.arduino.cc>
//
// SPDX-License-Identifier: MPL-2.0

#include "Arduino_RouterBridge.h"
#include "Servo.h"
#include <Arduino_LED_Matrix.h>


// Define the pin the servo's signal wire is connected to
const int servoPin = 9;
const int idle_position = 90;
const int min_position = 45;
const int max_position = 135;

Arduino_LED_Matrix matrix;

const uint32_t hello_face[]{
  0x000200a8,0x0a802000,0x04403e00,0x00000000
};

const uint32_t idle_face[]{
  0x00000038,0x0e000000,0x00007f00,0x00000000
};


Servo servo;

void setup() {
  matrix.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  servo.attach(servoPin);
  servo.write(idle_position);

  if (!Bridge.begin()) {
    Serial.println("cannot setup Bridge");
  }
  if(!Monitor.begin()){
    Serial.println("cannot setup Monitor");
  }
  Bridge.provide("greet", greet);
  matrix.loadFrame(idle_face);
}

void loop() {
}

void greet() {
    Monitor.print("I should be greeting someone");
    digitalWrite(LED_BUILTIN, HIGH);
    matrix.loadFrame(hello_face);

    // Sweep  3 times
    for (int i = 0; i < 3; i++) {
      for (int j=idle_position; j<max_position; j++){
        servo.write(j);
        delay(5);
      }
      for (int j=max_position; j>min_position; j--){
        servo.write(j);
        delay(5);
      }
      for (int j=min_position; j<idle_position; j++){
        servo.write(j);
        delay(5);
      }
    }
    digitalWrite(LED_BUILTIN, LOW);
    matrix.loadFrame(idle_face);
}
