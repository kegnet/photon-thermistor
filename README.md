# photon-thermistor
A thermistor library for Particle Photon based on Adafruit's thermistor example
at https://learn.adafruit.com/thermistor/using-a-thermistor with thermistor
hardware http://www.adafruit.com/products/372.

This library uses the simplified version of the Steinhart–Hart equation described by
Adafruit with full configuration of the required variables as constructor parameters.

Most Arduino thermistor libraries assume the maximum analogRead value is 1023, but
the Photon's maximum analogRead value is 4095!

For NTC (negative temperature coefficient) thermistors only.

### Hookup

See https://learn.adafruit.com/thermistor/using-a-thermistor

![Breadboard Hookup](https://raw.githubusercontent.com/kegnet/photon-thermistor/master/breadboard_hookup.png)

### Configuration

Configuration is done via constructor parameters as follows:

```
Thermistor(int pin, int seriesResistor, int adcMax, int thermistorNominal, int temperatureNominal, int bCoef, int samples, int sampleDelay);

1. pin: Photon analog pin
2. seriesResistor: The ohms value of the fixed resistor (based on your hardware setup, usually 10k)
3. adcMax: The maximum analog-to-digital convert value returned by analogRead (Photon is 4095 NOT the typical Arduino 1023!)
4. thermistorNominal: Resistance at nominal temperature (will be documented with the thermistor, usually 10k)
5. temperatureNominal: Temperature for nominal resistance in celcius (will be documented with the thermistor, assume 25 if not stated)
6. bCoef: Beta coefficient (or constant) of the thermistor (will be documented with the thermistor, typically 3380, 3435, or 3950)
7. samples: Number of analog samples to average (for smoothing)
8. sampleDelay: Milliseconds between samples (for smoothing)
```

### Example

```
#include "photon-thermistor.h"

Thermistor *thermistor;

void setup() {
  thermistor = new Thermistor(A0, 10000, 4095, 10000, 25, 3950, 5, 20);
}

void loop() {
  float tempF = thermistor->readTempF();
  Particle.publish(String("temp"), String(tempF));
  delay(5000);
}
```

### Troubleshooting

* If the temperature reported by the thermistor is a very small negative number, around -140, the circuit is open or thermistor is not connected.
* If the temperature reported by the thermistor is a very high number, such as 650, the thermistor is likely connected without the 10k ohm resistor.
