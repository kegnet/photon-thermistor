#include "photon-thermistor.h"

Thermistor *thermistor;

void setup() {
  Serial.begin(9600);
  thermistor = new Thermistor(A0, 10000, 4095, 10000, 25, 3950, 5, 20);
}

void loop() {
  float tempF = thermistor->readTempF();
  Particle.publish(String("temp"), String(tempF));
  delay(5000);
}
