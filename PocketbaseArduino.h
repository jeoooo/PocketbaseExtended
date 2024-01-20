#ifndef PocketbaseArduino_h
#define PocketbaseArduino_h

#include <Arduino.h>
#include "PocketBaseArduino.h"

class PocketbaseArduino
{
public:
    PocketbaseArduino(const char *BASE_URL);

    PocketbaseArduinoCollection collection(const char *collectionName);

private:
    String GETRequest(const String &url);
};

class PocketbaseArduinoCollection
{
public:
    PocketbaseArduinoCollection(PocketbaseArduino &parent, const char *collectionName);

    const String getOne(const char *recordId, const char *expand, const char *fields);

private:
    const char *collectionName;
    PocketbaseArduinoCollection &PocketbaseArduino;
}

#endif
