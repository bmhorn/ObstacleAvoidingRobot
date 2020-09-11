#include <Arduino.h>
#include "DriveModes.hpp"
#include "Measurements.hpp"

// Start speed [0;255]
int startSpeed = 255;

// Reaction distance
int stop_dist = 10;
int change_dist = 30;

//int curr_min_dist = 0;
//int curr_min_dir = 0;
int dist[SONAR_NUM] = {1, 1, 1};
boolean state_0 = false;
boolean state_1 = false;
boolean state_2 = false;

int random_num = rand() % 2;

String outMsg = "";
String inMsg = ""; // string to hold input

void setup()
{
  Serial.begin(115200); // set up Serial library at 115200 bps
  // initialize motors
  initializeMotor(startSpeed);
  motor1.run(FORWARD);
  delay(1000);
  motor2.run(FORWARD);
  delay(1000);
  motor3.run(FORWARD);
  delay(1000);
  motor4.run(FORWARD);
  delay(1000);
  stopMotor();
}

void loop()
{
  meassureAllDir(dist, orientationSonar, true);
  Serial.println(outMsg);
  state_0 = dist[0]<change_dist;
  state_1 = dist[1]<stop_dist;
  state_2 = dist[2]<change_dist;
  
  if(state_0 && !state_1 && !state_2)//Obstacle at the left
  {
    driveRight();delay(100);
  }
if(!state_0 && !state_1 && state_2)//Obstacle at the right
  {
    driveLeft();delay(100);
  }
if(state_0 && state_1 && !state_2)//Obstacle at the left and the front
  {
    turnRight();delay(100);
  }
if(!state_0 && state_1 && state_2)//Obstacle at the right and the front
  {
    turnLeft();delay(100);
  }
if(state_0 && !state_1 && state_2)//Obstacle at the right and the left
  {
    driveForward();delay(100);
  }
if(!state_0 && state_1 && !state_2)//Obstacle at the front
  {
    if(random_num){turnRight();}else{turnLeft();}delay(100);
  }
if(state_0 && state_1 && state_2)//Obstacle at the front, left, right
  {
    driveBackward();delay(1000);
    if(random_num){turnRight();}else{turnLeft();}delay(2000);
  }
if(!state_0 && !state_1 && !state_2)//no Obstacle
  {
    driveForward();delay(100);
    random_num = rand() % 2;
  }

}