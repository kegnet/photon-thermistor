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
#ifndef PHOTON_THERMISTOR_H
#define PHOTON_THERMISTOR_H

#include <math.h>


class Thermistor {
  protected:
    const int _pin;
    const int _seriesResistor;
    const int _adcMax;
    const int _thermistorNominal;
    const int _temperatureNominal;
    const int _bCoef;
    const int _samples;
    const int _sampleDelay;

    float readTempRaw() const;

  public:
    /*
    * arg 1: pin: Photon analog pin
    * arg 2: seriesResistor: The ohms value of the fixed resistor (based on your hardware setup, usually 10k)
    * arg 3: adcMax: The maximum analog-to-digital convert value returned by analogRead (Photon is 4095 NOT the typical Arduino 1023!)
    * arg 4: thermistorNominal: Resistance at nominal temperature (will be documented with the thermistor, usually 10k)
    * arg 5: temperatureNominal: Temperature for nominal resistance in celcius (will be documented with the thermistor, assume 25 if not stated)
    * arg 6: bCoef: Beta coefficient (or constant) of the thermistor (will be documented with the thermistor, typically 3380, 3435, or 3950)
    * arg 7: samples: Number of analog samples to average (for smoothing)
    * arg 8: sampleDelay: Milliseconds between samples (for smoothing) */
    Thermistor(int pin, int seriesResistor, int adcMax, int thermistorNominal,
    		int temperatureNominal, int bCoef, int samples, int sampleDelay);

    // Temperature in Kelvin
    float readTempK() const;
    // Temperature in Celsius
    float readTempC() const;
    // Temperature in Farenight
    float readTempF() const;
};

#endif
