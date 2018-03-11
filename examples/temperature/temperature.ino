#include "photon-thermistor.h"

// Declare a pointer to the thermistor we'll initialize during setup
Thermistor *thermistor;

void setup() {
  // Initialize the thermistor with required parameters.
  // For hookup instructions see https://github.com/kegnet/photon-thermistor
  //
  // CONSTRUCTOR PARAMETERS:
  // 1. pin: Photon analog pin
  // 2. seriesResistor: The ohms value of the fixed resistor (based on your hardware setup, usually 10k)
  // 3. adcMax: The maximum analog-to-digital convert value returned by analogRead (Photon is 4095 NOT the typical Arduino 1023!)
  // 4. thermistorNominal: Resistance at nominal temperature (will be documented with the thermistor, usually 10k)
  // 5. temperatureNominal: Temperature for nominal resistance in celcius (will be documented with the thermistor, assume 25 if not stated)
  // 6. bCoef: Beta coefficient (or constant) of the thermistor (will be documented with the thermistor, typically 3380, 3435, or 3950)
  // 7. samples: Number of analog samples to average (for smoothing)
  // 8. sampleDelay: Milliseconds between samples (for smoothing)
  thermistor = new Thermistor(A0, 10000, 4095, 10000, 25, 3950, 5, 20);
}

void loop() {
  // Call one readTemp method to get temperature in Kelvin, Celsius, or Fahrenheit
  //float tempK = thermistor->readTempK();
  //float tempC = thermistor->readTempC();
  float tempF = thermistor->readTempF();

  Particle.publish(String("tempF"), String(tempF));
  delay(5000);
}
