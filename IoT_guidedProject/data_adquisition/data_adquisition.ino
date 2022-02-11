// Import required libraries.
#include <TimeLib.h>

// Global variables.
int pin_trigger = 5;
int pin_echo = 6;
int node_ID = 2;

long duration;
int distance;

void setup() {
  pinMode(pin_trigger, OUTPUT);
  pinMode(pin_echo, INPUT);
  Serial.begin(9600);
}
void loop() {
  // Adquire sensor measurements.
  int rainSensor = analogRead(A0);
  int flowSensor = analogRead(A1);
  measureDistance();

  // Get date and time.
  String date = getDate();
  String Time = getTime();

  // Code json format data.
  String jsonData = "{\"Node ID\" : " + String(node_ID) + ", \"Rain\" : " + String(rainSensor) + ", \"Flow\" : " + String(flowSensor) + ", \"Depth\" : " + String(distance) + ", \"Date\" : " + String(date) + ", \"Time\" : " + String(Time) + "}";

  // Send json.
  Serial.println(jsonData);
  delay(1000);
}

// Methods.
void measureDistance() {
  // Clears the trigPin
  digitalWrite(pin_trigger, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trigger, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(pin_echo, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2;
}

String getDate() {
  String date = "\"" + String(day()) + "/" + String(month()) + "/" + String(year()) + "\"";
  return date;
}

String getTime() {
  String Time = "\"" + String(hour()) + ":" + String(minute()) + ":" + String(second()) + "\"";
  return Time;
}
