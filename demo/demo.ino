#include "ADCS.h"

//Data variable definition
int MotSpeed1 = 200; 
int MotSpeed2 = 200;
int Speed_adjustment = 120;
int stop_bit = 0;
float distance = 0.0;
int set_dis = 30;

//Program initialization
void setup()  
{
    Serial.begin(9600); 

    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    pinMode(Trig,OUTPUT);   
    pinMode(Echo,INPUT); 
    // Define ultrasonic sensor pins
}

//Principal function
void loop()
{
  int distance;
  distance = GetDistance(); 
  Serial.println(distance);  //Print distance in serial port
  
  if(distance < 30)     //Judge that the distance is less than 30cm and start to decelerate
  {
      Speed_adjustment--;
      delay(5);     //Car deceleration speed
      if(Speed_adjustment<=120) Speed_adjustment=120;
      MotSpeed1 = Speed_adjustment+20;
      MotSpeed2 = Speed_adjustment;
  }

  if(distance > 30)  //Judge if the distance is more than 30cm and start to accelerate
  {
      Speed_adjustment++;
      delay(5);
      if(Speed_adjustment>=235)Speed_adjustment=235;
      MotSpeed1 = Speed_adjustment+20;
      MotSpeed2 = Speed_adjustment;
  }
     
  if(distance < set_dis)  //Judge that the car is less than the obstacle avoidance distance
  {
      delay(10);
      distance = GetDistance(); 
      if(distance < set_dis)
      {
          if(stop_bit==0)
          {
              //stop
              motor1(0,0);
              motor2(0,0);
              delay(300);
              stop_bit=1;
          }
          //Car back (REVERSED - now goes backward)
          motor1(140, 0);  // FLIPPED: was (0,140)
          motor2(140, 0);  // FLIPPED: was (0,140)
          delay(600);
          //The car turns left (REVERSED)
          motor1(140, 0);  // FLIPPED: was (0,140)
          motor2(0, 140);  // FLIPPED: was (140,0)
          delay(200);          
          Speed_adjustment=120;
      }
  }
  else
  {
      //Move forward (REVERSED - now goes forward)
      motor1(0, MotSpeed1);  // FLIPPED: was (MotSpeed1,0)
      motor2(0, MotSpeed2);  // FLIPPED: was (MotSpeed2,0)
      stop_bit=0;
  }
}