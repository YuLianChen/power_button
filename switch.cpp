#include "config.h"

//高电平时开关开启
void SwitchButtonIint() {
  pinMode(SWITCHBOTTON, OUTPUT);
  digitalWrite(SWITCHBOTTON, HIGH);
}

//开关活动
void Switch_Button_On()
{
  delay(500);
  digitalWrite(SWITCHBOTTON, LOW);
  delay(500);
  digitalWrite(SWITCHBOTTON, HIGH);
}