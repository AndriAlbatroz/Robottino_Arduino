#ifndef Gestore_US_h
#define Gestore_US_h

#include <ArduinoSTL.h>

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

using namespace std;

class Gestore_US
{
  public:
    enum Unita_di_Misura
    {
      NC = 0,
      CM = 1,
      INC = 2      
    }; 
    enum Tipo_Sensore
    {
      ND = 0,
      RIGHT = 1,
      LEFT = 2
    };
    struct Sensore
    {
      Tipo_Sensore _tipo;
      Unita_di_Misura _unita_di_misura;
      int trig_pin;
      int echo_pin;
      long time_out;
      bool _default;
    };
    Gestore_US();
    void Set_Single_Sensor(int pin_trig, int pin_echo, Unita_di_Misura _unita_di_misura);
    void Set_Single_Sensor_TO(int pin_trig, int pin_echo, long time_out, Unita_di_Misura _unita_di_misura);
    void Set_Double_Sensors(int pin_trig_r, int pin_echo_r, bool _default_r, int pin_trig_l, int pin_echo_l, bool _default_l, Unita_di_Misura _unita_di_misura);
    void Set_Double_Sensors_TO(int pin_trig_r, int pin_echo_r, bool _default_r, int pin_trig_l, int pin_echo_l, bool _default_l, long time_out, Unita_di_Misura _unita_di_misura);    
    long Calcola();
    long Calcola(Tipo_Sensore tipo_sensore);
    long Calcola_Media();
  private:
    vector<Sensore> _Sensori;
    long Trig(Sensore _sens, int _delay);
};

#endif
