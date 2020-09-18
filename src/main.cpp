#include <Arduino.h>
#include "DriveModes.hpp"
#include "Measurements.hpp"
#include "Compass.hpp"

boolean print_state = true;

// Start speed [0;255]
int startSpeed = 255;

// Reaction distance
int stop_dist = 10;
int change_dist = 30;

//int curr_min_dist = 0;
//int curr_min_dir = 0;
int dist[SONAR_NUM] = {
    1, 1
    //, 1
};
boolean state_0 = false;
boolean state_1 = false;
boolean state_2 = false;

float curr_heading = 0;
float tmp_heading = 0;
float heading_tol = 0.03;

String outMsg = "";
String inMsg = ""; // string to hold input

void turnToDegree(float headingTarget, float tol, boolean print_state);

void setup()
{
  Serial.begin(9200); // set up Serial library at 115200 bps
  Serial.print("Start...");
  // initialize motors
  initializeMotor(startSpeed);
  motor1.run(FORWARD);
  delay(100);
  stopMotor();
  Serial.print("...+...");
  motor2.run(FORWARD);
  delay(100);
  stopMotor();
  Serial.print("...+...");
  motor3.run(FORWARD);
  delay(100);
  stopMotor();
  Serial.print("...+...");
  motor4.run(FORWARD);
  delay(100);
  stopMotor();
  Serial.print("...+...");

  Wire.begin();
  // Set operating mode to continuous
  Wire.beginTransmission(Addr);
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Serial.print("...+...");
  Serial.println("->...Init done");
}

void loop()
{
  curr_heading = measure_orientation(false);

  meassureAllDir(dist, orientationSonar, print_state);
  state_0 = dist[0] > change_dist;
  state_1 = dist[1] < stop_dist;
  state_2 = dist[0] < stop_dist;

Serial.print("Start Orientation: ");
Serial.println(curr_heading);

  tmp_heading = curr_heading + 45;
    tmp_heading = (tmp_heading > 360) ? tmp_heading - 360 : tmp_heading;
Serial.print("target Orientation: ");
Serial.println(tmp_heading);

    turnToDegree(tmp_heading, heading_tol, print_state);
  delay(3000);
  /*
  if (state_0 && !state_1 && !state_2) //Obstacle at the left
  {
    driveRight();
    delay(100);
  }
  if (!state_0 && !state_1 && state_2) //Obstacle at the right
  {
    driveLeft();
    delay(100);
  }
  if (state_0 && state_1 && !state_2) //Obstacle at the left and the front
  {
    tmp_heading = curr_heading + 90;
    tmp_heading = (tmp_heading > 360) ? tmp_heading - 360 : tmp_heading;
    turnToDegree(tmp_heading, heading_tol, print_state);
  }
  if (!state_0 && state_1 && state_2) //Obstacle at the right and the front
  {
    tmp_heading = curr_heading - 90;
    tmp_heading = (tmp_heading < 0) ? tmp_heading + 360 : tmp_heading;
    turnToDegree(tmp_heading, heading_tol, print_state);
  }
  if (state_0 && !state_1 && state_2) //Obstacle at the right and the left
  {
    driveForward();
    delay(100);
  }
  if (!state_0 && state_1 && !state_2) //Obstacle at the front
  {
    tmp_heading = curr_heading - 180;
    tmp_heading = (tmp_heading < 0) ? tmp_heading + 360 : tmp_heading;
    turnToDegree(tmp_heading, heading_tol, print_state);
  }
  if (state_0 && state_1 && state_2) //Obstacle at the front, left, right
  {
    driveBackward();
    delay(1000);
    tmp_heading = curr_heading - 180;
    tmp_heading = (tmp_heading < 0) ? tmp_heading + 360 : tmp_heading;
    turnToDegree(tmp_heading, heading_tol, print_state);
  }
  if (!state_0 && !state_1 && !state_2) //no Obstacle
  {
    driveForward();
    delay(100);
  }
  */
}

void turnToDegree(float headingTarget, float tol, boolean print_state)
{
  if (print_state)
    {
      Serial.print("Target Heading: ");
      Serial.println(headingTarget);
    }
  boolean headingReached = false;
  float heading = 0.0;
  float minTarget = 360.0 * (1.0 - tol);
  float breakTarget = 180.0;
  float maxTarget = 360.0 * (tol);
 if (print_state)
    {
      Serial.print("Min Heading: ");
      Serial.println(minTarget);
      Serial.print("Max Heading: ");
      Serial.println(maxTarget);
      Serial.print("Tol: ");
      Serial.println(tol);
    }
    
  while (!headingReached)
  {
    //delay(60);
    heading = measure_orientation(print_state) - headingTarget;
    heading = (heading < 0) ? heading + 360 : heading;
    if (print_state)
    {
      Serial.print("Heading: ");
      Serial.println(heading);
    }

    if (heading < minTarget && heading >= breakTarget)
    {
      if (print_state)
      {
        Serial.println("Turn Left");
      }
      turnLeft();
    }
    else if (heading < breakTarget && heading > maxTarget)
    {
      if (print_state)
      {
        Serial.println("Turn Right");
      }
      turnRight();
    }
    else
    {
      if (print_state)
      {
        Serial.println("Stop");
      }
      headingReached = true;
      stopMotor();
    }
  }
}