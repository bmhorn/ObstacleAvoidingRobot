#ifndef DRIVEMODES_HPP
#define DRIVEMODES_HPP

#include <AFMotor.h>

// DC motor on M1-4
AF_DCMotor motor1(1);//FR
AF_DCMotor motor2(2);//FL
AF_DCMotor motor3(3);//HL
AF_DCMotor motor4(4);//HR

/*-------------------------------------------------------------------
------------------------Function declaration-------------------------
-------------------------------------------------------------------*/
void stopMotor();
void driveForward();
void turnLeft();
void turnRight();
void driveBackward();
void driveLeft();
void driveRight();
void initializeMotor();

/*-------------------------------------------------------------------
------------------------Function definition--------------------------
-------------------------------------------------------------------*/
void stopMotor() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void driveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnLeft() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void turnRight() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void driveBackward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void driveLeft() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void driveRight() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void initializeMotor(int startSpeed) {
  motor1.setSpeed(startSpeed);
  motor2.setSpeed(startSpeed);
  motor3.setSpeed(startSpeed);
  motor4.setSpeed(startSpeed);
}
#endif /* DRIVEMODES_HPP */