// PocketbaseExtended.cpp

#include "PocketbaseExtended.h"
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

PocketbaseExtended::PocketbaseExtended(const char *baseUrl)
{
    base_url = baseUrl;

    if (base_url.endsWith("/"))
    {
        base_url.remove(base_url.length() - 1);
    }

    base_url += "/api/";

    current_endpoint = base_url;
    expand_param = "";
    fields_param = "";
}

PocketbaseExtended &PocketbaseExtended::collection(const char *collection)
{
    current_endpoint = "collections/" + String(collection) + "/";
    return *this;
}

String performGETRequest(const char *endpoint)
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
        // TODO: improve return value in case failure happens
        return ""; // Return an empty string on failure
    }
#endif
}

String performDELETERequest(const char *endpoint)
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
            Serial.print("[HTTPS] DELETE...\n");
            int httpCode = https.sendRequest("DELETE");
            if (httpCode > 0)
            {
                Serial.printf("[HTTPS] DELETE... code: %d\n", httpCode);
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
            Serial.print("[HTTP] DELETE...\n");
            int httpCode = http.sendRequest("DELETE");
            if (httpCode > 0)
            {
                Serial.printf("[HTTP] DELETE... code: %d\n", httpCode);
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
        // TODO: improve return value in case failure happens
        return ""; // Return an empty string on failure
    }
#endif
}

String performPOSTRequest(const char *endpoint, const String &requestBody)
{
#if defined(ESP32)
    // ESP32 implementation
    // ...
#elif defined(ESP8266)
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient http;

    Serial.print("[HTTPS] Full URL: ");
    Serial.println(endpoint);

    if (http.begin(*client, endpoint))
    {
        Serial.print("[HTTPS] POST...\n");

        int httpCode = http.POST(requestBody);
        if (httpCode > 0)
        {
            Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
            if (httpCode)
            {
                String payload = http.getString();
                Serial.println(payload);
                http.end();
                return payload;
            }
        }
        else
        {
            Serial.printf("[HTTPS] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
    else
    {
        Serial.printf("[HTTPS] Unable to connect\n");
    }

    // TODO: improve return value in case of failure
    return ""; // Return an empty string on failure
#endif
}

String PocketbaseExtended::getOne(const char *recordId, const char *expand /* = nullptr */, const char *fields /* = nullptr */)
{
    String fullEndpoint = base_url + String(current_endpoint) + "records/" + recordId;

    // Append the expand parameter if provided
    if (expand != nullptr && strlen(expand) > 0)
    {
        fullEndpoint += "?expand=" + String(expand);
    }

    // Append the fields parameter if provided
    if (fields != nullptr && strlen(fields) > 0)
    {
        // Check if there's already a query string
        fullEndpoint += (fullEndpoint.indexOf('?') == -1) ? "?" : "&";
        fullEndpoint += "fields=" + String(fields);
    }

    return performGETRequest(fullEndpoint.c_str());
}

String PocketbaseExtended::getList(
    const char *page /* = nullptr */,
    const char *perPage /* = nullptr */,
    const char *sort /* = nullptr */,
    const char *filter /* = nullptr */,
    const char *skipTotal /* = nullptr */,
    const char *expand /* = nullptr */,
    const char *fields /* = nullptr */)
{
    String fullEndpoint = base_url + String(current_endpoint) + "records/";

    // Append the expand parameter if provided
    if (expand != nullptr && strlen(expand) > 0)
    {
        fullEndpoint += (fullEndpoint.indexOf('?') == -1) ? "?" : "&";
        fullEndpoint += "?expand=" + String(expand);
    }

    // Append the fields parameter if provided
    if (fields != nullptr && strlen(fields) > 0)
    {
        // Check if there's already a query string
        fullEndpoint += (fullEndpoint.indexOf('?') == -1) ? "?" : "&";
        fullEndpoint += "fields=" + String(fields);
    }

    // Append the page parameter if provided
    if (page != nullptr && strlen(page) > 0)
    {
        // Check if there's already a query string
        fullEndpoint += (fullEndpoint.indexOf('?') == -1) ? "?" : "&";
        fullEndpoint += "page=" + String(page);
    }

    // Append the perPage parameter if provided
    if (perPage != nullptr && strlen(perPage) > 0)
    {
        // Check if there's already a query string
        fullEndpoint += (fullEndpoint.indexOf('?') == -1) ? "?" : "&";
        fullEndpoint += "perPage=" + String(perPage);
    }

    // Append the sort parameter if provided
    if (sort != nullptr && strlen(sort) > 0)
    {
        // Check if there's already a query string
        fullEndpoint += (fullEndpoint.indexOf('?') == -1) ? "?" : "&";
        fullEndpoint += "sort=" + String(sort);
    }

    // Append the skipTotal parameter if provided
    if (skipTotal != nullptr && strlen(skipTotal) > 0)
    {
        // Check if there's already a query string
        fullEndpoint += (fullEndpoint.indexOf('?') == -1) ? "?" : "&";
        fullEndpoint += "skipTotal=" + String(skipTotal);
    }

    // Append the filter parameter if provided
    if (filter != nullptr && strlen(filter) > 0)
    {
        // Check if there's already a query string
        fullEndpoint += (fullEndpoint.indexOf('?') == -1) ? "?" : "&";
        fullEndpoint += "skipTotal=" + String(filter);
    }

    return performGETRequest(fullEndpoint.c_str());
}

String PocketbaseExtended::deleteRecord(const char *recordId)
{
    String fullEndpoint = base_url + String(current_endpoint) + "records/" + recordId;

    return performDELETERequest(fullEndpoint.c_str());
}

String PocketbaseExtended::create(const String &requestBody)
{
    // Construct the endpoint based on the current_endpoint
    String fullEndpoint = current_endpoint + "records/";

    // Call performPOSTRequest with the constructed endpoint and provided parameters
    return performPOSTRequest(fullEndpoint.c_str(), requestBody);
}