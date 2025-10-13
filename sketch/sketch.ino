// SPDX-FileCopyrightText: Copyright (C) 2025 ARDUINO SA <http://www.arduino.cc>
//
// SPDX-License-Identifier: MPL-2.0

#include "Arduino_RouterBridge.h"

// Define the pin the servo's signal wire is connected to
const int servoPin = 9;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(servoPin, OUTPUT);

  if (!Bridge.begin()) {
    Serial.println("cannot setup Bridge");
  }
  if(!Monitor.begin()){
    Serial.println("cannot setup Monitor");
  }
  Bridge.provide("greet", greet);
}

void loop() {
}

void greet() {
    Monitor.print("I should be greeting someone");
    digitalWrite(LED_BUILTIN, HIGH);
  
    // Sweep from 0 to 180 degrees 3 times
    for (int i = 0; i < 3; i++) {
      setServoAngle(0);
      delay(200); 
      setServoAngle(180);
      delay(200);
    }

    digitalWrite(LED_BUILTIN, LOW);
}


// This function sends the correct pulse to the servo to set its angle
void setServoAngle(int angle) {
  // Map the angle (0-180) to The required pulse width in microseconds (1000-1800)
  int pulseWidth = map(angle, 0, 180, 1000, 1800);

  // Send the pulse
  digitalWrite(servoPin, HIGH);        // Set the signal pin high
  delayMicroseconds(pulseWidth);      // Wait for the pulse duration
  digitalWrite(servoPin, LOW);         // Set the signal pin low

  // Wait for the rest of the 20ms cycle to complete
  delayMicroseconds(20000 - pulseWidth);
}
