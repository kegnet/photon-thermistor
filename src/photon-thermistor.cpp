/*
  photon-thermistor.cpp - Photon Thermistor Library

  Copyright (c) 2018 Paul Cowan <paul@monospacesoftware.com>
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

#define ABS_ZERO -273.15

Thermistor::Thermistor(int pin,
	int seriesResistor,
	int adcMax,
	int thermistorNominal,
	int temperatureNominal,
	int bCoef,
	int samples,
	int sampleDelay) :
		_pin(pin),
		_seriesResistor(seriesResistor),
		_adcMax(adcMax),
		_thermistorNominal(thermistorNominal),
		_temperatureNominal(temperatureNominal),
		_bCoef(bCoef),
		_samples(samples),
		_sampleDelay(sampleDelay),
		 _vcc(3.3),
		 _analogReference(3.3) {
  pinMode(_pin, INPUT);
}

Thermistor::Thermistor(int pin,
	double vcc,
	double analogReference,
	int seriesResistor,
	int adcMax,
	int thermistorNominal,
	int temperatureNominal,
	int bCoef, int samples,
	int sampleDelay):
		_pin(pin),
		_vcc(vcc),
		_analogReference(analogReference),
		_seriesResistor(seriesResistor),
		_adcMax(adcMax),
		_thermistorNominal(thermistorNominal),
		_temperatureNominal(temperatureNominal),
		_bCoef(bCoef), _samples(samples),
		_sampleDelay(sampleDelay) {
  pinMode(_pin, INPUT);
}

double Thermistor::readTempRaw() const {
  unsigned sum = 0;
  for(int i=0; i<_samples-1; i++) {
    sum += analogRead(_pin);
    delay(_sampleDelay);
  }
  sum += analogRead(_pin);

  return (1. * sum) / _samples;
}

double Thermistor::readTempK() const {
	double adcAvg = readTempRaw();
  double resistance = -1.0 * (_analogReference * _seriesResistor * adcAvg) / (_analogReference * adcAvg - _vcc * _adcMax);
  double steinhart = (1.0 / (_temperatureNominal - ABS_ZERO)) + (1.0 / _bCoef) * log(resistance / _thermistorNominal);
  double kelvin = 1.0 / steinhart;
  return kelvin;
}

double Thermistor::readTempC() const {
  return kToC(readTempK());
}

double Thermistor::readTempF() const {
  return cToF(readTempC());
}

// convert Kelvin to Celsius
double Thermistor::kToC(double k) const {
	double c = k + ABS_ZERO;
	return c;
}

// convert Celsius to Fahrenheit
double Thermistor::cToF(double c) const {
	return (c * 1.8) + 32;
}
