#include "hcsr04/HC_SR04.h"
#include "led/Led.h"
#include <Arduino.h>

// Les broches
const int LED_GREEN = 40;
const int LED_RED = 41;
const int LED_YELLOW = 42;
const int TRIG_PIN = 20;
const int ECHO_PIN = 21;

// La file
const int QUEUE_LENGTH = 10;

// Les instances

Led ledGreen(LED_GREEN,1);
Led ledYellow(LED_YELLOW,2);
Led ledRed(LED_RED,3);

HC_SR04 sensor(TRIG_PIN, ECHO_PIN);

// La file

QueueHandle_t distQueue = nullptr;

TaskHandle_t sensorHandle = nullptr;

TaskHandle_t greenHandle = nullptr;
TaskHandle_t redHandle = nullptr;
TaskHandle_t yellowHandle = nullptr;

// Les tâches

void vTaskLed(void *pvParam) {

  //Led *led =(Led*)pvParam;
  Led *led = static_cast<Led*>(pvParam);

  float distanceRead;

  while (true) {

    if (xQueueReceive(distQueue, &distanceRead, portMAX_DELAY) == pdPass) {

      // eteindre les DELs
        ledGreen.off();
        ledYellow.off();
        ledRed.off();

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

void vTaskDistance(void *pvParam) {
  float distanceMeasured;
  while (true) {
    distanceMeasured = sensor.getDistance();
    if(distQueue != nullptr){
       xQueueSend(distQueue, &distanceMeasured, 0);
    }
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

void setup() {

  // Initialisations
  ledGreen.init();
  ledYellow.init();
  ledRed.init();
  sensor.init();

  distQueue = xQueueCreate(QUEUE_LENGTH, sizeof(float));

  xTaskCreate(vTaskDistance, "Mesure", 2048, nullptr, 2, &sensorHandle);

  xTaskCreate(vTaskLed, "Led Green", 2048, ledGreen, 1, &greenHandle);
  xTaskCreate(vTaskLed, "Led Yellow", 2048, ledYellow, 1, &yellowHandle);
  xTaskCreate(vTaskLed, "Led Red", 2048, ledRed, 1, &redHandle);
}

void loop() {
  
}
