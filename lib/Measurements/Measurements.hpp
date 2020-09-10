#ifndef MEASUREMENTS_HPP
#define MEASUREMENTS_HPP

#include <NewPing.h>

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

// Ultrasonic sensor
// L F R
NewPing sonar[SONAR_NUM] = {
  NewPing(A0, A0, MAX_DISTANCE),
  NewPing(A1, A1, MAX_DISTANCE),
  NewPing(A2, A2, MAX_DISTANCE)
};
const char *orientationSonar[SONAR_NUM] = {"Left","Front","Right"};

/*-------------------------------------------------------------------
------------------------Function declaration-------------------------
-------------------------------------------------------------------*/
void meassureAllDir(int distance[SONAR_NUM], const char *orientation[SONAR_NUM], boolean print_state);
void minElement(int array[], byte size,int& minValue,int& minIndex);

/*-------------------------------------------------------------------
------------------------Function definition--------------------------
-------------------------------------------------------------------*/
void meassureAllDir(int distance[SONAR_NUM], const char *orientation[SONAR_NUM], boolean print_state) {
    for (byte i = 0; i < SONAR_NUM; i++) {
        distance[i] = sonar[i].ping_cm();
        delay(50);
        if (distance[i]==0){
            distance[i]=MAX_SENSOR_DISTANCE;
        }
        if (print_state) {
            Serial.print(String("Distance at the ")+String(orientation[i]));
            Serial.println(String(": ")+distance[i]+String("cm"));
        }
    }
    delay(100);
}

void minElement(int array[], byte size,int& minValue,int& minIndex) {
    minValue = array[0];
    minIndex = 0;
    for (byte i = 0; i < size; i++) {
        if(array[i] < minValue) {
            minValue = array[i];
            minIndex = (int) i;
        }
    }
}

#endif /* MEASUREMENTS_HPP */