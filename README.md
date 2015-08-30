# photon-thermistor
A thermistor library for Particle (Spark) Photon
Based on Adafruit Thermistor documentation at https://learn.adafruit.com/thermistor/using-a-thermistor with thermistor hardware http://www.adafruit.com/products/372.

Most other thermistor libraries assume the maximum alalogRead value is 1023, but
the Photon's maximum analogRead value is 4095!

This library uses the simplied version of the Steinhart–Hart equation described in the
Adafruit with full configuration of the required variables as constructor parameters.

For an NTC (negative temperature coefficient) thermistor only!

###CONSTRUCTOR PARAMETERS:

```
Thermistor(int pin, int seriesResistor, int adcMax, int thermistorNominal, int temperatureNominal, int bCoef, int samples, int sampleDelay);

<pin>: Photon pin
<seriesResistor>: The resistance value of the fixed resistor (based on your hardware setup)
<adcMax>: The maximum analog-to-digital convert value returned by analogRead (Photon is 4095 NOT the typical Arduino 1023!)
<thermistorNominal>: Resistance at nominal temperature (will be documented with the thermistor, usually "10k")
<temperatureNominal>: Temperature for nominal resistance in celcius (will be supplied with the thermistor, assume 25 if not stated)
<bCoef>: Beta coefficient of the thermistor; usually 3435 or 3950 (will be documented with the thermistor)
<samples>: Number of analog samples to average (for smoothing)
<sampleDelay>: Milliseconds between analog samples (for smoothing)
```
