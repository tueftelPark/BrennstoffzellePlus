//Fehlerquelle: Arduino muss auf 5V eingestellt sein
//kleiner Schalter auf dem Grove Steckboard

//Ein Servo kann sich zwischen 0° und 180° bewegen§

#include <Arduino_SensorKit.h>
#include <Servo.h>
Servo servo;


//Bei Bedarf hier die Zahlen ändern
int winkel1 = 0;
int winkel2 = 90;
int winkel3 = 180;

void setup() {
  Serial.begin(9600);  // Serial Monitor initialisieren (nur wenn benötigt)
  
  servo.attach(9); //servo auf D8

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

  servo.write(winkel3);
  Oled.print(winkel3);
  delay(3000);
  Oled.clear();  
}