#include <Arduino.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include <ArduinoJson.h> // Only version 5 will work with the current FirebaseArduino.h 
#include <FirebaseArduino.h>

#define FIREBASE_HOST "xbee-esp8266.firebaseio.com"
#define FIREBASE_AUTH "4fJ9n0tnW9B0AcspUY3e7caZHAKvop3MbgSdGccZ"
const String SSID = "Coincard";
const String PASSWORD = "Haiham1994";

StaticJsonBuffer<256> jb;
JsonObject& obj = jb.createObject();
void setup()
{
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connects successfully!");
  Serial.print("The IP address of ESP8266 is:");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  uint8_t count = 0;
  while (count < 10)
  {
    obj["value"] = String(count);
    obj["time"] = millis();
    Firebase.push("Variable",obj);
    if(Firebase.failed()){
      Serial.println(Firebase.error());
    }
    count++;
    delay(1000);
  }
}