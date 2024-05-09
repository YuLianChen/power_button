#include "config.h"



// 创建主题字符串
String subscriptionTopic;

WiFiClient esp8266Client;

PubSubClient client1(esp8266Client);

void SetMqttServer(const char *mqttServer, unsigned int mqttPort) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("[ANTARES] Unable to connect to MQTT server.\r\n");
  } else {
    Serial.print("Setting MQTT server \"" + String(mqttServer) + "\" on port " + String(mqttPort) + "\r\n");
    client1.setServer(mqttServer, mqttPort);
  }
}

void CheckMqttConnection() {
  subscriptionTopic = "switch/conputer";

  if (!client1.connected()) {
    while (!client1.connected()) {
      Serial.print(" Attempting MQTT connection...\n");

      String clientId = "ESP8266-11";

      char clientIdChar[clientId.length() + 1];
      clientId.toCharArray(clientIdChar, clientId.length() + 1);

      if (client1.connect(clientIdChar)) {
        Serial.print("Connected! Client ID:");
        Serial.print(clientIdChar);
        Serial.print("\n");
        char subscriptionTopicChar[subscriptionTopic.length() + 1];
        subscriptionTopic.toCharArray(subscriptionTopicChar, subscriptionTopic.length() + 1);

        Serial.println();
        Serial.print("Topic: ");
        Serial.println(subscriptionTopicChar);

        client1.publish(subscriptionTopicChar, "connect!");
        client1.subscribe(subscriptionTopicChar);
      } else {
        Serial.print(" Failed, rc=" + String(client1.state()) + ", Will try again in 5 secs.\n");
        delay(5000);
      }
    }
  }
  client1.loop();
}

void MqttPush(void)
{
  client1.publish("test", "ESP01S");
}
