#include "ADCS.h"

float leftScale = 0.70;
int   turnSpeed = 120;

int   baseSpeed    = 180;
int   obstacleStop = 20;

void stopMotors() {
  motor1(0, 0);
  motor2(0, 0);
}

int getDistance() {
  return GetDistance();
}

// Rotate left until sensor reads ABOVE threshold, then rotate left 0.5s more
void leftSweep(int sweepThreshold) { // counterclockwise
  // Rotate left while checking distance
  motor2(turnSpeed, 0);     // left backward
  motor1(0, turnSpeed);     // right forward

  while (true) {
    int d = getDistance();
    Serial.print(F("L_SWEEP d=")); Serial.println(d);
    if (d > sweepThreshold) {
      break;
    }
    delay(30);
  }

  // Continue rotating left for 0.5s more
  delay(50);
  stopMotors();
}

// Rotate right until sensor reads ABOVE threshold, then rotate right 0.5s more
void rightSweep(int sweepThreshold) { // clockwise
  // Rotate right while checking distance
  motor2(0, turnSpeed);     // left forward
  motor1(turnSpeed, 0);     // right backward

  while (true) {
    int d = getDistance();
    Serial.print(F("R_SWEEP d=")); Serial.println(d);
    if (d > sweepThreshold) {
      break;
    }
    delay(30);
  }

  // Continue rotating right for 0.5s more
  delay(50);
  stopMotors();
}

// void driveForward(int speed) {
//   motor2(0, (int)(speed * leftScale));
//   motor1(0, speed);
// }

void driveForward(int speed){
  // Serial.println("Moving Forward to evade");
    
  // First half of forward movement
  motor2(0, 180);    // Left motor forward
  motor1(0, 240);    // Right motor backward
  delay(800);
  for (int i = 0; i < 8 ; i ++){
    motor2(0, 140);
    motor1(0, 240);
    delay(65);
    motor2(0, 160);
    motor1(0, 220);
    delay(35);
  }
}

int getStableDistance() {
  int r[3];
  for (int i = 0; i < 3; i++) {
    r[i] = GetDistance();
    delay(10);
  }
  if (r[0] > r[1]) { int t = r[0]; r[0] = r[1]; r[1] = t; }
  if (r[1] > r[2]) { int t = r[1]; r[1] = r[2]; r[2] = t; }
  if (r[0] > r[1]) { int t = r[0]; r[0] = r[1]; r[1] = t; }
  return r[1];
}

void driveUntilWall() {
  // driveForward(baseSpeed);
  while (true) {
    driveForward(baseSpeed);

    int d = getStableDistance();
    if (d > 0 && d <= obstacleStop) {
      stopMotors();
      delay(200);
      return;
    }
    delay(50);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  delay(1500);

  // Test: uncomment whichever you want to try
  // leftSweep();
  // rightSweep();

  rightSweep(50);
  driveUntilWall();
  leftSweep(100);
  driveUntilWall();
}

void loop() {

}