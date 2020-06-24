#include <Arduino.h>
#include "ThingSpeak.h"
#include "secrets.h"
unsigned long myChannelNumber = SECRET_CH_ID;
const char *myWriteAPIKey = SECRET_WRITE_APIKEY;

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(100);
  ThingSpeak.begin(client);
  WiFi.mode(WIFI_STA);
  Serial.printf("\nWi-Fi mode set to WIFI_STA %s\n", WiFi.mode(WIFI_STA) ? "" : "Failed!");
}

void loop()
{
  WiFi.disconnect();
  delay(1);
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("\nAttempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid,pass);
      Serial.print(".");
      WiFi.printDiag(Serial);
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

    int valueA0 = analogRead(A0);

    // Write value to Field 1 of a ThingSpeak Channel
    ThingSpeak.setField(1, valueA0);
    int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (httpCode == 200)
    {
      Serial.println("Channel write successful.");
    }
    else
    {
      Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
    }

    // Wait 20 seconds to update the channel again
    delay(5000);
  }