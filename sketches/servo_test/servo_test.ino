#include <Servo.h>

Servo servo;

int servoPin = 2;
int buttonPin = 3;

int led = 13;

int pos = 0;
bool changePos = true;

void setup() {
  //set the pin outs
  pinMode(buttonPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  //change the position if the button was pressed
  if (digitalRead(buttonPin) == HIGH) {
    pos += 45;
    if (pos > 180) {
      pos = 0;
    }
    changePos = true;
    delay(100);
  }
  
  //change the position of the servo if it is updated
  if (changePos) {
    changePos = false;
    servo.attach(servoPin);
    servo.write(pos);
    delay(1000);
    servo.detach();//detach the servo if it's not used so it doesn't try to correct the position all the time
  }
  
  //test whether the update flag is on (should not be on)
  /*if (changePos) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }*/
}
