// Bahnschrankensteuerung mit:
// - Grove Ultrasonic Distance Sensor V2.0 an D8
// - Grove Servo an D3

#include <Servo.h> // Servo-Bibliothek einbinden

// Grove Ultrasonic Sensor V2.0 ist an Pin D3 angeschlossen
const int ultrasonicPin = 3; // Digital Pin 3 für den Grove Sensor

// Grove Servo ist an Pin D8 angeschlossen
const int servoPin = 9; 
Servo schranke;

// Hier Entfernung anpassen
const int schwellwert = 20; // Anpassbarer Schwellwert

// Hier Winkel anpassen
const int winkelAuf = 180;
const int winkelZu = 0;

void setup() {
  // Grove Sensor benötigt kein spezielles Setup im setup()
  
  // Servo initialisieren
  schranke.attach(servoPin);
  schranke.write(winkelZu); // Startposition: Schranke geschlossen

}

void loop() {
  // Entfernung messen
  long entfernung = messeEntfernung();
  
  // Schrankensteuerung
  if (entfernung > 0 && entfernung < schwellwert) {
    Serial.println("Objekt erkannt! Öffne Schranke...");
    schranke.write(winkelAuf); // Schranke öffnen (100°)
    delay(3000);        // Offen halten für 3 Sekunden
    schranke.write(winkelZu);  // Schranke schließen (0°)
  }

  // Wartezeit zwischen den Messungen
  delay(100);
}

// Funktion zur Entfernungsmessung mit Grove Ultrasonic V2.0
long messeEntfernung() {
  // Sensor vorbereiten
  pinMode(ultrasonicPin, OUTPUT);
  digitalWrite(ultrasonicPin, LOW);
  delayMicroseconds(2);
  
  // Trigger-Impuls senden
  digitalWrite(ultrasonicPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicPin, LOW);
  
  // Auf Echo warten
  pinMode(ultrasonicPin, INPUT);
  long dauer = pulseIn(ultrasonicPin, HIGH);

  // Entfernung berechnen (Schallgeschwindigkeit 343 m/s → 0.034 cm/µs)
  long entfernung = (dauer * 0.034) / 2;

  return entfernung;
}