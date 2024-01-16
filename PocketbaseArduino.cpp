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