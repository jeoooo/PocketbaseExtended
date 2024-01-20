// PocketbaseArduino.cpp

#include "PocketbaseArduino.h"
#include <ESP8266HTTPClient.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <BearSSLHelpers.h>

PocketbaseArduino::PocketbaseArduino(const char *baseUrl)
{
    // Initialize base_url with the provided URL
    base_url = baseUrl;

    // Ensure there is no trailing "/"
    if (base_url.endsWith("/"))
    {
        base_url.remove(base_url.length() - 1); // Remove the trailing "/"
    }

    // Append "/api/" to the base URL
    base_url += "/api/";

    // Initialize current_endpoint
    current_endpoint = base_url;
}

String PocketbaseArduino::httpGETRequest(const char *endpoint)
{

    Serial.print("[HTTP] Full URL: ");
    Serial.println(endpoint);

    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    if (http.begin(endpoint))
    {
        Serial.print("[HTTP] GET...\n");
        int httpCode = http.GET();
        if (httpCode > 0)
        {
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
            {
                String payload = http.getString();
                Serial.println(payload);
                http.end();
                return payload;
            }
        }
        else
        {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    }
    else
    {
        Serial.printf("[HTTP] Unable to connect\n");
    }
    return ""; // Return an empty string on failure
}

String PocketbaseArduino::httpsGETRequest(const char *endpoint)
{
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;

    Serial.print("[HTTPS] Full URL: ");
    Serial.println(endpoint);

    if (https.begin(*client, endpoint))
    {
        Serial.print("[HTTPS] GET...\n");
        int httpCode = https.GET();
        if (httpCode > 0)
        {
            Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
            {
                String payload = https.getString();
                Serial.println(payload);
                https.end();
                return payload;
            }
        }
        else
        {
            Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
        https.end();
    }
    else
    {
        Serial.printf("[HTTPS] Unable to connect\n");
    }
    return ""; // Return an empty string on failure
}

PocketbaseArduino &PocketbaseArduino::collection(const char *collection)
{
    current_endpoint = "collections/" + String(collection) + "/";
    return *this;
}

String PocketbaseArduino::getOne(const char *recordId)
{
    String fullEndpoint;

    if (base_url.startsWith("https://"))
    {
        // Use HTTPS if base URL starts with "https://"
        fullEndpoint = base_url + String(current_endpoint) + "records/" + recordId;
        return httpsGETRequest(fullEndpoint.c_str());
    }
    else
    {
        // Use HTTP for other cases
        fullEndpoint = base_url + String(current_endpoint) + "records/" + recordId;
        return httpGETRequest(fullEndpoint.c_str());
    }
}
