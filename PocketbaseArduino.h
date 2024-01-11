#ifndef PocketbaseArduino_h
#define PocketbaseArduino_h

#include <Arduino.h>
#include "PocketBase.h" // Assuming you have a PocketBase Arduino library

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
     * @brief Fetches a single record from a Pocketbase collection.
     *
     * This function retrieves a single record from a Pocketbase collection based on the provided record ID.
     * It allows optional parameters for expanding related fields and selecting specific fields to include in the response.
     *
     * @param recordId The ID of the record to fetch.
     * @param expand (Optional) A string specifying related fields to expand in the response.
     * @param fields (Optional) A string specifying the fields to include in the response.
     * @return The fetched record as a String object.
     */
    const String getOne(const char *recordId, const char *expand = nullptr, const char *fields = nullptr)
    {
        try
        {
            // Construct the API endpoint URL with optional expand and fields query parameters
            String apiUrl = pb.getBaseUrl() + "/api/collections/" + collectionName + "/records/" + recordId;

            if (expand != nullptr)
            {
                apiUrl += "?expand=" + String(expand);
                if (fields != nullptr)
                {
                    apiUrl += "&fields=" + String(fields);
                }
            }
            else if (fields != nullptr)
            {
                apiUrl += "?fields=" + String(fields);
            }

            // Perform the GET request to retrieve the record
            // Use your PocketBase library to make the GET request, and store the response in 'result'
            // For example, assuming pb has a getRecord method in your PocketBase library:
            String result = pb.getRecord(apiUrl);

            // Parse the result to check for error responses
            DynamicJsonDocument jsonResponse(1024); // Adjust the size based on your needs
            deserializeJson(jsonResponse, result);

            int code = jsonResponse["code"].as<int>();

            // Handle possible error responses
            if (code == 404)
            {
                // Handle 404 error
                Serial.println("Error: The requested resource wasn't found.");
            }
            else if (code == 403)
            {
                // Handle 403 error
                Serial.println("Error: Only admins can access this action.");
            }
            else
            {
                // Return the result
                return result;
            }
        }
        catch (const std::exception &e)
        {
            Serial.println("Exception occurred during the request: " + String(e.what()));
        }

        // Return an empty string in case of an error
        return "";
    }

    const String create(const char *jsonData, const char *fieldName = nullptr, const char *fileName = nullptr, Stream *fileStream = nullptr);

    const String update(const char *jsonData);

    const String deleteRecord(const char *recordId, const char *filesToDelete[] = nullptr);

private:
    PocketBase &pb;             // Reference to the PocketBase object associated with the collection
    const char *collectionName; // The name of the collection
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
