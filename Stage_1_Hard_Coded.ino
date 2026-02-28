
#include "ADCS.h"
//Definition of ultrasonic pin
#define Trig A4 
#define Echo A5
// Distance threshold for obstacle detection (in cm)
#define DETECTION_DISTANCE 50  // Adjust based on your needs

// Movement parameters
#define MOVE_DURATION 3000  // Time to move sideways (ms)

// Drift correction parameters
#define FORWARD_CORRECTION_START 1500  // When to start correction during forward motion (ms)
#define BACKWARD_CORRECTION_START 1500 // When to start correction during backward motion (ms)

// Motor speed values


// Global variable to track last movement direction
bool lastMovedLeft = false;

void setup() {
  // Initialize ultrasonic sensor pins
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  
  // Initialize motor pins as outputs
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
  // Optional: Initialize serial for debugging
  Serial.begin(9600);
}
bool FOrward = false;
void loop() {
  // Get distance from ultrasonic sensor
  float distance = GetDistance();
  
  // Debug output (optional)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


 if (distance < 75 && distance > 0){
    if (FOrward){
      motor2(180, 0);
      motor1(190, 0);
      delay(100);
      backward();
      FOrward = false;
    }else{
      forward();
      FOrward = true;
    }
 }
  
void forward(){
Serial.println("Moving Forward to evade");
    
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
    motor2(0, 0);
    motor1(0, 0);
}

void backward(){
  Serial.println("Moving Backward to evade");
    
    

    // First half of backward movement
    motor2(160, 0);   // Left motor backward
    motor1(240, 0);   // Right motor forward
    delay(600);
    
    // Second half with drift correction (compensate for left drift)
    motor2(180, 0);   // Increase left motor speed slightly
    motor1(240, 0);   // Keep right motor same
    delay(600);



    motor2(0, 0);
    motor1(0, 0);

}
