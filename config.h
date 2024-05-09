#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define MQTTSERVER  "47.116.53.93"
#define MATTPORT     1883

/***********************************MQTT*************************************/
void MqttPush(void);
void CheckMqttConnection();
void SetMqttServer(const char *mqttServer, unsigned int mqttPort);
/****************************************************************************/