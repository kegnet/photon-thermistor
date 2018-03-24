# photon-thermistor
A fully configurable thermistor library for Particle Photon and other devices.

This library allows configuration of Vcc, analog reference voltage, and ADC max, which should allow it to work for
most device configurations.  Most thermistor libraries assume analogRef=Vcc, or ADC max=1024.

* On Photon devices, ADC max is 4095, NOT the typical Arduino 1023!
* On ESP8266 devices, ADC max is 1023 but analog reference is usually 1.0v, not 3.3v!

For NTC (negative temperature coefficient) thermistors only.

### Hookup

See https://learn.adafruit.com/thermistor/using-a-thermistor

![Breadboard Hookup](https://raw.githubusercontent.com/kegnet/photon-thermistor/master/breadboard_hookup.png)

### Configuration

Configuration is done via constructor parameters as follows:

Simplified constructor: input voltage (Vcc) = reference voltage = 3.3.
```
1. pin: Photon analog pin
2. seriesResistor: The ohms value of the fixed resistor (based on your hardware setup, usually 10k)
3. adcMax: The maximum analog-to-digital convert value returned by analogRead (Photon is 4095 NOT the typical Arduino 1023!)
4. thermistorNominal: Resistance at nominal temperature (will be documented with the thermistor, usually 10k)
5. temperatureNominal: Temperature for nominal resistance in celcius (will be documented with the thermistor, assume 25 if not stated)
6. bCoef: Beta coefficient (or constant) of the thermistor (will be documented with the thermistor, typically 3380, 3435, or 3950)
7. samples: Number of analog samples to average (for smoothing)
8. sampleDelay: Milliseconds between samples (for smoothing)

Thermistor(int pin, int seriesResistor, int adcMax, int thermistorNominal, int temperatureNominal, int bCoef, int samples, int sampleDelay)
```

Full constructor which allows configuration of Vcc and analog reference voltage.
```
1. pin: Photon analog pin
2: vcc: Input voltage
3: analogReference: reference voltage. Typically the same as vcc, but not always (ie ESP8266=1.0)
4: seriesResistor: The ohms value of the fixed resistor (based on your hardware setup, usually 10k)
5: adcMax: The maximum analog-to-digital convert value returned by analogRead (Photon is 4095 NOT the typical Arduino 1023!)
6: thermistorNominal: Resistance at nominal temperature (will be documented with the thermistor, usually 10k)
7: temperatureNominal: Temperature for nominal resistance in celcius (will be documented with the thermistor, assume 25 if not stated)
8: bCoef: Beta coefficient (or constant) of the thermistor (will be documented with the thermistor, typically 3380, 3435, or 3950)
9: samples: Number of analog samples to average (for smoothing)
10: sampleDelay: Milliseconds between samples (for smoothing)

Thermistor(int pin, float vcc, float analogReference, int seriesResistor, int adcMax, int thermistorNominal, int temperatureNominal, int bCoef, int samples, int sampleDelay)
```

### Particle Example
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

### ESP8266 Example
```
#include "photon-thermistor.h"

Thermistor *thermistor;

void setup() {
  thermistor = new Thermistor(A0, 3.3 1.0, 47000, 1024, 10000, 25, 3950, 5, 20);
}

void loop() {
  float tempF = thermistor->readTempF();
  Serial.println(String(tempF));
  delay(5000);
}
```

### Troubleshooting

* If the temperature reported by the thermistor is a very small negative number, around -140, the circuit is open or thermistor is not connected.
* If the temperature reported by the thermistor is a very high number, such as 650, the thermistor is likely connected without the 10k ohm resistor.
* Be sure your connection is Vcc -> seriesResistor -> thermistor -> ground, and your A0 pin is connect between seriesResistor and thermistor. It will not work otherwise.
