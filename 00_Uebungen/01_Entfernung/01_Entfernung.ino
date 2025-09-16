//Fehlerquelle: Arduino muss auf 5V eingestellt sein
//kleiner Schalter auf dem Grove Steckboard

// TODO: Stecke den Ultraschall Sensor auf dem Grove Steckerbrett D3 ein

#include <Arduino_SensorKit.h>

const int sensor = 3;  // D3 für den Ultraschallsensor

void setup() {
  Serial.begin(9600);  // Serial Monitor initialisieren (nur wenn benötigt)
  
  // OLED Display initialisieren
  Oled.begin();
  Oled.setFlipMode(false);
  Oled.setFont(u8x8_font_px437wyse700b_2x2_r);
  Oled.clear();
  
  // Begrüßungsnachricht
  Oled.setCursor(0, 0);
  Oled.print("Bereit");
  delay(3000);
  Oled.clear();
}

void loop() {
  // Messung durchführen
  pinMode(sensor, OUTPUT);
  digitalWrite(sensor, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor, LOW);
  
  pinMode(sensor, INPUT);
  long entfernung = pulseIn(sensor, HIGH) / 29 / 2;
  
  // Anzeige aktualisieren
  Oled.clear();
  Oled.setCursor(0, 3);
  Oled.print(entfernung);
  Oled.print(" cm");
  
  delay(500);
}