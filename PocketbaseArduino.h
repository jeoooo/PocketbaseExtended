#ifndef PocketbaseArduino_h
#define PocketbaseArduino_h

#include <Arduino.h>
#include "PocketBase.h" // Assuming you have a PocketBase Arduino library

/**
 * @class PocketbaseCollection
 * @brief Represents a collection of records in PocketBase.
 *
 * This class provides methods to interact with a specific collection of records in PocketBase.
 * It allows retrieving, creating, updating, and deleting records in the collection.
 */
class PocketbaseCollection
    /**
     * @brief Represents a collection of records in the PocketBase database.
     *
     * This class provides methods to interact with a specific collection in the PocketBase database.
     * It allows retrieving, creating, updating, and deleting records in the collection.
     */
    class PocketbaseCollection
{
public:
    /**
     * @brief Constructs a PocketbaseCollection object.
     *
     * @param pb The PocketBase object to associate with the collection.
     * @param collectionName The name of the collection.
     */
    PocketbaseCollection(PocketBase &pb, const char *collectionName)
        : pb(pb), collectionName(collectionName) {}

    /**
     * @brief Retrieves a single record from the collection.
     *
     * @param record The identifier of the record to retrieve.
     * @return The JSON representation of the retrieved record.
     */
    const String getOne(const char *record);

    /**
     * @brief Creates a new record in the collection.
     *
     * @param jsonData The JSON data representing the new record.
     * @param fieldName The name of the field associated with the file. (optional)
     * @param fileName The name of the file to upload. (optional)
     * @param fileStream The stream containing the file data. (optional)
     * @return The JSON representation of the created record.
     */
    const String create(const char *jsonData, const char *fieldName = nullptr, const char *fileName = nullptr, Stream *fileStream = nullptr);

    /**
     * @brief Updates an existing record in the collection.
     *
     * @param jsonData The JSON data representing the updated record.
     * @return The JSON representation of the updated record.
     */
    const String update(const char *jsonData);

    /**
     * @brief Deletes a record from the collection and optionally deletes associated files.
     *
     * @param recordId The ID of the record to delete.
     * @param filesToDelete An optional array of filenames to delete from file fields.
     * @return The JSON representation of the deleted record.
     */
    const String deleteRecord(const char *recordId, const char *filesToDelete[] = nullptr);

private:
    PocketBase &pb;             // Reference to the PocketBase object associated with the collection
    const char *collectionName; // The name of the collection
};

/**
 * @brief Represents a Pocketbase Arduino client.
 *
 * This class provides a convenient way to interact with the Pocketbase API using an Arduino device.
 * It allows you to perform operations such as creating collections and accessing data within those collections.
 */
class PocketbaseArduino
{
public:
    /**
     * @brief Constructs a PocketbaseArduino object with the specified base URL.
     *
     * @param BASE_URL The base URL of the Pocketbase API.
     */
    PocketbaseArduino(const char *BASE_URL)
        : pb(BASE_URL) {}

    /**
     * @brief Returns a PocketbaseCollection object for the specified collection name.
     *
     * @param collectionName The name of the collection.
     * @return PocketbaseCollection The PocketbaseCollection object for the specified collection.
     */
    PocketbaseCollection collection(const char *collectionName)
    {
        return PocketbaseCollection(pb, collectionName);
    }

private:
    PocketBase pb;
};

#endif
