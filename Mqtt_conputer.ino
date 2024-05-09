#include "config.h"

#define WIFISSID "chen"          /* WIFI 名称 */
#define PASSWORD "chenyujing233" /* WIFI 密码 */
#define SWITCHBOTTON 3           /* 开关引脚 */





// 创建定时器句柄
Ticker timer1;


bool WifiConnect(String SSID, String wifiPassword) {
  WiFi.begin(SSID, wifiPassword);
  Serial.print("Trying to connect to " + SSID + "...\r\n");

  for (unsigned char count = 0; count < 20; count++) {
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



void SwitchButtonIint() {
  pinMode(SWITCHBOTTON, OUTPUT);
}



WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com", 60 * 60 * 8, 30 * 60 * 1000);



void setup() {
  Serial.begin(115200);
  // SwitchButtonIint();
  WifiConnect(WIFISSID, PASSWORD);

  timeClient.begin();
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());

  SetMqttServer(MQTTSERVER, MATTPORT);
  // timer1.attach(0.5, timer1_cb);
}

void loop() {

  CheckMqttConnection();
  MqttPush();
  Serial.println(timeClient.getFormattedTime());
  delay(5000);
}
