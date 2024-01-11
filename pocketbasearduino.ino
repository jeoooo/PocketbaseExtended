#include <ESP8266WiFi.h>
#include "PocketbaseArduino.h"

const char *ssid = "your_wifi_ssid";
const char *password = "your_wifi_password";

const char *BASE_URL = "http://127.0.0.1:8090";

PocketbaseArduino pocketBase(BASE_URL);

void setup()
{
  Serial.begin(9600);

  connectToWiFi();

  String record = pocketBase.collection("posts").getOne("record");
  Serial.println("Record: " + record);
}

void loop()
{
  // Your main loop code here
}

void connectToWiFi()
{
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}
