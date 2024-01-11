#ifndef PocketbaseArduino_h
#define PocketbaseArduino_h

#include <Arduino.h>
#include "PocketBase.h" // Assuming you have a PocketBase Arduino library

/**
 * * *************************************************************************************************************
 * *                                         IMPORTANT:                                                          *
 * *                                                                                                             *
 * * You need at least two files for a library:                                                                  *
 * *                                                                                                             *
 * * 1. A header file (w/ the extension .h) and the source file (w/ extension .cpp).                             *
 * *    The header file has definitions for the library: basically a listing of everything that's inside;        *
 * *                                                                                                             *
 * * 2. source file - while the source file has the actual code.                                                 *
 * *                                                                                                             *
 * * source: https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide                          *
 * * *************************************************************************************************************
 ***********************************************/

/**
 * @brief The PocketbaseArduino class represents an Arduino library for interacting with PocketBase.
 *
 * This class provides methods for creating a PocketbaseCollection object and accessing the PocketBase API.
 */
class PocketbaseArduino
{
public:
    PocketbaseArduino(const char *BASE_URL) : pb(BASE_URL) {}

    PocketbaseCollection collection(const char *collectionName) {}

private:
    PocketBase pb;
};

/**
 * @brief Exception class for PocketbaseArduino.
 *
 * This class represents an exception that can be thrown by the PocketbaseArduino library.
 * It inherits from the std::exception class and provides a custom error message.
 */
class PocketbaseArduinoException : public std::exception
{
public:
    /**
     * @brief Constructs a PocketbaseArduinoException object with the given error message.
     *
     * @param message The error message associated with the exception.
     */
    PocketbaseArduinoException(const std::string &message) : message(message) {}

    /**
     * @brief Returns a C-style string describing the exception.
     *
     * This function overrides the what() function of the std::exception class and returns
     * the error message associated with the exception.
     *
     * @return A C-style string describing the exception.
     */
    const char *what() const noexcept override
    {
        return message.c_str();
    }

private:
    std::string message; /**< The error message associated with the exception. */
};

/**
 * @class PocketbaseCollection
 * @brief Represents a collection in the PocketBase database.
 *
 * This class provides methods to interact with a specific collection in the PocketBase database.
 * It allows retrieving, creating, updating, and deleting records in the collection.
 */
class PocketbaseCollection

    class PocketbaseCollection
{
public:
    PocketbaseCollection(PocketBase &pb, const char *collectionName)
        : pb(pb), collectionName(collectionName) {}

    const String getOne(const char *recordId, const char *expand = nullptr, const char *fields = nullptr);

    const String create(const char *jsonData, const char *id = nullptr, const char *expand = nullptr, const char *fields = nullptr);

    // TODO: REFACTOR
    const String update(const char *jsonData);

    // TODO: REFACTOR
    const String deleteRecord(const char *recordId, const char *filesToDelete[] = nullptr);

private:
    PocketBase &pb;             // Reference to the PocketBase object associated with the collection
    const char *collectionName; // The name of the collection
};

#endif
