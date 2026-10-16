#include "hcsr04/HC_SR04.h"
#include "led/Led.h"
#include <Arduino.h>

// Les broches
const int LED_GREEN = 40;
const int LED_RED = 41;
const int LED_YELLOW = 42;
const int TRIG_PIN = 37;
const int ECHO_PIN = 39;

// La file
const int QUEUE_LENGTH = 10;

// Les instances

Led ledGreen(LED_GREEN,1);
Led ledYellow(LED_YELLOW,2);
Led ledRed(LED_RED,3);

HC_SR04 sensor(TRIG_PIN, ECHO_PIN);

// La file
QueueHandle_t distQueue = nullptr;

// Les tâches



void setup() {

  // Initialisations
  ledGreen.init();
  ledYellow.init();
  ledRed.init();
  sensor.init();

  distQueue = xQueueCreate(QUEUE_LENGTH, sizeof(float));

  sensor.setQueue(distQueue);
  ledGreen.setQueue(distQueue);
  ledYellow.setQueue(distQueue);
  ledRed.setQueue(distQueue);


  sensor.start();
  ledGreen.start();
  ledRed.start();
  ledYellow.start();

}

void loop() {
  
}
