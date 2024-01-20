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

    // Methods to build collection and record URLs
    PocketbaseArduino &collection(const char *collection);

    /**
     * @brief Fetches a single record from a Pocketbase collection
     *
     * @param recordId  The ID of the record to view.
     *
     * @param expand    (Optional) Auto expand record relations. Ex.:?expand=relField1,relField2.subRelField Supports up to 6-levels depth nested relations expansion.
     *                  The expanded relations will be appended to the record under the expand property (eg. "expand": {"relField1": {...}, ...}).
     *                  Only the relations to which the request user has permissions to view will be expanded.
     *
     * @param fields    (Optional) Comma separated string of the fields to return in the JSON response (by default returns all fields). Ex.: ?fields=*,expand.relField.name
     *                  * targets all keys from the specific depth level.
     *                  In addition, the following field modifiers are also supported:
     *                  :excerpt(maxLength, withEllipsis?)
     *                  Returns a short plain text version of the field string value.
     *                  Ex.: ?fields=*,description:excerpt(200,true)
     *
     *                  For more information, see: https://pocketbase.io/docs
     */
    String getOne(const char *recordId, const char *expand /* = nullptr */, const char *fields /* = nullptr */);

private:
    String httpGETRequest(const char *endpoint);
    String httpsGETRequest(const char *endpoint);

private:
    String base_url;
    String current_endpoint;
};

#endif
