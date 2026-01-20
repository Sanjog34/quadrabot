
#include"quadruped.h"

Leg front_right(3.0,2.5,13,14);
void setup(){

Serial.begin(115200);
front_right.base_height(3);
front_right.move_vertical();
}
void loop(){
    
}
