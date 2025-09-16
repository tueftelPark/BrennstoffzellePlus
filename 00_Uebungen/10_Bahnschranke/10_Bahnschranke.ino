// Bahnschrankensteuerung

#include <Servo.h> // Servo-Bibliothek einbinden
Servo schranke;

// Grove Ultrasonic Sensorist an Pin D3 angeschlossen
const int ultrasonicPin = 3; // Digital Pin 3 für den Grove Sensor

// Grove Servo ist an Pin D8 angeschlossen
const int servoPin = 8; 

//TODO: Hier den Schwellwert für die Entfernung anpassen (aus der Aufgabe 01_Enfternung)
const int schwellwert = XX; // Anpassbarer Schwellwert

//TODO: Hier die Winkel anpassen für die Bahnschranke anpassen (aus der Aufgabe 02_Winkel)
const int winkelAuf = YY;
const int winkelZu = YY;

//TODO: Entscheide hier wie lange die Bahnschranke offen sein soll
//      ACHTUNG: Ersetzte ZZ mit der Anzahl Millisekunden
//                  5 Sekunden = 5000
const int zeit = ZZ;

void setup() {
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
    delay(zeit);        // Offen halten für 3 Sekunden
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