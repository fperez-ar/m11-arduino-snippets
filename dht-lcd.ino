#include<LiquidCrystal.h> //16x2
#include <DHT.h>
#define DHTTYPE DHT11
#define CONTRAST_DHT11 100
#define DEBUG 0
#define INTERVAL 5000
// Connections:
// VSS, RW, K to GND 
// VDD 5v
// V0 2k Resist to GND
// A(node) to POT or 5v
const int rs = 10, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// temp sensor
DHT dht(13, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  // LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Hola mundo");
}

// int sprintf(char *buffer, const char *format, ...);
void loop() {
  delay(INTERVAL);  
  const float h = dht.readHumidity();
  const float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Sensor no inicializado"));
    return;
  }
  float hi = dht.computeHeatIndex(t, h, false);
  #if DEBUG
  Serial.print(F("Temp: "));
  Serial.println(t);
  Serial.print(F("Humedad: "));
  Serial.println(h);
  Serial.print(F("Sensacion termica: "));
  Serial.println(hi);
  #endif

  // LCD
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t);
  lcd.print(" H: ");
  lcd.println(h);
  lcd.setCursor(0, 1);
  lcd.print("Sensacion: ");
  lcd.println(hi);
}

