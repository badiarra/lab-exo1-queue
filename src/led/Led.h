#ifndef LED_H
#define LED_H

class Led 
{
  public:
    Led(int pin);
    void on();
    void off();
    void toggle();
    bool getState();
    void init();
  private:
    int _pin;
    bool _state;
};

#endif