#include <HttpClient.h>

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  int temp = analogRead(A0);
  int hum = analogRead(A1);
  String json1 = "{\"temperatura\" : " + String(temp) + ", \"humedad\" : " + String(hum) + "}";
  Serial.println("dato a enviar: " + json1);
  HttpClient cliente;
  cliente.setHeader("Content-Type: application/json");
  String httpDestination = "http://things.ubidots.com/api/v1.6/devices/arduino01/?token=BBFF-yB97DF1ZzLZbBnUR0RsVPbzqKEA3iH";
  String httpBody = json1;
  cliente.post(httpDestination, httpBody);
  Serial.println("enviando:");
  delay(5000);
  Serial.flush();
}
