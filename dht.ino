#include <DHT.h>
#define DHTTYPE DHT11

DHT dht(2, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(5000);  
  const float h = dht.readHumidity();
  const float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Sensor de mierrrda, todavia no anda!"));
    return;
  }
  float hi = dht.computeHeatIndex(t, h, false);
  Serial.print("humedad de mierda: ");
  Serial.print(h);
  Serial.print(" Temp: ");
  Serial.println(t);
  Serial.print("Sensacion termica: ");
  Serial.println(hi);
}
