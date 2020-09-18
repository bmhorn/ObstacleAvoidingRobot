#ifndef COMPASS_HPP
#define COMPASS_HPP

#include <Wire.h>

#define Addr 0x1E // 7-bit address of HMC5883 compass

/*-------------------------------------------------------------------
------------------------Function declaration-------------------------
-------------------------------------------------------------------*/
float measure_orientation(boolean print_state);

/*-------------------------------------------------------------------
------------------------Function definition--------------------------
-------------------------------------------------------------------*/
float measure_orientation(boolean print_state)
{
    int x = 0, y = 0, z = 0; //triple axis data

    // Initiate communications with compass
    Wire.beginTransmission(Addr);
    Wire.write(byte(0x03)); // Send request to X MSB register
    Wire.endTransmission();

    Wire.requestFrom(Addr, 6); // Request 6 bytes; 2 bytes per axis
    while (Wire.available() != 6)
    {
        delay(10);
    }
    if (Wire.available() == 6)
    { // If 6 bytes available
        x = (int)Wire.read() << 8;
        x |= Wire.read();
        z = (int)Wire.read() << 8;
        z |= Wire.read();
        y = (int)Wire.read() << 8;
        y |= Wire.read();
    }

    // If compass module lies flat on the ground with no tilt,
    // just x and y are needed for calculation
    float heading = (atan2(x, y) + PI) * (180 / PI);
    if (heading < 0)
    {
        heading += 360; // N=0/360, E=90, S=180, W=270
    }

    if (print_state)
    {
        Serial.print("Orientation: ");
        Serial.println(heading);
        Serial.print("x: ");
        Serial.print(x);
        Serial.print("    y:  ");
        Serial.print(y);
        Serial.print("    z:  ");
        Serial.println(z);
    }
    return heading;
}

#endif /* COMPASS_HPP */