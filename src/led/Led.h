#ifndef LED_H
#define LED_H
#include <Arduino.h>
class Led 
{
  public:
    Led(int pin, int type);
    void on();
    void off();
    void init();
    int getType();

    void setQueue (QueueHandle_t q);
    static void vTaskLed(void *pvParam);
    void start();
  private:
    int _pin;
    int _type; //1 Green, 2 Yellow, 3 Red
    QueueHandle_t queue = nullptr;
    TaskHandle_t handle = nullptr;
};

#endif