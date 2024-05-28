#include "config.h"

/***********************************MQTT*************************************/
void MqttPush(void);
void CheckMqttConnection();
void SetMqttServer(const char *mqttServer, unsigned int mqttPort);
void callback(char* topic, byte* payload, unsigned int length);
void mqtt_loop();
bool is_rev_data();
int get_mqtt_rev(char *rev, uint * datalen, int buffer_len);
/****************************************************************************/