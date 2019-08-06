#include <Servo.h>

//number of legs
const int legs = 6;

//the servos for turning (front or back) and moving (up or down)
Servo servoTurn[legs];
Servo servoHeight[legs];

//the pins used for the turn or height servos
const int turnServoPin[legs] = {2, 4, 6, 8, 10, 12};
const int heightServoPin[legs] = {3, 5, 7, 9, 11, 13};

//the initial servo positions
const int turnInitialPos = 90;
const int heightInitialPos = 90;

//the turn differences for moving the servos to front, back, up or down
const int turnDiffFront = -30;
const int turnDiffBack = 30;
const int heightDiffUp = 20;
const int heightDiffDown = -20;

//the position factors (invert the values because of the mirrored leg positions)
const int positionFactors[legs] = {1, -1, 1, -1, 1, -1};

void setup() {
  delay(5000);//wait before starting
}

void loop() {
  int steps = 5;
  startingPosition();
  for (int i = 0; i < steps; i++) {
    stepForward();
  }
}

/**
 * Move all legs to the starting position
 */
void startingPosition() {
  const int movingTime = 1000;
  for (int i = 0; i < legs; i++) {
    turnLegToPos(i+1, turnInitialPos);
    moveLegDown(i+1);
  }
  delay(movingTime);
}

/**
 * Make one step forward
 */
void stepForward() {
  const int moveTime = 500;
  const int turnTime = 500;

  const int legsPerSet = 3;
  const int legsSet1[] = {2, 3, 6};
  const int legsSet2[] = {1, 4, 5};
  
  //move up the first set of legs
  for (int i = 0; i < legsPerSet; i++) {
    moveLegUp(legsSet1[i]);
  }
  delay(moveTime);//give the legs some time to move

  //move the legs to the front or back
  for (int i = 0; i < legsPerSet; i++) {
    turnLegToFront(legsSet1[i]);
    turnLegToBack(legsSet2[i]);
  }
  delay(turnTime);//give the legs some time to move

  //move down the first set of legs
  for (int i = 0; i < legsPerSet; i++) {
    moveLegDown(legsSet1[i]);
  }
  delay(moveTime);//give the legs some time to move

  //move up the second set of legs
  for (int i = 0; i < legsPerSet; i++) {
    moveLegUp(legsSet2[i]);
  }
  delay(moveTime);//give the legs some time to move
  
  //move the legs to the front or back
  for (int i = 0; i < legsPerSet; i++) {
    turnLegToFront(legsSet2[i]);
    turnLegToBack(legsSet1[i]);
  }
  delay(turnTime);//give the legs some time to move

  //move down the first set of legs
  for (int i = 0; i < legsPerSet; i++) {
    moveLegDown(legsSet2[i]);
  }
  delay(moveTime);//give the legs some time to move
}

/**
 * Moves a leg up (leg count from 1 to 6)
 */
void moveLegDown(int leg) {
  int height = heightInitialPos;
  height += heightDiffDown * positionFactors[leg-1];
  moveLegToPos(leg, height);
}
/**
 * Moves a leg down (leg count from 1 to 6)
 */
void moveLegUp(int leg) {
  int height = heightInitialPos;
  height += heightDiffUp * positionFactors[leg-1];
  moveLegToPos(leg, height);
}

/**
 * Turns a leg to the front position (leg count from 1 to 6)
 */
void turnLegToFront(int leg) {
  int turn = turnInitialPos;
  turn += turnDiffFront * positionFactors[leg-1];
  turnLegToPos(leg, turn);
}
/**
 * Turns a leg to the back position (leg count from 1 to 6)
 */
void turnLegToBack(int leg) {
  int turn = turnInitialPos;
  turn += turnDiffBack * positionFactors[leg-1];
  turnLegToPos(leg, turn);
}

/**
 * Turns a leg to a position (front or back).
 * After the move command is send the leg is detached to not move anymore (or try to keep position).
 * 
 * After the move there is no delay, so the move still needs some time.
 */
void turnLegToPos(int leg, int turn) {
  servoTurn[leg-1].attach(turnServoPin[leg-1]);
  servoTurn[leg-1].write(turn);
  servoTurn[leg-1].detach();
}
/**
 * Moves a leg to a position (up or down).
 * After the move command is send the leg is detached to not move anymore (or try to keep position).
 * 
 * After the move there is no delay, so the move still needs some time.
 */
void moveLegToPos(int leg, int height) {
  servoHeight[leg-1].attach(heightServoPin[leg-1]);
  servoHeight[leg-1].write(height);
  servoHeight[leg-1].detach();
}
