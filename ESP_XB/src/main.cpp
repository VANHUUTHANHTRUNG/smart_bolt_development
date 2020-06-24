// read Tx packet sent by another XBee
// receiver XBee module connected to ESP8266 by Rx/Tx pins

#include <Arduino.h>
#include <XBee.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
Rx64Response rx64 = Rx64Response();

uint8_t ssRx = 14;
uint8_t ssTx = 12;
SoftwareSerial nss;

void setup()
{
  Serial.begin(115200);
  nss.begin(115200, SWSERIAL_8N1, ssRx, ssTx, false, 95, 11); // SoftwareSerial was checked, working fine in both ways
  Serial.println("\nSoftware serial test!");
}

int incoming_byte = 0;
void loop()
{
  xbee.readPacket();

  if (xbee.getResponse().isAvailable())
  {
    // got something

    if (xbee.getResponse().getApiId() == RX_64_RESPONSE)
    {
      // got a rx packet
      xbee.getResponse().getRx64Response(rx64);
      uint8_t data[rx64.getDataLength()];
      for (int i = 0; i < rx64.getDataLength(); i++)
      {
        data[i] = rx64.getData(i);
      }
      for (int i = 0; i < rx64.getDataLength(); i++)
      {
        Serial.println(data[i]);
      }
    }
    else
    {
      // not something we were expecting
      Serial.println("Something unexpected");
    }
  }
  else if (xbee.getResponse().isError())
  {
    Serial.print("Error reading packet.  Error code: ");
    Serial.println(xbee.getResponse().getErrorCode());
    // or flash error led
  }
}