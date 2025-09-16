//TODO: Du kannst zusätzliche Bedingungen wie z.B.: eine LED ansteuern,
//      wenn die Bahnschranke offen ist ab Zeile 150 einfügen

#include <Arduino_SensorKit.h>
#include <Servo.h>
Servo servo;

// Pin für den Servo -> Grove D8
const int servoPin = 8;
// Pin für den Ultraschallsensor-Sensor -> Grove D3
const int echoPin = 3; 
// Pin für den Button -> Grove D4 (Schon vorverbunden)
const int Taster = 4; 


//TODO: Hier den Schwellwert für die Entfernung anpassen (aus der Aufgabe 01_Enfternung)
const int schwellwert = XX; // Anpassbarer Schwellwert

//TODO: Hier die Winkel anpassen für die Bahnschranke anpassen (aus der Aufgabe 02_Winkel)
const int winkelAuf = YY;
const int winkelZu = YY;

//TODO: Entscheide hier wie lange die Bahnschranke offen sein soll
//      ACHTUNG: Ersetzte ZZ mit der Anzahl Millisekunden
//                  5 Sekunden = 5000
const int zeit = ZZ;


// Timer-Variablen
unsigned long startMillis = 0; // Startzeit
unsigned long elapsedMillis = 0; // Vergangene Zeit
bool running = false; // Timer-Status
bool measurementComplete = false; // Flag für abgeschlossene Messung
bool readyForNewMeasurement = false; // Flag für bereit für neue Messung

// Schrankensteuerung
bool schrankeOffen = false; // Status der Schranke
unsigned long schrankeTimer = 0; // Startzeit der geöffneten Schranke
const unsigned long schrankeOffenZeit = 3000; // Schranke bleibt 3 Sekunden geöffnet

// Letzter Button-Status für Entprellung
int Tasterstatus = 0; // Startwert
int lastTasterstatus = 0; // Vorheriger Zustand des Buttons

// Für das OLED-Display
unsigned long lastDisplayedSeconds = 0; // Zuletzt angezeigte Sekunden
unsigned long finalTime = 0; // Gespeicherte Endzeit in Sekunden

void setup() {
  // Servo initialisieren
  servo.attach(servoPin);
  servo.write(winkelZu); // Schranke geschlossen

  // Grove Ultrasonic Sensor benötigt keinen separaten Trigger-Pin
  pinMode(echoPin, INPUT);

  // Taster-Pin
  pinMode(Taster, INPUT); // Taster als Eingang

  // OLED-Display starten
  Oled.begin();
  Oled.setFlipMode(false); // Text wird normal angezeigt
  Oled.setFont(u8x8_font_px437wyse700b_2x2_r);
  Oled.clear();
  Oled.println("ready");
  Oled.display(); // OLED aktualisieren
  delay(1000);
}

void loop() {
  // Button einlesen
  Tasterstatus = digitalRead(Taster);

  // Flankengesteuerte Erkennung des Buttons
  if (Tasterstatus == HIGH && lastTasterstatus == LOW) {
    delay(50); // Entprellung
    if (digitalRead(Taster) == HIGH) {
      // Zustandsmaschine für die Messung
      if (!running && !measurementComplete && !readyForNewMeasurement) {
        // Erster Druck - Starte Messung
        running = true;
        startMillis = millis();
        Oled.clear();
      } 
      else if (running) {
        // Zweiter Druck - Stoppe Messung
        running = false;
        measurementComplete = true;
        finalTime = elapsedMillis / 1000;
        displayFinalTime();
      }
      else if (measurementComplete) {
        // Dritter Druck - Bestätige und gehe in Bereitschaft
        measurementComplete = false;
        readyForNewMeasurement = true;
        Oled.clear();
        Oled.println("ready");
        Oled.display();
      }
      else if (readyForNewMeasurement) {
        // Vierter Druck - Starte neue Messung
        readyForNewMeasurement = false;
        running = true;
        elapsedMillis = 0;
        startMillis = millis();
        Oled.clear();
      }
    }
  }
  lastTasterstatus = Tasterstatus;

  // Timer-Berechnung, falls aktiv
  if (running) {
    elapsedMillis = millis() - startMillis;
    
    // Aktualisiere die Anzeige während der Messung jede Sekunde
    unsigned long currentSeconds = elapsedMillis / 1000;
    if (currentSeconds != lastDisplayedSeconds) {
      lastDisplayedSeconds = currentSeconds;
      displayCurrentTime();
    }
  }

  // Schrankensteuerung
  schrankeSteuern();

  delay(50); // Kurze Pause für Stabilität
}

// Anzeige der aktuellen Zeit während der Messung
void displayCurrentTime() {
  Oled.clear();
  Oled.print(lastDisplayedSeconds); // Nur ganze Sekunden
  Oled.print(" s");
  Oled.display();
}

// Anzeige der Endzeit mit 2 Nachkommastellen
void displayFinalTime() {
  Oled.clear();
  
  // Um die Endzeit mit zwei Nachkommastellen anzuzeigen, kannst du die float-Werte verwenden
  float finalTimeInSeconds = finalTime + (elapsedMillis % 1000) / 1000.0;
  Oled.print(finalTimeInSeconds, 2); // Zeigt 2 Dezimalstellen
  Oled.print(" s");
  Oled.display();
}

// Schrankensteuerung basierend auf Entfernung
void schrankeSteuern() {
  long entfernung = messeEntfernung();

  // Schranke öffnen, wenn ein Objekt erkannt wird und sie geschlossen ist
  if (entfernung > 0 && entfernung < schwellwert && !schrankeOffen) {
    servo.write(winkelAuf); // Schranke öffnet
    schrankeOffen = true;
    schrankeTimer = millis(); // Startzeit merken
  }

  // Schranke schließen, wenn sie offen ist und die Zeit abgelaufen ist
  if (schrankeOffen && millis() - schrankeTimer >= schrankeOffenZeit) {
    servo.write(winkelZu); // Schranke schließt
    schrankeOffen = false;
  }
}

// Funktion zur Messung der Entfernung mit Grove Ultrasonic Sensor
long messeEntfernung() {
  pinMode(echoPin, OUTPUT);
  digitalWrite(echoPin, LOW);
  delayMicroseconds(2);
  digitalWrite(echoPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(echoPin, LOW);
  pinMode(echoPin, INPUT);
  
  long dauer = pulseIn(echoPin, HIGH);
  long entfernung = (dauer * 0.034) / 2;
  return entfernung;
}
