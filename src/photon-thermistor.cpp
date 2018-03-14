/*
  Thermistor.cpp - Photon Thermistor Library

  Copyright (c) 2015 Paul Cowan <paul@monospacesoftware.com>
  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "photon-thermistor.h"
#include "application.h"
#include <math.h>

#define ABS_ZERO -273.15

Thermistor::Thermistor(int pin, int seriesResistor, int adcMax, int thermistorNominal,
		int temperatureNominal, int bCoef, int samples, int sampleDelay) :
		_pin(pin),_seriesResistor(seriesResistor), _adcMax(adcMax), _thermistorNominal(thermistorNominal),
		_temperatureNominal(thermistorNominal), _bCoef(bCoef), _samples(samples), _sampleDelay(sampleDelay) {
  pinMode(_pin, INPUT);
}

float Thermistor::readTempRaw() const {
  unsigned sum = 0;
  for(int i=0; i<_samples-1; i++) {
    sum += analogRead(_pin);
    delay(_sampleDelay);
  }
  sum += analogRead(_pin);

  return (1. * sum) / _samples;
}
float Thermistor::readTempK() const {
  float adcAvg = readTempRaw();
  float resistance = ((float)_seriesResistor) / (((float)_adcMax) / adcAvg - 1);
  float s = log(resistance / _thermistorNominal) / _bCoef + 1.0f / (_temperatureNominal - ABS_ZERO);
  return 1 / s;
}

float Thermistor::readTempC() const {
  return readTempK() + ABS_ZERO;
}

float Thermistor::readTempF() const {
  return (readTempC() * 1.8) + 32;
}
