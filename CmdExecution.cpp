#include "HardwareSerial.h"
#include "CmdExecution.h"
#include "ArduinoJson.h"
#include "clock.h"


void CmdExeInit() {
}

void exe_cmd(char* cmd) {
  Serial.println(cmd);
  DynamicJsonBuffer jsonBuffer(1024);
  JsonObject& root = jsonBuffer.parseObject(cmd);
  if (!root.success()) {
    Serial.println(F("Parsing failed!"));
    // return;
  }

  int cmd_type;


  //解析指令类型
  switch(root["cmd"].as<int>())
  {
    case 1:
    Serial.println("Press button");
    Switch_Button_On();
    break;
    case 2:
    Serial.println("Update the alarm time");
    
    break;
    case 3:
    Serial.println("Go back to the current alarm setting");
    break;
    case 4:
    Serial.println("Go back to the current alarm setting");
    break;
    case 5:
    Serial.println("Returns the current system time");
    break;
    case 6:
    Serial.println("updata rtc clock");
    clock_updata();
    default:
    break;
  }
}