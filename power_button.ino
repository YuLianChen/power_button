#include "config.h"
#include "wifi.h"
#include "clock.h"
#include "mqtt.h"
#include "CmdExecution.h"




void setup() {
  SwitchButtonIint();
  Serial.begin(115200);
  // SwitchButtonIint();
  WifiConnect(WIFISSID, PASSWORD);
  rtc_clock_init();
  SetMqttServer(MQTTSERVER, MATTPORT);
  CheckMqttConnection();
  MqttPush();
  CmdExeInit();
}

void loop() {


  char rev_cmd[100] = { 0 };
  uint rev_buffer_len = sizeof(rev_cmd);
  uint datalen = 0;
  while (1) {

    //wifi连接状态检查
    if (WiFi.status() != WL_CONNECTED) {
      //wifi重新连接
      WifiConnect(WIFISSID, PASSWORD);
    } else {
      //mqtt 检查
      CheckMqttConnection();
      //时钟校准
      clock_loop();
      
    }
      //检查mqtt是否有收到消息
      if (is_rev_data()) {
        get_mqtt_rev(rev_cmd, &datalen, rev_buffer_len);
        //执行收到的命令
        exe_cmd(rev_cmd);
        memset(rev_cmd, 0, rev_buffer_len);
      }
      // MqttPush();
      delay(1000);
    }
  }
