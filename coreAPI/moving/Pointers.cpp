#include "Pointers.h"

Pointers::Pointers(Pointers* ptrs_p) {
    centerArm = ptrs_p->getCenterArm();
    leftWheel = ptrs_p->getLeftWheel();
    rightWheel = ptrs_p->getRightWheel();
    colorSensor = ptrs_p->getColorSensor();
    touchSensor = ptrs_p->getTouchSensor();
}

Pointers::Pointers(
    Motor* c_Arm, 
    Motor* l_Wheel, 
    Motor* r_Wheel, 
    ColorSensor* c_Sensor,
    TouchSensor* t_Sensor
) {
    centerArm = c_Arm;
    leftWheel = l_Wheel;
    rightWheel = r_Wheel;
    colorSensor = c_Sensor;
    touchSensor = t_Sensor;
}


Motor* Pointers::getCenterArm() {
    return centerArm;
}
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
