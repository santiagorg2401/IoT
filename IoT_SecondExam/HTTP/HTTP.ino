#include <BH1750.h>
#include <HttpClient.h>

BH1750 lightMeter;
int MySolarGrid_ID = 01;

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  while (!Serial);

  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test"));
}

void loop() {
  float sensor = analogRead(A0);
  float volt = (12 * sensor) / (1023);
  float lux = lightMeter.readLightLevel();

  String jsonData = "{\"MySolarGrid ID\" : " + String(MySolarGrid_ID) + ", \"Battery voltaje\" : " + String(volt) + ", \"Light level\" : " + String(lux) + "}";
  Serial.println("dato a enviar: " + jsonData);

  HttpClient cliente;
  cliente.setHeader("Content-Type: application/json");
  String httpDestination = "http://192.168.249.19:3000/data";
  String httpBody = jsonData;
  cliente.post(httpDestination, httpBody);
  Serial.println("enviando:");
  delay(1000);
  Serial.flush();
}
