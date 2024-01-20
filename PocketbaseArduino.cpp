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
 * @return The payload received from the server.
 */
String httpGETRequest(const char *url)
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

/**
 * Performs an HTTPS GET request to the specified URL.
 *
 * @param url The URL to send the GET request to.
 * @return The payload received from the server.
 */
String httpsGETRequest(const char *url)
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

    return ""; // Return an empty string on failure, MUST BE CHANGED
}

/**
 * Fetch a single record from a Pocketbase Collection.
 *
 * @param recordId
 * The Id of the Pocketbase record to be fetched.
 * @param expand
 * (Optional) Expand the record relation fields directly in the returned response without making additional requests.
 * @param fields
 * (Optional) Retrieve specific fields from a Pocketbase Collection
 * @param skipTotal
 * (Optional) If it is set the total counts query will be skipped and the response fields totalItems and totalPages will have -1 value.
 * This could drastically speed up the search queries when the total counters are not needed or cursor based pagination is used.
 *
 *
 * For more info about Pocketbase, see: https://pocketbase.io/docs
 * @return The payload received from the server.
 */
const String PocketbaseCollection::getOne(const char *recordId, const char *expand, const char *fields, bool skipTotal)
{
    String url = PocketbaseArduino.baseUrl + "/api/collections/" + collectionName + "/records/" + recordId;

    // Add optional query parameters if provided
    if (expand != nullptr || fields != nullptr || skipTotal)
    {
        url += "?";

        if (expand != nullptr)
        {
            url += "expand=" + String(expand);
            if (fields != nullptr || skipTotal)
            {
                url += "&";
            }
        }

        if (fields != nullptr)
        {
            url += "fields=" + String(fields);
            if (skipTotal)
            {
                url += "&";
            }
        }

        if (skipTotal)
        {
            url += "skipTotal=true";
        }
    }

    String result;
    // Determine the protocol based on the baseUrl
    String protocol = PocketbaseArduino.baseUrl.startsWith("https://") ? "https://" : "http://";

    if (protocol == "http://")
    {
        result = httpGETRequest(url);
    }
    else
    {
        result = httpsGETRequest(url);
    }

    return result;
}
