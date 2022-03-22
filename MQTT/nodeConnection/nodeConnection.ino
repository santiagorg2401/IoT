#include <SPI.h>
#include <Bridge.h>
#include <BridgeClient.h>
#include <PubSubClient.h>

#define mqttUser "77adbc40-a4a0-11ec-8da3-474359af83d7"
#define mqttPass "c0cfe6ac5caf9a3407c77dcff10f20b732f5757b"
#define mqttPort 1883
char mqttBroker[] = "mqtt.mydevices.com";
char mqttClientId[] = "c253f010-a4a6-11ec-8c44-371df593ba58";
char inTopic0[] = "v1/77adbc40-a4a0-11ec-8da3-474359af83d7/things/c253f010-a4a6-11ec-8c44-371df593ba58/data/0";
char inTopic1[] = "v1/77adbc40-a4a0-11ec-8da3-474359af83d7/things/c253f010-a4a6-11ec-8c44-371df593ba58/data/1";
char dato0[]="value0=";
char dato1[]="value1=";

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
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
      int sensor0 = analogRead(A0);
      char datojson0[50];
      sprintf(datojson0, "%s %i", dato0, sensor0);
      Serial.println(datojson0);
      client.publish(inTopic0,datojson0);

      int sensor1 = analogRead(A1)*2;
      char datojson1[50];
      sprintf(datojson1, "%s %i", dato1, sensor1);
      Serial.println(datojson1);
      client.publish(inTopic1,datojson1);
      
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
  Serial.begin(57600);
  Bridge.begin();
  client.setServer( mqttBroker, mqttPort );
  client.setCallback( callback );
  Serial.println("Setup done");
  delay(1500);
}
void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
