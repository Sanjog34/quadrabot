
#include "quadruped.h"
Leg back_left(8, 10.25, 14, 13, left);
Leg back_right(8,10.25,19,18,right);
Leg front_left(8, 10.25, 27, 26, left);
Leg front_right(8,10.25,23,21,right);

Quadruped quadruped(front_right,front_left,back_right,back_left);
void setup()
{

    Serial.begin(115200);
    quadruped.init(15,7);
    quadruped.moveTo_base_pos();
    delay(1000);
    quadruped.move_vert();
    

}
void loop()
{
    if(Serial.available()){
        char c= Serial.read();
        if(c=='a'){
            Serial.println("start");
            quadruped.move_forward();
            Serial.println("end");
        }
        if(c=='b'){
            quadruped.moveTo_base_pos();
        }
    }
}
