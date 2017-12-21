#ifndef Gestore_US_h
#define Gestore_US_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

class Gestore_US
{
  public:
    Gestore_US(int pin_trig, int pin_echo);
    Gestore_US(int pin_trig_r, int pin_echo_r, int pin_trig_l, int pin_echo_l);
    Gestore_US(int pin_trig, int pin_echo, long time_out);
    Gestore_US(int pin_trig_r, int pin_echo_r, int pin_trig_l, int pin_echo_l, long time_out);
  private:
    enum Unita_di_Misura
    {
      CM = 0,
      INC = 1,
      NC = 2
    }; 
};

#endif


