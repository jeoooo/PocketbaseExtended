#ifndef PocketbaseArduino_h
#define PocketbaseArduino_h

#include <Arduino.h>
#include "PocketBaseArduino.h"

class PocketbaseArduino
{
public:
    PocketbaseArduino(const char *BASE_URL) : pb(BASE_URL) {}

    PocketbaseCollection collection(const char *collectionName);

private:
    PocketBase pb;

    String GETRequest(const String &url);
};

class PocketbaseArduinoException : public std::exception
{
public:
    PocketbaseArduinoException(const int &message) : message(std::to_string(message)) {}

    const char *what() const noexcept override
    {
        return whatMessage.c_str();
    }

private:
    std::string message;
};

class PocketbaseCollection
{
public:
    const String getList(
        unsigned int page = 1,
        unsigned int perPage = 30,
        const char *sort = nullptr,
        const char *filter = nullptr,
        const char *expand = nullptr,
        const char *fields = nullptr,
        bool skipTotal = true);

    const String getFullList(
        unsigned int page = 1,
        unsigned int perPage = 30,
        const char *sort = nullptr,
        const char *filter = nullptr,
        const char *expand = nullptr,
        const char *fields = nullptr,
        bool skipTotal = true);

    const String getOne(
        const char *recordId,
        const char *expand = nullptr,
        const char *fields = nullptr);

    const String create(
        const char *jsonData,
        const char *id = nullptr,
        const char *expand = nullptr,
        const char *fields = nullptr);

    const String update(const char *jsonData, const char *recordId);

    const String deleteRecord(const char *jsonData, const char *recordId, const char *filesToDelete[] = nullptr);

private:
    PocketBase &pb;
    const char *collectionName;
}

#endif
