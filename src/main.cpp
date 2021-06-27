#include <Arduino.h>

#define VBATPIN 34

void read_adc_pin() {
  float vbat = 0;
  uint32_t vbat_analog = 0;
  int i;
  for (i = 0; i < 64; i++) {
    vbat_analog = vbat_analog + analogRead(VBATPIN);
  }
  vbat_analog = vbat_analog / 64;
  // Calibration
  // Using a programmable power supply, read the ADC reading and the voltage input 
  // Run a linear regression on the table to get the parameters for your voltage divider
  vbat = (float)(vbat_analog)*0.0047 + 0.8094; 
  if (vbat_analog == 0) {
    vbat = 0;
  }
  Serial.print(F("ADC reading: "));
  Serial.print(vbat_analog);
  Serial.print(F("  - Voltage: "));
  Serial.println(vbat);
}

void setup() {
  Serial.begin(115200);
  // Use VBATPIN as ADC
  adcAttachPin(VBATPIN);
  analogSetClockDiv(255);
}

void loop() {
  read_adc_pin();
  delay(3000);
}