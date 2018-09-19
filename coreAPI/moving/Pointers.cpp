#include "Pointers.h"

//     Pointers pt_s(l_Wheel, r_Wheel, c_Sensor, t_Sensor);
Pointers::Pointers(
    Motor* l_Wheel, 
    Motor* r_Wheel, 
    ColorSensor* c_Sensor,
    TouchSensor* t_Sensor
)
{
    leftWheel = l_Wheel;
    rightWheel = r_Wheel;
    colorSensor = c_Sensor;
    touchSensor = t_Sensor;
}


/*
Clock getClock() {
    return clock;
}*/
Motor* Pointers::getLeftWheel() {
    return leftWheel;
}
Motor* Pointers::getRightWheel() {
    return rightWheel;
}
ColorSensor* Pointers::getColorSensor() {
    return colorSensor;
}
TouchSensor* Pointers::getTouchSensor() {
    return touchSensor;
}
