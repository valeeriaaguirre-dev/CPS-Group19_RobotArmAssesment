/*
  Arduino - 4 Servo Robot Arm Test

  Receives serial commands (1, 2, 3, 4)
  from Processing and moves the servos.

  For use with Processing / Wekinator.
*/

#include <Servo.h>

// Number of servos
const int Num_servo = 4;

// Create four Servo objects
Servo myservo[Num_servo];

// Pins connected to the servo signal wires
int servoPin[Num_servo] = {12, 11, 10, 9};

// Position of each servo
int pos[Num_servo] = {90, 90, 90, 90};

// Incoming command from Processing
int servoCode = -1;


void setup() {

  // Start serial communication with Processing
  Serial.begin(9600);

  // Attach each Servo object to its Arduino pin
  for (int i = 0; i < Num_servo; i++) {

    myservo[i].attach(servoPin[i]);

    // Start each servo at 90 degrees
    myservo[i].write(pos[i]);
  }
}


void loop() {

  // Is Processing sending us something?
  if (Serial.available() > 0) {

    // Read one byte from Processing
    servoCode = Serial.read();

    // Choose a robot-arm position
    switch (servoCode) {

      case 1:
        pos[0] = 30;
        pos[1] = 30;
        pos[2] = 30;
        pos[3] = 30;
        break;

      case 2:
        pos[0] = 60;
        pos[1] = 60;
        pos[2] = 60;
        pos[3] = 60;
        break;

      case 3:
        pos[0] = 90;
        pos[1] = 90;
        pos[2] = 90;
        pos[3] = 90;
        break;

      case 4:
        pos[0] = 120;
        pos[1] = 120;
        pos[2] = 120;
        pos[3] = 120;
        break;

      default:
        // Do nothing if an unexpected command arrives
        break;
    }

    // Send the new positions to all four servos
    for (int i = 0; i < Num_servo; i++) {
      myservo[i].write(pos[i]);
    }

    delay(10);
  }
}
