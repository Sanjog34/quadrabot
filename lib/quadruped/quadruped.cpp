#include <Arduino.h>
#include <ESP32Servo.h>
#include <math.h>
#include <quadruped.h>

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINT(x)
#endif

Leg ::Leg(double humerus, double radius, int hip_pin, int knee_pin)
    : Humerus(humerus),
      Radius(radius),
      hip_Pin(hip_pin),
      knee_Pin(knee_pin)
{
    servohip.attach(hip_Pin);
    servoknee.attach(knee_Pin);
}

void Leg ::set_offset(double hip_offset, double knee_offset)
{
    this->hip_offset = hip_offset;
    this->knee_offset = knee_offset;
}

void Leg::get_angles(double height, double length)
{
    double d = sqrt(length * length + height * height);

    double hip_arg = (Humerus * Humerus + d * d - Radius * Radius) / (2 * Humerus * d);
    hip_arg = constrain(hip_arg, -1, 1);

    double knee_arg = (Humerus * Humerus - d * d + Radius * Radius) / (2 * Humerus * Radius);
    knee_arg = constrain(knee_arg, -1, 1);

    hip_angle = int(90 - (180.0 / M_PI) * (atan2(length, height) + acos(hip_arg) - (hip_offset * M_PI / 180.0)));
    int knee_deg = int((180.0 / M_PI) * acos(knee_arg));
    knee_angle = map(knee_deg, 0, 180, 180, 0);

    hip_angle = constrain(hip_angle, 0, 180);
    knee_angle = constrain(knee_angle, 0, 180);
}

void Leg ::move_vertical()
{
    DEBUG_PRINT("hip angle     knee angle      height from ground\n");
    for (float i = height; i >= 0; i = i - 0.1)
    {
        get_angles(i, 0);
        DEBUG_PRINT(hip_angle);
        DEBUG_PRINT("    ");
        DEBUG_PRINT(knee_angle);
        DEBUG_PRINT("    ");
        DEBUG_PRINT(i);
        DEBUG_PRINT("\n");
        move_leg();
    }
    for (float i = 0; i <= height; i = i + 0.1)
    {
        get_angles(i, 0);
        DEBUG_PRINT(hip_angle);
        DEBUG_PRINT("    ");
        DEBUG_PRINT(knee_angle);
        DEBUG_PRINT("    ");
        DEBUG_PRINT(i);
        DEBUG_PRINT("\n");
        move_leg();
    }
}

void Leg ::move_horizontal(double length)
{
    DEBUG_PRINT("hip angle     knee angle      length      height from ground\n");
    for (float i = 0; i <= length; i = i + 0.1)
    {
        get_angles(height, i);
        DEBUG_PRINT(hip_angle);
        DEBUG_PRINT("    ");
        DEBUG_PRINT(knee_angle);
        DEBUG_PRINT("    ");
        DEBUG_PRINT(i);
        DEBUG_PRINT("    ");
        DEBUG_PRINT(height);
        DEBUG_PRINT("\n");
        move_leg();
    }
    for (float i = length; i >= 0; i = i - 0.1)
    {
        get_angles(height, i);
        DEBUG_PRINT(hip_angle);
        DEBUG_PRINT("    ");
        DEBUG_PRINT(knee_angle);
        DEBUG_PRINT("    ");
        DEBUG_PRINT(i);
        DEBUG_PRINT("    ");
        DEBUG_PRINT(height);
        DEBUG_PRINT("\n");
        move_leg();
    }
}

void Leg ::base_height(double Height)
{
    height = Height;
    get_angles(height, 0);
    servohip.write(hip_angle);
    servoknee.write(knee_angle);
}

void Leg ::move_leg()
{
    servohip.write(hip_angle);
    servoknee.write(knee_angle);
    delay(10);
}
