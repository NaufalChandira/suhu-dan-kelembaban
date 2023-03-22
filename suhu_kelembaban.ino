#define BLYNK_TEMPLATE_ID "TMPL6aehE2BbE"
#define BLYNK_TEMPLATE_NAME "Suhu"
#define BLYNK_AUTH_TOKEN "-ncAnjvDIxJctB0wA5sOqRcoDmxTnX8i"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>

#include "DHT.h"

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Hadi's";  // type your wifi name
char pass[] = "Den200904";  // type your wifi password

BlynkTimer timer;

#include <LiquidCrystal_I2C.h>
#define DHTTYPE DHT11
#define dht_pin D4
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
// pin data sensor DHT11 terhubung pada pin digital 2
     // tipe sensor DHT11
DHT dht(dht_pin, DHTTYPE);

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);

      lcd.print("Suhu: ");
  lcd.print(t);
  lcd.print(",");
    lcd.print("Kelembaban: ");
  lcd.print(h);
  lcd.println("\n");
  delay(8000);
}

void setup() {
  Serial.begin(115200);

Blynk.begin(auth, ssid, pass, "blynk-cloud.com",8080);
dht.begin();
    lcd.init();
  // set up the LCD's number of columns and rows:
  lcd.backlight();

    timer.setInterval(100L, sendSensor);

}

void loop() {
   Blynk.run();
  timer.run();
  

}