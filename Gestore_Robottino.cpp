#include "Arduino.h"
#include "Gestore_Robottino.h"

Gestore_Robottino::Gestore_Robottino(int pin_f_r_, int pin_f_l_, int pin_b_r_, int pin_b_l_, int pin_en_r_, int pin_en_l_)
{
  pin_f_r = pin_f_r_;
  pin_f_l = pin_f_l_;
  pin_b_r = pin_b_r_;
  pin_b_l = pin_b_l_;
  pin_en_r = pin_en_r_;
  pin_en_l = pin_en_l_;

  pinMode(pin_f_r, OUTPUT);
  pinMode(pin_f_l, OUTPUT);
  pinMode(pin_b_r, OUTPUT);
  pinMode(pin_b_l, OUTPUT);
  pinMode(pin_en_r, OUTPUT);
  pinMode(pin_en_l, OUTPUT);

  digitalWrite(pin_en_r, true);
  digitalWrite(pin_en_l, true);
  
  //InitPin();
}

void Gestore_Robottino::InitPin() 
{
  pinMode(pin_f_r, OUTPUT);
  pinMode(pin_f_l, OUTPUT);
  pinMode(pin_b_r, OUTPUT);
  pinMode(pin_b_l, OUTPUT);

  Reset();
}

void Gestore_Robottino::Turn_For_Left(int degree) 
{
  if (degree == 0) return;

  Reset();

  for (int i = 0; i <= degree; i++) 
  {
    digitalWrite(pin_f_r, true);
    digitalWrite(pin_b_r, false);
  }
}

void Gestore_Robottino::Turn_For_Right(int degree) 
{
  if (degree == 0) return;

  Reset();

  for (int i = 0; i <= degree; i++)
  {
    digitalWrite(pin_f_l, true);
    digitalWrite(pin_f_r, false);
  }
}

void Gestore_Robottino::Turn_Back_Left(int degree) 
{
  if (degree == 0) return;

  Reset();

  for (int i = 0; i <= degree; i++)
  {
    digitalWrite(pin_b_r, true);
    digitalWrite(pin_b_l, false);
  }
}

void Gestore_Robottino::Turn_Back_Right(int degree)
{
  if (degree == 0) return;

  Reset();

  for (int i = 0; i <= degree; i++)
  {
    digitalWrite(pin_b_l, true);
    digitalWrite(pin_b_r, false);
  }
}

void Gestore_Robottino::Back() 
{
  Reset();

  digitalWrite(pin_b_r, true);
  digitalWrite(pin_b_l, true);
}

void Gestore_Robottino::For() 
{
  Reset();

  digitalWrite(pin_f_l, true);
  digitalWrite(pin_f_r, true);
}

void Gestore_Robottino::Stop()
{
  Reset();
}

void Gestore_Robottino::Reset()
{
  digitalWrite(pin_f_r, false);
  digitalWrite(pin_f_l, false);
  digitalWrite(pin_b_r, false);
  digitalWrite(pin_b_l, false);
}

