#include <Servo.h>

Servo servo;

int servoPin = 2;
int buttonPin = 3;

int pos = 0;
bool changePos = true;

void setup() {
  pinMode(buttonPin, INPUT);
  servo.attach(servoPin);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    pos += 45;
    if (pos > 180) {
      pos = 0;
    }
    changePos = true;
    delay(100);
  }

  if (changePos) {
    servo.write(pos);
    delay(1000);
  }
}
