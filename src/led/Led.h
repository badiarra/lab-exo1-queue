#ifndef LED_H
#define LED_H

class Led 
{
  public:
    Led(int pin);
    void on();
    void off();
    void init();
    int getType();

    void setQueue (xQueueHandle_t q);
    static void vTaskLed(void *pvParam);
    void start()
  private:
    int _pin;
    int _type; //1 Green, 2 Yellow, 3 Red
    xQueueHandle_t queue = nullptr;
    TaskHandle_t handle = nullptr;
};

#endif