#ifndef HC_SR04_H
#define HC_SR04_H

#include <Arduino.h>

class HC_SR04
{
private:

    int trigPin;
    int echoPin;

    TaskHandle_t handle = nullptr;

    xQueueHandle_t queue = nullptr;

public:

    HC_SR04(int trig, int echo);

    void init();

    float getDistance();

    static void vTaskSensor( void *pvParam);

    void start();

    void stop();

    void setQueue( xQueueHandle_t queue);

};

#endif
