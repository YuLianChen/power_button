#include "wifi.h"

/**
*
*/
bool WifiConnect(String SSID, String wifiPassword) {
  WiFi.begin(SSID, wifiPassword);
  Serial.print("Trying to connect to " + SSID + "...\r\n");

  for (unsigned char count = 0; count < 20; count++) {
    if (WiFi.status() == WL_CONNECTED) {
      break;
    }
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Could not connect to " + SSID + ".\r\n");
    return false;
  } else {
    WiFi.setAutoReconnect(true);
    Serial.print("\n WiFi Connected!\n");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    return true;
  }
}

