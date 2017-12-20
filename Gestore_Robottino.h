/*********************************************************
 * 
 * Powered by: AndriAlbatroz
 * 
 * A simple library for controll two DC motors linked to a 
 * L298N motor driver (2 h bridge) and read the values of
 * the 2 HC-SR04 sensors
 * 
 * FileName: Header File of the library
 * 
*********************************************************/

#ifndef Gestore_Robottino_h
#define Gestore_Robottino_h

#include "Arduino.h"

class Gestore_Robottino
{
  public:
    Gestore_Robottino();
    void Set_Motor(int pin_f_r_, int pin_f_l_, int pin_b_r_, int pin_b_l_, int pin_en_r_, int pin_en_l_);
    void Set_US(int pin_us_trig_r_, int pin_us_trig_l_, int pin_us_echo_r_, int pin_us_echo_l_);
    void Turn_For_Left(int degree, bool use_previus_direction);
    void Turn_For_Right(int degree, bool use_previus_direction);
    void Turn_Back_Left(int degree, bool use_previus_direction);
    void Turn_Back_Right(int degree, bool use_previus_direction);
    void For();
    void Back();
    void Stop();
    void Reset();
    void InitPin();
    long GetDistance();
    // Enumerator for the management of the flow chart
    enum _Stato
    {
      Init_,
      Forward_,
      Back_,
      Turning_Left,
      Turning_Right,
      Obstacle,
      Obstacle_r,
      Obstacle_l,
      Stop_
    };
    // Function that return the _Stato (enum) type
    _Stato GetState();
    // Function that set the _Stato (enum) value
    void SetState(_Stato stato);

  private:
  // Pinss
    int pin_f_r;
    int pin_f_l;
    int pin_b_r;
    int pin_b_l;    
    int pin_en_r;
    int pin_en_l;
    int pin_us_trig_r;
    int pin_us_trig_l;
    int pin_us_echo_r;
    int pin_us_echo_l;
    // Offest of the US
    int offset;
    // Function for decide the direction when the us is true
    void DecicedeDirecetionNextUS();
    // Variabile private that is the current state of the machine
    _Stato _stato;
};

#endif
