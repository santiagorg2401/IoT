// Import required libraries.
#include <TimeLib.h>
#include <BH1750.h>
#include <Wire.h>

// Global variables.
BH1750 lightMeter;
int MySolarGrid_ID = 01;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  setTime(12,35,0,19,02,2022);
}

void loop() {
  // Adquire sensor measurements.
  float sensor = analogRead(A0);
  float lux = lightMeter.readLightLevel();

  // Scale voltaje readings.
  float volt = (12 * sensor)/(1023);

  // Get date and time.
  String date = getDate();
  String Time = getTime();

  // Code json format data.
  String jsonData = "{\"MySolarGrid ID\" : " + String(MySolarGrid_ID) + ", \"Battery voltaje\" : " + String(volt) + ", \"Light level\" : " + String(lux) + ", \"Date\" : " + String(date) + ", \"Time\" : " + String(Time) + "}";

  // Send json.
  Serial.println(jsonData);
  delay(1000);
}

// Methods.
String getDate() {
  String date = "\"" + String(day()) + "/" + String(month()) + "/" + String(year()) + "\"";
  return date;
}

String getTime() {
  String Time = "\"" + String(hour()) + ":" + String(minute()) + ":" + String(second()) + "\"";
  return Time;
}
