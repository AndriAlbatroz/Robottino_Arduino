#include "Gestore_US.h"

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

Gestore_US::Gestore_US()
{
	
}

void Gestore_US::Set_Single_Sensor(int pin_trig, int pin_echo, Unita_di_Misura _unita_di_misura)
{
	Sensore _sensore;
 
	_sensore._tipo = Tipo_Sensore::ND;
	_sensore._unita_di_misura = _unita_di_misura;
	_sensore.trig_pin = pin_trig;
	_sensore.echo_pin = pin_echo;
	_sensore.time_out = 1500;
	_sensore._default = true;

	_Sensori.push_back(_sensore);
}

void Gestore_US::Set_Double_Sensors(int pin_trig_r, int pin_echo_r, bool _default_r, int pin_trig_l, int pin_echo_l, bool _default_l, Unita_di_Misura _unita_di_misura)
{
 	if (_default_r == _default_l) return;

	Sensore _sensore_r, _sensore_l;

	_sensore_r._tipo = Tipo_Sensore::RIGHT;
  _sensore_r._unita_di_misura = _unita_di_misura;
	_sensore_r.trig_pin =  pin_trig_r;
	_sensore_r.echo_pin = pin_echo_r;
	_sensore_r.time_out = 3000;
	_sensore_r._default = _default_r;

	_sensore_l._tipo = Tipo_Sensore::LEFT;
  _sensore_l._unita_di_misura = _unita_di_misura;
	_sensore_l.trig_pin = pin_trig_l;
	_sensore_l.echo_pin = pin_echo_l;
	_sensore_l.time_out = 3000;
	_sensore_l._default = _default_l;

	_Sensori.push_back(_sensore_r);
	_Sensori.push_back(_sensore_l);
}


void Gestore_US::Set_Single_Sensor_TO(int pin_trig, int pin_echo, long time_out, Unita_di_Misura _unita_di_misura)
{
	Sensore _sensore;

	_sensore._tipo = Tipo_Sensore::ND;
  _sensore._unita_di_misura = _unita_di_misura;
	_sensore.trig_pin = pin_trig;
	_sensore.echo_pin = pin_echo;
	_sensore.time_out = time_out;
	_sensore._default = true;

	_Sensori.push_back(_sensore);
}


void Gestore_US::Set_Double_Sensors_TO(int pin_trig_r, int pin_echo_r, bool _default_r, int pin_trig_l, int pin_echo_l, bool _default_l, long time_out, Unita_di_Misura _unita_di_misura)
{
 	if (_default_r == _default_l) return;

	Sensore _sensore_r, _sensore_l;

	_sensore_r._tipo = Tipo_Sensore::RIGHT;
  _sensore_r._unita_di_misura = _unita_di_misura;
	_sensore_r.trig_pin =  pin_trig_r;
	_sensore_r.echo_pin = pin_echo_r;
	_sensore_r.time_out = time_out;
	_sensore_r._default = _default_r;

	_sensore_l._tipo = Tipo_Sensore::LEFT;
  _sensore_l._unita_di_misura = _unita_di_misura;
	_sensore_l.trig_pin = pin_trig_l;
	_sensore_l.echo_pin = pin_echo_l;
	_sensore_l.time_out = time_out;
	_sensore_l._default = _default_l;

	_Sensori.push_back(_sensore_r);
	_Sensori.push_back(_sensore_l);
}

long Gestore_US::Calcola() 
{
	if (sizeof(_Sensori) < 0) return;

  long durata = 0;
  
  for (int i = 0; i < sizeof(_Sensori); i++) 
  {
    if (_Sensori[i]._default)
    {
      durata = Trig(_Sensori[i], 10);
      switch(_Sensori[i]._unita_di_misura) 
      {
        case Unita_di_Misura::NC:
          return durata;
        break;
        case Unita_di_Misura::CM:
          return durata / 29 / 2;
        break;
        case Unita_di_Misura::INC:
          return durata / 72 / 2;
        break;
      }
      break;
    }
    else
    {
      continue;
    }
  } 
}

long Gestore_US::Calcola(Tipo_Sensore tipo_sensore) 
{
	if (sizeof(_Sensori) < 0) return;

  long durata = 0;
  
  for (int i = 0; i < sizeof(_Sensori); i++) 
  {
    if (_Sensori[i]._tipo == tipo_sensore)
    {
      durata = Trig(_Sensori[i], 10);
      switch(_Sensori[i]._unita_di_misura) 
      {
        case Unita_di_Misura::NC:
          return durata;
        break;
        case Unita_di_Misura::CM:
          return durata / 29 / 2;
        break;
        case Unita_di_Misura::INC:
          return durata / 72 / 2;
        break;
      }
      break;
    }
    else
    {
      continue;
    }
  } 
}

long Gestore_US::Calcola_Media()
{
	if (sizeof(_Sensori) <= 1) return;

	long durata_0 = Trig(_Sensori[0], 10);
	long durata_1 = Trig(_Sensori[1], 10);

  if (_Sensori[0]._unita_di_misura == _Sensori[1]._unita_di_misura)
  {
     switch(_Sensori[0]._unita_di_misura) 
      {
        case Unita_di_Misura::NC:
          return (durata_0 + durata_1) / 2;
        break;
        case Unita_di_Misura::CM:
          return (durata_0 + durata_1) / 2 / 29 / 2;
        break;
        case Unita_di_Misura::INC:
          return (durata_0 + durata_1) / 2 / 72 / 2;
        break;
      }
  }
}

long Gestore_US::Trig(Sensore _sens, int _delay) 
{
	digitalWrite(_sens.trig_pin, false);
  delayMicroseconds(2);
	digitalWrite(_sens.trig_pin, true);
	delayMicroseconds(_delay);
	digitalWrite(_sens.trig_pin, false);
  return pulseIn(_sens.echo_pin, true, _sens.time_out) == 0 ? _sens.time_out : pulseIn(_sens.echo_pin, true, _sens.time_out);
}
