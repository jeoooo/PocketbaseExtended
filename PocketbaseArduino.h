/**
 * PocketbaseArduino.h - Arduino Wrapper Library for Pocketbase
 * Created by jeooo, January 11, 2024
 * MIT License
 *
 */
#ifndef PocketbaseArduino_h
#define PocketbaseArduino_h

#include <Arduino.h>
#include "PocketBase.h" // Assuming you have a PocketBase Arduino library

/**
 *
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
 *
 */

/**
 * @brief The PocketbaseArduino class represents an Arduino library for interacting with PocketBase.
 *
 * This class provides methods for creating a PocketbaseCollection object and accessing the PocketBase API.
 */
class PocketbaseArduino
{
public:
    PocketbaseArduino(const char *BASE_URL) : pb(BASE_URL);

    PocketbaseCollection collection(const char *collectionName);

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
    PocketbaseArduinoException(const std::string &message) : message(message);

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

    /**
     * @brief Fetchesa paginated records listing
     *
     * This function retrieves a paginated record from a Pocketbase collection
     * It allows optional parameters for page, perPage, sorting, filtering, expanding, querying specific fields, and skipTotal
     *
     * @param page      (Optional) The page (aka. offset) of the paginated list (default to 1).
     * @param perPage   (Optional) The max returned records per page (default to 30).
     * @param sort      (Optional) Specify the ORDER BY fields.
     * @param filter    (Optional) Filter expression to filter/search the returned records list (in addition to the collection's listRule)
     * @param expand    (Optional) Auto expand record relations.
     * @param fields    (Optional) Comma separated string of the fields to return in the JSON response (by default returns all fields).
     * @param skipTotal (Optional) If it is set the total counts query will be skipped and the response fields totalItems and totalPages will have -1 value.
     *                  This could drastically speed up the search queries when the total counters are not needed or cursor based pagination is used.
     *                  For optimization purposes, it is set by default for the getFirstListItem() and getFullList() SDKs methods.
     *
     * @return          A JSON String representing the paginated record from a Pocketbase collection
     */
    const String PocketbaseCollection::getList(
        unsigned int page = 1,
        unsigned int perPage = 30,
        const char *sort = nullptr,
        const char *filter = nullptr,
        const char *expand = nullptr,
        const char *fields = nullptr,
        bool skipTotal = true);

    /**
     * @brief Fetches all records at once from a Pocketbase Collection
     *
     * This function retrieves a paginated record from a Pocketbase collection
     * It allows optional parameters for page, perPage, sorting, filtering, expanding, querying specific fields, and skipTotal
     *
     * @param page      (Optional) The page (aka. offset) of the paginated list (default to 1).
     * @param perPage   (Optional) The max returned records per page (default to 30).
     * @param sort      (Optional) Specify the ORDER BY fields.
     * @param filter    (Optional) Filter expression to filter/search the returned records list (in addition to the collection's listRule)
     * @param expand    (Optional) Auto expand record relations.
     * @param fields    (Optional) Comma separated string of the fields to return in the JSON response (by default returns all fields).
     * @param skipTotal (Optional) If it is set the total counts query will be skipped and the response fields totalItems and totalPages will have -1 value.
     *                  This could drastically speed up the search queries when the total counters are not needed or cursor based pagination is used.
     *                  For optimization purposes, it is set by default for the getFirstListItem() and getFullList() SDKs methods.
     *
     * @return          A JSON String representing the paginated record from a Pocketbase collection
     */
    const String PocketbaseCollection::getFullList(
        unsigned int page = 1,
        unsigned int perPage = 30,
        const char *sort = nullptr,
        const char *filter = nullptr,
        const char *expand = nullptr,
        const char *fields = nullptr,
        bool skipTotal = true);

    /**
     * @brief Fetches a single record from a Pocketbase collection.
     *
     * This function retrieves a single record from a Pocketbase collection based on the provided record ID.
     * It allows optional parameters for expanding related fields and selecting specific fields to include in the response.
     *
     * @param recordId  The ID of the record to fetch.
     * @param expand    (Optional) A string specifying related fields to expand in the response.
     * @param fields    (Optional) A string specifying the fields to include in the response.
     *
     * @return          The fetched record as a String object.
     */
    const String getOne(
        const char *recordId,
        const char *expand = nullptr,
        const char *fields = nullptr);

    /**
     * @brief Creates a single, new record in the Pocketbase collection.
     *
     * @param jsonData      The JSON data for the new record.
     * @param id            (Optional) The ID of the record. If not set, it will be auto-generated by Pocketbase.
     * @param expand        (Optional) A string specifying related fields to expand in the response.
     * @param fields        (Optional) A string specifying the fields to include in the response.
     *
     * @return              A JSON string representing the created record if successful, an empty string otherwise.
     */
    const String create(
        const char *jsonData,
        const char *id = nullptr,
        const char *expand = nullptr,
        const char *fields = nullptr);

    // TODO: REFACTOR
    const String update(const char *jsonData);

    // TODO: REFACTOR
    const String deleteRecord(const char *recordId, const char *filesToDelete[] = nullptr);

private:
    PocketBase &pb;             // Reference to the PocketBase object associated with the collection
    const char *collectionName; // The name of the collection
};

#endif
