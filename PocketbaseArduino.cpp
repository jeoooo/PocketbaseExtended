/**
 *
 * PocketbaseArduino
 *
 * ESP8266/ESP32 Library
 * for Pocketbase
 *
 * Created Jan 16, 2024
 * By jeoooo
 *
 * Github Repository:
 * https://github.com/jeoooo/PocketbaseArduino
 *
 */

#include "PocketbaseArduino.h"
#include <ESP8266HTTPClient.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <BearSSLHelpers.h>

/**
 *
 * * *************************************************************************************************************
 * *                                               IMPORTANT:                                                    *
 * *                                                                                                             *
 * * You need at least two files for a library:                                                                  *
 * *                                                                                                             *
 * * 1. A header file (w/ the extension .h) and the source file (w/ extension .cpp).                             *
 * *    The header file has definitions for the library: basically a listing of everything that's inside;        *
 * *                                                                                                             *
 * * 2. source file - while the source file has the actual code.                                                 *
 * *                                                                                                             *
 * * source: https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide                          *
 * *                                                                                                             *
 * * *************************************************************************************************************
 *
 */

/**
 * Performs an HTTP GET request to the specified URL.
 *
 * @param url The URL to send the GET request to.
 */
void httpGETRequest(const char *url)
{
    // create an HTTPClient instance
    HTTPClient http;

    // Initializing an HTTP communication
    Serial.print("[HTTP] begin...\n");
    if (http.begin(url))
    { // HTTP
        Serial.print("[HTTP] GET...\n");

        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0)
        {
            // HTTP header has been sent, and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
            {
                String payload = http.getString();
                Serial.println(payload);
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
}

/**
 * Performs an HTTPS GET request to the specified URL.
 *
 * @param url The URL to send the GET request to.
 */
void httpsGETRequest(const char *url)
{
    // create a WiFiClientSecure instance
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

    // Ignore SSL certificate validation
    client->setInsecure();

    // create an HTTPClient instance for HTTPS
    HTTPClient https;

    // Initializing an HTTPS communication using the secure client
    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, url))
    { // HTTPS
        Serial.print("[HTTPS] GET...\n");

        // start connection and send HTTP header
        int httpCode = https.GET();

        // httpCode will be negative on error
        if (httpCode > 0)
        {
            // HTTP header has been sent, and Server response header has been handled
            Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
            {
                String payload = https.getString();
                Serial.println(payload);
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
}

const String PocketbaseCollection::getFullList(
    unsigned int page = 1,
    unsigned int perPage = 30,
    const char *sort = nullptr,
    const char *filter = nullptr,
    const char *expand = nullptr,
    const char *fields = nullptr,
    bool skipTotal = true)
{
    // TODO: Implement the function here
}

const String PocketbaseCollection::getList(
    unsigned int page = 1,
    unsigned int perPage = 30,
    const char *sort = nullptr,
    const char *filter = nullptr,
    const char *expand = nullptr,
    const char *fields = nullptr,
    bool skipTotal = true)
{
    // TODO: Implement the function here
}

const String PocketbaseCollection::getOne(const char *recordId, const char *expand = nullptr, const char *fields = nullptr)
{
    // TODO: Implement the function here
}

const String PocketbaseCollection::create(const char *jsonData, const char *id = nullptr, const char *expand = nullptr, const char *fields = nullptr)
{
    // TODO: Implement the function here
}

const String PocketbaseCollection::update(const char *jsonData, const char *recordId)
{
    // TODO: Implement the function here
}

const String PocketbaseCollection::deleteRecord(const char *jsonData, const char *recordId, const char *filesToDelete[] = nullptr)
{
    // TODO: Implement the function here
}