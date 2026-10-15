#include <Servo.h>

#define NUM_JOINTS 4

Servo myservo[NUM_JOINTS];
const int servoPins[NUM_JOINTS] = { 12, 11, 10, 9 };
const int potPins[NUM_JOINTS]   = { A0, A1, A2, A3 };
int val[NUM_JOINTS];

void setup() {
  for (int i = 0; i < NUM_JOINTS; i++) {
    myservo[i].attach(servoPins[i]);
  }
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < NUM_JOINTS; i++) {
    val[i] = analogRead(potPins[i]);
    val[i] = map(val[i], 0, 1023, 0, 150);
    myservo[i].write(val[i]);
    // serial.print(val[i]);
    // serial.print(, );
    
  }
  delay(15);
}