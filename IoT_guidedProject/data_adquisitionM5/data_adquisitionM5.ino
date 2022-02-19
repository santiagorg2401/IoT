// Import required libraries.
#include <TimeLib.h>
#include <M5Stack.h>

// Global variables.
int pin_trigger = 5;
int pin_echo = 2;
int node_ID = 2;

long duration;
int distance;
int i = 0;

void setup() {
  pinMode(pin_trigger, OUTPUT);
  pinMode(pin_echo, INPUT);
  
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);

  setTime(16,55,0,15,02,2022);
}
void loop() {
  // Adquire sensor measurements.
  int rainSensor = analogRead(G35);
  int flowSensor = analogRead(G36);
  measureDistance();

  // Get date and time.
  String date = getDate();
  String Time = getTime();

  // Code json format data.
  String jsonData = "{\"Node ID\" : " + String(node_ID) + ", \"Rain\" : " + String(rainSensor) + ", \"Flow\" : " + String(flowSensor) + ", \"Depth\" : " + String(distance) + ", \"Date\" : " + String(date) + ", \"Time\" : " + String(Time) + "}";

  // Send json.
  //M5.Lcd.print(jsonData);
  delay(70);

  if (i==1){
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    i = 0;
  }else{
    M5.Lcd.print(jsonData);
    i++;
  }
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
