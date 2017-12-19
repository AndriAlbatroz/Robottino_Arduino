#ifndef Gestore_Robottino_h
#define Gestore_Robottino_h

#include "Arduino.h"

class Gestore_Robottino
{
  public:
    Gestore_Robottino(int pin_f_r_, int pin_f_l_, int pin_b_r_, int pin_b_l_, int pin_en_r_, int pin_en_l_);
    void Turn_For_Left(int degree);
    void Turn_For_Right(int degree);
    void Turn_Back_Left(int degree);
    void Turn_Back_Right(int degree);
    void For();
    void Back();
    void Stop();
    void Reset();
    void InitPin();
  private:
    int pin_f_r;
    int pin_f_l;
    int pin_b_r;
    int pin_b_l;    
    int pin_en_r;
    int pin_en_l;
};

#endif
