/*
  Thermistor.cpp - KegNet Thermistor Library

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
#include <math.h>

class Thermistor {
  private:
    int _pin;
    int _seriesResistor;
    int _adcMax;
    int _thermistorNominal;
    int _temperatureNominal;
    int _bCoef;
    int _samples;
    int _sampleDelay;

  public:
    Thermistor(int pin, int seriesResistor, int adcMax, int thermistorNominal, int temperatureNominal, int bCoef, int samples, int sampleDelay);

    float readTempRaw();
    float readTempK();
    float readTempC();
    float readTempF();
};
