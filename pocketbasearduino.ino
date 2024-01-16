/**
 *
 * HTTP/HTTPS GET REQUEST
 *
 * [REFERENCE CODE]
 *
 * HTTP AND HTTPS GET REQUEST FOR ESP8266
 *
 * Created Jan 16 2024
 * By jeoooo
 *
 * Modified Jan 16 2024
 * By jeoooo
 *
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <BearSSLHelpers.h>

const char *ssid = "dlink-3CCB";
const char *password = "rvtbf69439";

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

/**
 * Performs an HTTP GET request to the specified URL.
 *
 * @param url The URL to send the GET request to.
 */
void httpGETRequest(const char *url)
{
  // create an HTTPClient instance
  HTTPClient http;

  // Initializing an HTTP communication
  Serial.print("[HTTP] begin...\n");
  if (http.begin(url))
  { // HTTP
    Serial.print("[HTTP] GET...\n");

    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0)
    {
      // HTTP header has been sent, and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = http.getString();
        Serial.println(payload);
      }
    }
    else
    {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
  else
  {
    Serial.printf("[HTTP] Unable to connect\n");
  }
}

/**
 * Performs an HTTPS GET request to the specified URL.
 *
 * @param url The URL to send the GET request to.
 */
void httpsGETRequest(const char *url)
{
  // create a WiFiClientSecure instance
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

  // Ignore SSL certificate validation
  client->setInsecure();

  // create an HTTPClient instance for HTTPS
  HTTPClient https;

  // Initializing an HTTPS communication using the secure client
  Serial.print("[HTTPS] begin...\n");
  if (https.begin(*client, url))
  { // HTTPS
    Serial.print("[HTTPS] GET...\n");

    // start connection and send HTTP header
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0)
    {
      // HTTP header has been sent, and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = https.getString();
        Serial.println(payload);
      }
    }
    else
    {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
  }
  else
  {
    Serial.printf("[HTTPS] Unable to connect\n");
  }
}

void loop()
{
  // Example usage of the httpGETRequest function
  httpGETRequest("http://jsonplaceholder.typicode.com/users/1");
  delay(5000);

  // Example usage of the httpsGETRequest function
  httpsGETRequest("https://www.howsmyssl.com/a/check");
  delay(5000);
}
