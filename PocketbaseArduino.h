#ifndef PocketbaseArduino_h
#define PocketbaseArduino_h

#include <Arduino.h>
#include "PocketBase.h" // Assuming you have a PocketBase Arduino library

/**
 * @brief Represents a collection of records in PocketBase.
 *
 * This class provides methods to interact with a specific collection of records in PocketBase.
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
     * @param record The record to retrieve.
     * @return The retrieved record as a String.
     */
    String getOne(const char *record)
    {
        return pb.getOneRecord(collectionName, record);
    }

    /**
     * Creates a single, new record in the Pocketbase collection.
     *
     * @param jsonData The JSON data for the new record.
     * @return True if the record was successfully created, false otherwise.
     */
    bool create(const char *jsonData)
    {
        return pb.addRecord(collectionName, jsonData);
    }

    /**
     * @brief Updates a single, new record in the Pocketbase collection.
     *
     * This function updates a record in the Pocketbase collection with the provided JSON data.
     *
     * @param jsonData The JSON data to update the record with.
     * @return True if the record was successfully updated, false otherwise.
     */
    bool update(const char *jsonData)
    {
        return pb.updateRecord(collectionName, jsonData);
    }

    /**
     * @brief Deletes a single, new record in the Pocketbase collection.
     *
     * This function deletes a record in the Pocketbase collection with the provided JSON data.
     *
     * @param jsonData The JSON data to update the record with.
     * @return True if the record was successfully updated, false otherwise.
     */
    bool delete(const char *jsonData)
    {
        return pb.deleteRecord(collectionName, jsonData);
    }

private:
    PocketBase &pb;             ///< Reference to the associated PocketBase object.
    const char *collectionName; ///< The name of the collection.
};

class PocketbaseArduino
{
public:
    PocketbaseArduino(const char *BASE_URL)
        : pb(BASE_URL) {}

    PocketbaseCollection collection(const char *collectionName)
    {
        return PocketbaseCollection(pb, collectionName);
    }

private:
    PocketBase pb;
};

#endif
