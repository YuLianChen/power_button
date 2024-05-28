#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FS.h>


#define MQTTSERVER  "47.116.53.93"
#define MATTPORT     1883

#define WIFISSID "icloud_clark_2.4g" /* WIFI 名称 */
#define PASSWORD "15803890751"       /* WIFI 密码 */
#define SWITCHBOTTON 3               /* 开关引脚 */
#define FILE_PATH  "/Fle/note.txt"
void SwitchButtonIint();
void Switch_Button_On();