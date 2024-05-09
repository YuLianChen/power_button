#include "config.h"

typedef void (*Alarmcb)(void);
// 储存时间
uint8_t TimerClock[3] = { 0 };

void TimerGo() {
  // 秒
  if ((TimerClock[2]++) == 60) {
    TimerClock[2] = 0;
    // 分
    if (TimerClock[1]++ == 60) {
      TimerClock[1] = 0;
      // 时
      if (TimerClock[0]++ == 24) {
        TimerClock[0] = 0;
      }
    }
  }
}

void timer1_cb() {
  TimerGo();
}

//定时闹铃
void alarm(uint8_t hour, uint8_t minute, uint8_t sec, Alarmcb AlarmTask) {
  if (TimerClock[0] == hour && TimerClock[1] == minute && TimerClock[2] == sec) {
    AlarmTask();
    delay(2000);
  }
}

