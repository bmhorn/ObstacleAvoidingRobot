#include <Arduino.h>
#include "DriveModes.hpp"
#include "Measurements.hpp"

// Start speed [0;255]
int startSpeed = 255;

// Reaction distance
int stop_dist = 10;
int change_dist = 20;

int curr_min_dist = 0;
int curr_min_dir = 0;
int dist0[SONAR_NUM] = {1, 1, 1};

int random_num = rand() % 2 + 1;

int c = 0;
String msg = "";
String inString = ""; // string to hold input

void setup()
{
  Serial.begin(115200); // set up Serial library at 115200 bps
  // initialize motors
  initializeMotor(startSpeed);
  stopMotor();
}

void loop()
{
  meassureAllDir(dist0, orientationSonar, true);
  minElement(dist0, SONAR_NUM, curr_min_dist, curr_min_dir);
  msg = String("Obstacle ahead in ") + curr_min_dist + String(" cm.");
  Serial.println(msg);
}