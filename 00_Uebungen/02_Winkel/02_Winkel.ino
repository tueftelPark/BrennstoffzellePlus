//Fehlerquelle: Arduino muss auf 5V eingestellt sein
//kleiner Schalter auf dem Grove Steckboard

#include <Arduino_SensorKit.h>
#include <Servo.h>
Servo servo;

//TODO: Schliesse den Servo am Grove Steckbrett D8 an

const int mein_servo = 9; 

//Ein Servo kann sich zwischen 0° und 180° bewegen
//TODO: Wähle 2 Winkel zwischen 0° und 180° aus und trage diese in Zeile 14 und 15 ein
//      ersetze YY mit der jeweiligen Zahl für den Winkel
//      (Achtung Zahl ohne ° (Winkel Symbol eintragen))

//Bei Bedarf hier die Zahlen ändern
int winkel1 = YY;
int winkel2 = YY;

void setup() {
  Serial.begin(9600);  // Serial Monitor initialisieren (nur wenn benötigt)
  
  servo.attach(mein_servo); //servo auf D8

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

void loop()
{ 
  servo.write(winkel1);
  Oled.print(winkel1);
  delay(3000);
  Oled.clear();                        

  servo.write(winkel2);
  Oled.print(winkel2);
  delay(3000);
  Oled.clear();    
}