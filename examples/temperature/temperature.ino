#include "photon-thermistor.h"

Thermistor *thermistor;

void setup() {
  thermistor = new Thermistor(A0, 10000, 10000, 25, 3950, 5, 20);
}

void loop() {
  double tempF = thermistor->readTempF();
  Particle.publish(String("tempF"), String(tempF));
  delay(5000);
}
