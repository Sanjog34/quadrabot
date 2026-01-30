#include "quadruped.h"

#include "quadruped.h"
Leg back_left(8, 10.25, 14, 13, left);
Leg back_right(8, 10.25, 19, 18, right);
Leg front_left(8, 10.25, 27, 26, left);
Leg front_right(8, 10.25, 23, 21, right);

Quadruped quadruped(front_right, front_left, back_right, back_left);
void setup()
{

    Serial.begin(115200);
    quadruped.init(15, 7);
    quadruped.moveTo_base_pos();
    delay(1000);
    back_left.moveTo_base_pos();
    delay(1000);
    back_right.moveTo_base_pos();
    delay(1000);
    front_right.moveTo_base_pos();
    delay(1000);
    front_left.moveTo_base_pos();
    delay(1000);
    quadruped.moveTo_base_pos();
}
void loop()
{
    while (1)
    {
        if (Serial.available())
        {
            char c = Serial.read();
            if (c == 'a')
            {
                back_left.crawl_forward();
            }
            else if (c == 'x')
            {
                back_left.moveTo_base_pos();
                break;
            }
        }
    }
    while (1)
    {
        if (Serial.available())
        {
            char c = Serial.read();
            if (c == 'a')
            {
                back_right.crawl_forward();
            }
            else if (c == 'x')
            {
                back_right.moveTo_base_pos();
                break;
            }
        }
    }
    while (1)
    {
        if (Serial.available())
        {
            char c = Serial.read();
            if (c == 'a')
            {
                front_right.crawl_forward();
            }
            else if (c == 'x')
            {
                front_right.moveTo_base_pos();
                break;
            }
        }
    }
    while (1)
    {
        if (Serial.available())
        {
            char c = Serial.read();
            if (c == 'a')
            {
                front_left.crawl_forward();
            }
            else if (c == 'x')
            {
                front_left.moveTo_base_pos();
                break;
            }
        }
    }
}
