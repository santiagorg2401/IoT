#include <TimeLib.h>
#include <BH1750.h>
#include <SPI.h>
#include <Bridge.h>
#include <BridgeClient.h>
#include <PubSubClient.h>

#define mqttUser ""
#define mqttPass ""
#define mqttPort 1883
char mqttBroker[] = "192.168.163.19";
char mqttClientId[] = "ArduinoYun01";
char inTopic0[] = "topico1";
char dato0[] = "{\"temperatura\" : ";

BH1750 lightMeter;
int MySolarGrid_ID = 01;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
BridgeClient BClient;
PubSubClient client(BClient);
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqttClientId, mqttUser, mqttPass)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      float sensor = analogRead(A0);
      float volt = (12 * sensor) / (1023);
      float lux = lightMeter.readLightLevel();
      String date = "\"" + String(day()) + "/" + String(month()) + "/" + String(year()) + " " + String(hour()) + ":" + String(minute()) + "\"";
      String jsonData = "{\"MySolarGridID\" : " + String(MySolarGrid_ID) + ", \"BatteryVoltaje\" : " + String(volt) + ", \"LightLevel\" : " + String(lux) + ", \"date\" : " + date + "}";

      Serial.println(jsonData);
      client.publish(inTopic0, jsonData.c_str());

      client.disconnect();
      delay(5000);
      // ... and resubscribe
      //client.subscribe("topic2");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void setup()
{
  Serial.begin(9600);
  Bridge.begin();
  client.setServer( mqttBroker, mqttPort );
  client.setCallback( callback );
  Serial.println("Setup done");
  delay(1500);
  
  setTime(16,22,00,29,04,2022); 

  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test"));
}
void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
