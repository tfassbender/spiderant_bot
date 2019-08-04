#include <Servo.h>

Servo leg1_turn;
Servo leg1_height;

int leg1_turn_pin = 2;
int leg1_height_pin = 3;

int button_turn = 4;
int button_height = 5;

int leg1_turn_pos = 90;
int leg1_height_pos = 90;

bool leg1_turn_update = true;
bool leg1_height_update = true;

void setup() {
  //set the pin outs
  pinMode(button_turn, INPUT);
  pinMode(button_height, INPUT);
}

void loop() {
  controllButtons();
  moveServos();
}

void controllButtons() {
  //change the position if the button was pressed
  if (digitalRead(button_turn) == HIGH) {
    leg1_turn_pos += 10;
    if (leg1_turn_pos > 135) {
      leg1_turn_pos = 45;
    }
    leg1_turn_update = true;
    delay(50);
  }
  if (digitalRead(button_height) == HIGH) {
    leg1_height_pos += 10;
    if (leg1_height_pos > 135) {
      leg1_height_pos = 75;
    }
    leg1_height_update = true;
    delay(50);
  }
}

void moveServos() {
 //change the position of the servo if it is updated
  if (leg1_turn_update) {
    leg1_turn_update = false;
    leg1_turn.attach(leg1_turn_pin);
    leg1_turn.write(leg1_turn_pos);
    delay(500);
    leg1_turn.detach();//detach the servo if it's not used so it doesn't try to correct the position all the time
  }
  
  if (leg1_height_update) {
    leg1_height_update = false;
    leg1_height.attach(leg1_height_pin);
    leg1_height.write(leg1_height_pos);
    delay(500);
    leg1_height.detach();
  }
}
