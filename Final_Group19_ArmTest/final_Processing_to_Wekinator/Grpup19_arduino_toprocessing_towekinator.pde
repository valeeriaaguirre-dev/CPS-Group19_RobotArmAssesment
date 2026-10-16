
/*
  processing_osc_to_arduino_4_servos

  Receives OSC messages from Wekinator
  and sends serial commands to Arduino.

  Wekinator classifier: 4 classes

  Class 1 -> Servo 1
  Class 2 -> Servo 2
  Class 3 -> Servo 3
  Class 4 -> Servo 4

  Based on Becky Stewart's original code (2022).
  Modified for four servos.
*/

import oscP5.*;
import netP5.*;
import processing.serial.*;

// OSC communication
OscP5 oscP5;

// Serial communication with Arduino
Serial port;

// Remember the last command sent
int arduinoMessage = -1;


void setup() {

  size(256, 150);

  // Display available serial ports
  println("Available serial ports:");
  printArray(Serial.list());

  // Connect to Arduino
  // Change [2] to match your Arduino's port
  port = new Serial(this, Serial.list()[2], 9600);

  // Listen for OSC messages from Wekinator
  oscP5 = new OscP5(this, 12000);

}


void draw() {

  // Draw the original grey gradient
  for (int i = 0; i < 256; i++) {
    stroke(i);
    line(i, 0, i, 150);
  }

  // OPTIONAL DEBUGGING:
  // Uncomment these lines to test Arduino
  // using the mouse instead of Wekinator.

  // int mouseMessage = (int)map(mouseX, 0, 256, 1, 5);
  // mouseMessage = constrain(mouseMessage, 1, 4);
  // updateArduino(mouseMessage);

}


// Called when an OSC message arrives
void oscEvent(OscMessage theOscMessage) {

  // Check that the message comes from
  // Wekinator's output address
  if (theOscMessage.checkAddrPattern("/wek/outputs")) {

    // Check that the message contains a float
    if (theOscMessage.checkTypetag("f")) {

      // Read the classification value
      float firstValue = theOscMessage.get(0).floatValue();

      println("Wekinator class: " + firstValue);

      // Convert float to integer
      int servoCommand = (int)firstValue;

      // Accept only classes 1 to 4
      if (servoCommand >= 1 && servoCommand <= 4) {

        // Send class number to Arduino
        updateArduino(servoCommand);

      } else {

        println("Invalid class: " + servoCommand);

      }

      return;
    }
  }

  println("Unexpected OSC message: "
    + theOscMessage.addrPattern());
}


// Send a new command to Arduino
void updateArduino(int newMessage) {

  // Only send if command has changed
  if (newMessage != arduinoMessage) {

    // Remember latest command
    arduinoMessage = newMessage;

    // Print command for debugging
    println("Sending to Arduino: " + arduinoMessage);

    // Send numeric byte over USB serial
    port.write(arduinoMessage);

  }
}
