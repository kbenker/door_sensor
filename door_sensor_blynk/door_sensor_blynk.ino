#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "creds.h" // includes key and wifi settings

const char auth[] = KEY;

// Network settings
const char ssid[] = SSID;
const char pass[] = PASS;

// Blynk cloud server
const char* host = "blynk-cloud.com";
unsigned int port = 8080;

WiFiClient client;

int pin = 4;

bool current = 0;
bool previous = 1;
unsigned long startTime;
unsigned long totalTime = 0;

void setup(void)
{
  pinMode(pin, INPUT_PULLUP);

  // Start Serial
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  switchState();
  delay(1000);
}

void switchState(){
  current = digitalRead(pin);
  unsigned long curTime = millis();
  if (current != previous) {
    startTime = curTime;
    previous = current;
    if (current == LOW) {
      Serial.print("Closed after ");
      Serial.print(totalTime);
      Serial.println(" seconds");
      Blynk.virtualWrite(V2, "Closed");
    }
    else {
      Serial.print("Open after ");
      Serial.print(totalTime);
      Serial.print(" seconds");
      Blynk.virtualWrite(V2, "Open");
    } 
  }
  totalTime = (curTime - startTime) / 1000;
  Blynk.virtualWrite(V3, totalTime);
}
