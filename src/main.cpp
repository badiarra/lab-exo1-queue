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

Led ledGreen(LED_GREEN);
Led ledYellow(LED_YELLOW);
Led ledRed(LED_RED);

HC_SR04 sensor(TRIG_PIN, ECHO_PIN);

// La file

QueueHandle_t distQueue = nullptr;
TaskHandle_t sensorHandle = nullptr;
TaskHandle_t ledsHandle = nullptr;
TaskHandle_t greenHandle = nullptr;
TaskHandle_t redHandle = nullptr;
TaskHandle_t yellowHandle = nullptr;

// Les tâches

void vTaskLed(void *pvParam) {
  float distanceRead;
  while (true) {
    if (xQueueReceive(distQueue, &distanceRead, portMAX_DELAY) == pdPASS) {
      // eteindre les DELs
      ledGreen.off();
      ledYellow.off();
      ledRed.off();
      if (distanceRead > 0 && distanceRead < 20) {
        ledRed.on();
      } else if (distanceRead >= 20 && distanceRead < 50) {
        ledYellow.on();
      } else if (distanceRead >= 50 ){  //Pour eviter 0 et les distances negatives
        ledGreen.on();
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

  xTaskCreate(vTaskLed, "Led", 2048, nullptr, 1, &ledsHandle);
}

void loop() {
  
}
