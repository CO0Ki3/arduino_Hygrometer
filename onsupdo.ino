#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#include <DS1302.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C led(0x27, 16, 2);

DHT dht(1, DHT22);

#define DHT_ 6

Adafruit_NeoPixel ring = Adafruit_NeoPixel(0, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(3, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(6, PIN, NEO_GRB + NEO_KHZ800);

#define SCK_PIN 4
#define IO_PIN 3
#define RST_PIN 2

DS1302 rtc(RST_PIN, IO_PIN, SCK_PIN);

void begin() {
  Serial.begin(9600);
  dht.begin();
  ring.begin();
  ring.show();
  pixels.setBrightness(45);
  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setTime(/*시간*/);
  rtc.setDate(/*날짜*/);
  lcd.init();
}

void loop() {
  float hum = dht.readHumidity();
  float tmp = dht.readTemperture();
  if (isnan(tmp) || isnan(hum)) {
    Serial.println("Reading error..");
    lcd.print("ERROR");
    }
    else {
      Serial.print("Temperature: ");
      Serial.print(tmp);
      Serial.print(" C\t");
      Serial.print("Humidity: ");
      Serial.print(hum);
      Serial.println(" %");
      lcd.print(tmp);
      lcd.print(" C\n");
      lcd.print(hum);
      lcd.print(" %");
      }
      if(tmp < 25) {
        pixels.setPixelColor(0, pixels.Color(0, 0, 255));
        pixels.setPixelColor(1, pixels.Color(0, 0, 255));
        pixels.setPixelColor(2, pixels.Color(0, 0, 255));
      }
      else if(tmp >= 25) {
        pixels.setPixelColor(0, pixels.Color(255, 0, 0));
        pixels.setPixelColor(1, pixels.Color(255, 0, 0));
        pixels.setPixelColor(2, pixels.Color(255, 0, 0));
      }
      if(hum < 40) {
        pixels.setPixelColor(3, pixels.Color(255, 225, 0));
        pixels.setPixelColor(4, pixels.Color(255, 255, 0));
        pixels.setPixelColor(5, pixels.Color(255, 255, 0));
      }
      else if (hum >= 40) {
        pixels.setPixelColor(3, pixels.Color(0, 255, 0));
        pixels.setPixelColor(4, pixels.Color(0, 255, 0));
        pixels.setPixelColor(5, pixels.Color(0, 255, 0));
      }
      pixels.setPixelColor(6, pixels.Color(255, 255, 255));
      while(1)
      {
        Serial.print(rtc.getDateStr());
        Serial.println(rtc.getTimeStr());
        lcd.print(rtc.setTime);
        lcd.print(rtc.setDate);
      }
      if(setTime > 8:00) {
        lcd.backlight();
        pixels.Brightness(100);
      }
      else if(setTime <= 8:00 || setTime >= 18:00) {
        lcd.backlight();
        pixels.Brightness(45);
      }
      pixels.setPixelColor(6, pixels.Color(255, 255, 255));
      pixels.show();
}
