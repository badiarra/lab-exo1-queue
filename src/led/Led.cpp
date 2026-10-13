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

 void Led::vTaskLed(void *ptr){

   // Led * led = (Led *)ptr;
    Led * led = static_cast<Led *>(ptr);

    float distanceRead;

  while (true) {

    if (xQueueReceive(led->queue, &distanceRead, portMAX_DELAY) == pdPass) {

      // eteindre les DELs
        led->off();

      if (distanceRead > 0 && distanceRead < 20 && led->getType() == 3) {  //Rouge
        led->on();
      } else if (distanceRead >= 20 && distanceRead < 50 && led->getType() == 2) { //Jaune
        led->on();
      } else if (distanceRead >= 50 && led->getType() == 1){  //Pour eviter 0 et les distances negatives
        led->on();
      }
    }
    //vTaskDelay(pdMS_TO_TICKS(500));  //Pas indispensable car xQueueReceive bloque aussi la tache
  }
 }


 void Led::start(){

    xTaskCreate(vTaskLed,
                "Task Led",
                2048,
                this,
                1,
                &handle);
 }


 void Led::setQueue(QueueHandle_t dataQueue){
    queue  = dataQueue;
}