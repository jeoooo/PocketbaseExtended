/*
    pbaseextended.ino

    Example of using the PocketbaseExtended Library for Arduino.

    Created 20 January 2024
    By Jeo Carlo Lubao
    Modified 29 January 2024
    By Jeo Carlo Lubao

    https://github.com/jeoooo/PocketbaseExtended

*/
#include <PocketbaseExtended.h>

// ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// FOR ESP32
// #include <HTTPClient.h>
// #include <WiFi.h>
// #include <WiFiClientSecure.h>

// HTTPS REQUESTS
#include <BearSSLHelpers.h>

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

// Initializing the Pocketbase instance
PocketbaseExtended pb("YOUR_POCKETBASE_BASE_URL");
String record;

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    // Example usage of deleteRecord function
    // deleteRecord("record_id");
    record = pb.collection("collection_name").deleteRecord("record_id");
}

void loop()
{
    // loop code here
}