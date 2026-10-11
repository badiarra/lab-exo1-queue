#include "Led.h"
#include <Arduino.h>

Led::Led(int pin){
    _pin = pin;
    _state = false;
}

void Led::init() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    _state = false;
}

void Led::on() {
    digitalWrite(_pin, HIGH);
    _state = true;
}

void Led::off() {
    digitalWrite(_pin, LOW);
    _state = false;
}

void Led::toggle() {
    if (_state) {
        off();
    } else {
        on();
    }
}

bool Led::getState() {
    return _state;
}
