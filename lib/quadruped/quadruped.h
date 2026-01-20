#ifndef QUADRUPED_H
#define QUADRUPED_H
#include <ESP32Servo.h>
class Leg
{
private:
    const double Humerus;
    const double Radius;
    double height;
    double hip_angle=180;
    double knee_angle=0;
    double hip_offset=0;
    double knee_offset=0;
    Servo servohip;
    Servo servoknee;
    int hip_Pin;
    int knee_Pin;

public:
    Leg(double Humerus, double Radius,int hip_pin,int knee_pin);
    void set_offset(double hip_offset, double knee_offset);
    void get_angles(double height, double length);
    void move_vertical();
    void move_horizontal(double length);
    void base_height(double Height);
    void move_leg();
};

class Quadruped
{
private:
    Leg &Front_Right;
    Leg &Front_Left;
    Leg &Back_Right;
    Leg &Back_Left;

public:
    Quadruped(Leg &fr, Leg &fl, Leg &br, Leg &bl)
        : Front_Right(fr),
          Front_Left(fl),
          Back_Right(br),
          Back_Left(bl)
    {
    }
    void move_forward();
    void move_backward();
    void sit_down();
    void say_hi();
    void shake_hand();
};
#endif