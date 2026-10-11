#include "Led.h"
#include <Arduino.h>

Led::Led(int pin, int ledType){
    _pin = pin;
    _type = ledType;
}

void Led::init() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void Led::on() {
    digitalWrite(_pin, HIGH);
}

void Led::off() {
    digitalWrite(_pin, LOW);
}

 int Led::getType(){
    return _type;
 }