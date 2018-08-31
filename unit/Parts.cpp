#include "Parts.h"

Parts::Parts():
  leftWheel(PORT_C), rightWheel(PORT_B),
  colorSensor(PORT_2),touchSensor(PORT_1),clock()
{

}


Clock getClock() {
    return clock;
}
Motor getLeftWheel() {
    return leftWheel;
}
Motor getRightWheel() {
    return rightWheel;
}
ColorSensor getColorSensor() {
    return colorSensor;
}
TouchSensor getTouchSensor() {
    return touchSensor;
}
