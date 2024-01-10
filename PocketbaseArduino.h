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
