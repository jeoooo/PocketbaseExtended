// PocketbaseArduino.cpp

#include "PocketbaseArduino.h"
// #include <ESP8266HTTPClient.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <BearSSLHelpers.h>

#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#endif

// ! must be removed in future updates
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

// ! must be removed in future updates
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
            // if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
            if (httpCode)
            {
                String payload = http.getString();
                // print request contents (must be removed)
                Serial.println(payload);
                http.end();
                return payload;
            }
        }
        // else
        // {
        //     Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        // }
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
            // if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
            if (httpCode)
            {
                String payload = https.getString();
                // print request contents (must be removed)
                Serial.println(payload);
                https.end();
                return payload;
            }
        }
        // else
        // {
        //     Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        // }
        https.end();
    }
    else
    {
        Serial.printf("[HTTPS] Unable to connect\n");
    }
    // TODO: improve return value in case failure happens
    return ""; // Return an empty string on failure
}

String performRequest(const char *endpoint)
{

#if defined(ESP32)
    std::unique_ptr<WiFiClientSecure> client(new WiFiClientSecure);
    client->setInsecure();
    if (strncmp(url, "https", 5) == 0)
    {
        http.begin(*client, url);
    }
    else
    {
        http.begin(url);
    }
#elif defined(ESP8266)
    if (strncmp(endpoint, "https", 5) == 0)
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
                // if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
                if (httpCode)
                {
                    String payload = https.getString();
                    // print request contents (must be removed)
                    Serial.println(payload);
                    https.end();
                    return payload;
                }
            }
            // else
            // {
            //     Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
            // }
            https.end();
        }
        else
        {
            Serial.printf("[HTTPS] Unable to connect\n");
        }
        // TODO: improve return value in case failure happens
        return ""; // Return an empty string on failure
    }
    else
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
                // if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
                if (httpCode)
                {
                    String payload = http.getString();
                    Serial.println(payload);
                    http.end();
                    return payload;
                }
            }
            // else
            // {
            //     Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            // }
            http.end();
        }
        else
        {
            Serial.printf("[HTTP] Unable to connect\n");
        }
        return ""; // Return an empty string on failure
    }
#endif
}

PocketbaseArduino &PocketbaseArduino::collection(const char *collection)
{
    current_endpoint = "collections/" + String(collection) + "/";
    return *this;
}

/**
 *
 *
 * @brief `getOne()` - Fetches a single record from a Pocketbase collection
 *
 * @param recordId  The ID of the record to view.
 *
 * @param expand    (Optional) Auto expand record relations. Ex.:?expand=relField1,relField2.subRelField Supports up to 6-levels depth nested relations expansion.
 *                  The expanded relations will be appended to the record under the expand property (eg. "expand": {"relField1": {...}, ...}).
 *                  Only the relations to which the request user has permissions to view will be expanded.
 *
 * @param fields    (Optional) Comma separated string of the fields to return in the JSON response (by default returns all fields). Ex.: ?fields=*,expand.relField.name
 *                  * targets all keys from the specific depth level. In addition, the following field modifiers are also supported:
 *                  :excerpt(maxLength, withEllipsis?)
 *                  Returns a short plain text version of the field string value.
 *                  Ex.: ` ?fields=*,description:excerpt(200,true)`
 *
 *                  For more information, see: https://pocketbase.io/docs
 */
String PocketbaseArduino::getOne(const char *recordId, const char *expand /* = nullptr */, const char *fields /* = nullptr */)
{
    String fullEndpoint;

    if (base_url.startsWith("https://"))
    {
        // Use HTTPS if base URL starts with "https://"
        fullEndpoint = base_url + String(current_endpoint) + "records/" + recordId;
    }
    else
    {
        // Use HTTP for other cases
        fullEndpoint = base_url + String(current_endpoint) + "records/" + recordId;
    }

    // Append the expand parameter if provided
    if (expand != nullptr && strlen(expand) > 0)
    {
        fullEndpoint += "?expand=" + String(expand);
    }

    // Append the fields parameter if provided
    if (fields != nullptr && strlen(fields) > 0)
    {
        // Check if there's already a query string
        if (fullEndpoint.indexOf('?') == -1)
        {
            fullEndpoint += "?";
        }
        else
        {
            fullEndpoint += "&";
        }

        fullEndpoint += "fields=" + String(fields);
    }

    if (base_url.startsWith("https://"))
    {

        return performRequest(fullEndpoint.c_str());
    }
    else
    {
        return performRequest(fullEndpoint.c_str());
    }
}

String PocketbaseArduino::getList(
    const char *page /* = nullptr */,
    const char *perPage /* = nullptr */,
    const char *sort /* = nullptr */,
    const char *filter /* = nullptr */,
    const char *expand /* = nullptr */,
    const char *fields /* = nullptr */,
    const char *skipTotal /* = nullptr */)
{
    String fullEndpoint;

    if (base_url.startsWith("https://"))
    {
        // Use HTTPS if base URL starts with "https://"
        fullEndpoint = base_url + String(current_endpoint) + "records/";
    }
    else
    {
        // Use HTTP for other cases
        fullEndpoint = base_url + String(current_endpoint) + "records/";
    }

    if (page != nullptr && strlen(page) > 0)
    {

        if (fullEndpoint.indexOf('?') == -1)
        {
            fullEndpoint += "?";
        }
        else
        {
            fullEndpoint += "&";
        }

        fullEndpoint += "page=" + String(page);
    }

    if (perPage != nullptr && strlen(perPage) > 0)
    {
        if (fullEndpoint.indexOf('?') == -1)
        {
            fullEndpoint += "?";
        }
        else
        {
            fullEndpoint += "&";
        }

        fullEndpoint += "perPage=" + String(perPage);
    }

    if (sort != nullptr && strlen(sort) > 0)
    {
        if (fullEndpoint.indexOf('?') == -1)
        {
            fullEndpoint += "?";
        }
        else
        {
            fullEndpoint += "&";
        }

        fullEndpoint += "perPage=" + String(sort);
    }

    if (filter != nullptr && strlen(filter) > 0)
    {
        if (fullEndpoint.indexOf('?') == -1)
        {
            fullEndpoint += "?";
        }
        else
        {
            fullEndpoint += "&";
        }

        fullEndpoint += "perPage=" + String(filter);
    }

    if (skipTotal != nullptr && strlen(skipTotal) > 0)
    {
        if (fullEndpoint.indexOf('?') == -1)
        {
            fullEndpoint += "?";
        }
        else
        {
            fullEndpoint += "&";
        }

        fullEndpoint += "perPage=" + String(skipTotal);
    }

    if (expand != nullptr && strlen(expand) > 0)
    {
        fullEndpoint += "?expand=" + String(expand);
    }

    if (fields != nullptr && strlen(fields) > 0)
    {

        if (fullEndpoint.indexOf('?') == -1)
        {
            fullEndpoint += "?";
        }
        else
        {
            fullEndpoint += "&";
        }

        fullEndpoint += "fields=" + String(fields);
    }

    if (base_url.startsWith("https://"))
    {
        return performRequest(fullEndpoint.c_str());
    }
    else
    {
        return performRequest(fullEndpoint.c_str());
    }
}
