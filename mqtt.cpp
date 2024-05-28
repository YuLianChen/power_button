#include "string.h"
#include "stdlib.h"
#include "Stream.h"
#include "mqtt.h"

#define TOPIC "switch/conputer/power"
#define PUSS_TOPIC "switch/conputer/power_report"
// 创建主题字符串
String subscriptionTopic;
WiFiClient esp8266Client;

// PubSubClient client1(esp8266Client);
PubSubClient client1(MQTTSERVER, MATTPORT, callback, esp8266Client);

//储存mqtt接收信息状态和数据
typedef struct {
  bool is_mqtt_rev;
  char *topic;
  char *data;
  uint data_len;
} mqtt_rev_stru_create;

mqtt_rev_stru_create mqtt_rev_data;

/**
 * @brief mqtt接收到消息的回调函数
 * 
 * @param topic 接收到消息的话题
 * @param payload 接收到的消息
 * @param length 消息的长度
 */
void callback(char *topic, byte *payload, unsigned int length) {
  //把写入的消息储存
  // char *rev_topic = (char *)malloc(50);

  char *rev_data = (char *)malloc(sizeof(char) * (length + 1));
  if (rev_data == NULL) {
    Serial.println("malloc failed");
  }
  memset(rev_data , 0, sizeof(char) * (length + 1));
  memcpy(rev_data, payload, length);
  mqtt_rev_data.data = rev_data;
  mqtt_rev_data.data_len = length;
  mqtt_rev_data.is_mqtt_rev = 1;

  // Serial.print("Message arrived [");
  // Serial.print(topic);
  // Serial.print("] ");
  // for (int i = 0; i < length; i++) {
  //   Serial.print((char)payload[i]);
  // }
  // Serial.println();
}


void SetMqttServer(const char *mqttServer, unsigned int mqttPort) {
  //mqtt 接收结构体初始化，一定要执行
  memset(&mqtt_rev_data, 0, sizeof(mqtt_rev_stru_create));
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("[ANTARES] Unable to connect to MQTT server.\r\n");
  } else {

    Serial.print("Setting MQTT server \"" + String(mqttServer) + "\" on port " + String(mqttPort) + "\r\n");
    // client1.setServer(mqttServer, mqttPort);
    // client1.setCallback(callback);
    // client1.setStream(stream);
  }
}

/**
 * @brief 
 * 
 * @param topic 
 * @param payload 
 * @param length 
 */
void CheckMqttConnection() {
  subscriptionTopic = TOPIC;

  if (!client1.connected()) {
    while (!client1.connected()) {
      Serial.print(" Attempting MQTT connection...\n");

      String clientId = "ESP01S";

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
        bool res = client1.subscribe(subscriptionTopicChar);
        if (res != true) {
          Serial.print("fail to subscribe,try again");
          for (int i = 0; i < 10; i++) {
            res = client1.subscribe(subscriptionTopicChar);
            if (res == true) {
              break;
            }
            Serial.print("fail to subscribe,try again");
            delay(1000);
          }
        }
      } else {
        Serial.print(" Failed, rc=" + String(client1.state()) + ", Will try again in 5 secs.\n");
        delay(5000);
      }
    }
  }
  client1.loop();
}

//返回接收到的消息
int get_mqtt_rev(char *rev, uint * datalen, int buffer_len) {
  bool flag = 1;
  if (buffer_len < mqtt_rev_data.data_len) {
    Serial.print("failed to get mqtt rev, rev buffer small\n");
    flag = 0;
  } else {
    memcpy(rev, mqtt_rev_data.data, mqtt_rev_data.data_len);
    *datalen = mqtt_rev_data.data_len;
  }

  if (flag) {
    free(mqtt_rev_data.data);
    mqtt_rev_data.is_mqtt_rev = 0;
    return 1;
  } else {
    return -1;
  }
}
//查询是否收到消息
bool is_rev_data() {
  return mqtt_rev_data.is_mqtt_rev;
}


void MqttPush(void) {
  client1.publish("PUSS_TOPIC", "ESP01S");
}

void mqtt_loop() {
  client1.loop();
}
