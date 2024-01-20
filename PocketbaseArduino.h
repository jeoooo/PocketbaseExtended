// PocketbaseArduino.h

#ifndef PocketbaseArduino_h
#define PocketbaseArduino_h

#include "Arduino.h"
#include <ESP8266HTTPClient.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <BearSSLHelpers.h>

class PocketbaseArduino
{
public:
    PocketbaseArduino(const char *baseUrl); // Constructor
    String httpGETRequest(const char *endpoint);
    String httpsGETRequest(const char *endpoint);

    // Methods to build collection and record URLs
    PocketbaseArduino &collection(const char *collection);
    String getOne(const char *recordId);

private:
    String base_url;
    String current_endpoint;
};

#endif
