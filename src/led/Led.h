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
    int getType();
  private:
    int _pin;
    bool _state;
    int _type; //1 Green, 2 Yellow, 3 Red
};

#endif