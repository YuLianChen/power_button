#include "user_interface.h"
#include "HardwareSerial.h"
#include "stdlib.h"

#include "clock.h"

typedef void (*Alarmcb)(void);
typedef struct {
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
} alarm_clock_str;

typedef struct Node {
  alarm_clock_str data;
  struct Node *next;
} Node, LinkList;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com", 60 * 60 * 8, 30 * 60 * 1000);


uint count = 0;
LinkList head;

//返回链表
LinkList *createLinkList(LinkList *L) {
  n = (LinkList *)malloc(sizeof(LinkList));
  if (n == NULL) {
    Serial.print("memory malloc failed\n");
    return 0;
  }
  memset(n, 0, sizeof(LinkList));
  return n;
}

int getLen(LinkList *L) {
  if (L->next == NULL) return 0;  //头节点为空，表示链表中不存在元素
  int len = 0;
  LinkList *r = L->next;
  while (r) {
    r = r->next;  //循环指针后移
    len++;
  }
  return len;
}

//将元素插入指定位置
int insertLinkList(LinkList *L, int pos, alarm_clock_str *data) {
  if (pos < 1 || pos > getLen(L) + 1) {
    Serial.println("index nums error");
    return 0;
  }
  LinkList *r = L, *n;
  n = (LinkList *)malloc(sizeof(LinkList));
  if (n == NULL) {
    Serial.print("memory malloc failed\n");
    return 0;
  }
  //赋值
  memcpy(&(n->data), data, sizeof(alarm_clock_str));
  while (--pos > 0) {
    r = r->next;  //移动到要插入的位置
  }
  n->next = r->next;
  r->next = n;  //把新节点置于要插入的节点后
  return 1;
}

//尾部添加新的数据
int addList(LinkList *L, alarm_clock_str *data) {
  return insertLinkList(L, getLen(L), data);
}

//将指定位置的元素删除
int deleteLinkList(LinkList *L, int pos) {
  if (pos < 1 || pos > getLen(L)) return 0;
  LinkList *r = L, *d;
  while (--pos > 0) {
    r = r->next;
  }
  d = r->next;
  r->next = d->next;
  free(d);
  return 1;
}

//查找指定为元素，返回指定元素位置
int seachLinkList(LinkList *L, alarm_clock_str *data) {
  int pos = 1;
  LinkList *r = L->next;
  while (r) {
    if (r->data.hour == data->hour && r->data.min == data->min && r->data.sec == data->sec) {
      return pos;
    }
    r = r->next;
    pos++;
  }
  return -1;
}

//获取闹钟时间列表
void get_alarm_time_list(char *data, uint datalen, LinkList *L) {
  if (datalen > getLen(L) * 9 + 1) {
    LinkList *r = L->next;
    char temp[10] = { 0 };
    int count = 0;
    while (r) {
      sprintf(data + (count * 9), "%02d:%02d:%02d ", r->data.hour, r->data.min, r->data.sec);
      count++;
      r = r->next;
    }
  }
}

//初始化读取闹钟
void file_read_alarm_time() {
  head = createLinkList(head);
  alarm_clock_str alarm_time = { 0 };
  File dataFile;
  char *temp_ch;
  char temp_string[10];
  if (SPIFFS.exists(file_name)) {
    Serial.println("read alarm time list");
    String file_path = FILE_PATH;
    dataFile = SPIFFS.open(file_path, "r");

    for (int i = 0; i < dataFile.size(); i++) {
      temp_ch = (char)dataFile.read();
      if (temp_ch == "\n") {

      } else {

      }
      Serial.print((char)dataFile.read());
    }
  } else {
    Serial.println("there is no alarm time list file");
  }
}

void rtc_clock_init() {
  timeClient.begin();
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  timeClient.update();
}

void clock_loop() {
  //十八分钟更新一次时间
  if (count == 1080) {
    timeClient.update();
    Serial.print("clock data update!\n");
    count = 0;
  }
  count++;
  Serial.println(timeClient.getFormattedTime());
}

void clock_updata() {
  timeClient.update();
}




//定时闹铃
void alarm(Alarmcb AlarmTask) {
  int tm_Hour = timeClient.getHours();
  int tm_Minute = timeClient.getMinutes();
  int tm_Second = timeClient.getSeconds();
  delay(1000);
}
