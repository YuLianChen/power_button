#include "stdint.h"
#include <FS.h>
#include "file.h"

String file_name = FILE_PATH; //被读取的文件位置和名称，放在/Fle文件夹下



void file_setup() {

  Serial.println("SPIFFS format start");
  SPIFFS.format();    // 格式化SPIFFS
  Serial.println("SPIFFS format finish");

  if (SPIFFS.begin()) { // 启动SPIFFS
    Serial.println("SPIFFS Started.");
  } else {
    Serial.println("SPIFFS Failed to Start.");
  }
}


//写操作
void file_write(String file_name, String content)
{
  /*****************************************写入闪存文件内容*************************************************/
  File dataFile = SPIFFS.open(file_name, "w");// 建立File对象用于向SPIFFS中的file对象（即/notes.txt）写入信息
  dataFile.println(content);       // 向dataFile写入字符串信息
  dataFile.close();                           // 完成文件写入后关闭文件
  Serial.print("已写入闪存文件内容:");
  Serial.println(content);
}
//读操作
//读操作
void file_read_print(String file_name) {
  //确认闪存中是否有file_name文件
  File dataFile;
  if (SPIFFS.exists(file_name)) {
    //建立File对象用于从SPIFFS中读取文件
    dataFile = SPIFFS.open(file_name, "r");
    //读取文件内容并且通过串口监视器输出文件信息
    Serial.println("读取的文件内容：");
    for (int i = 0; i < dataFile.size(); i++) {
      Serial.print((char)dataFile.read());
    }
  } else {
    Serial.print(file_name);
    Serial.print(" NOT FOUND.");
  }
  //完成文件读取后关闭文件
  dataFile.close();
}

//追加操作
void file_add(String file_name, String content)
{
  if (SPIFFS.exists(file_name))
  {
    File dataFile = SPIFFS.open(file_name, "a");// 建立File对象用于向SPIFFS中的file对象（即/notes.txt）写入信息
    dataFile.println(content); // 向dataFile添加字符串信息
    dataFile.close();                           // 完成文件操作后关闭文件
    Serial.println("已经增添内容:");
    Serial.println(content);
  }
  else 
  {
    Serial.print(file_name);
    Serial.print(" NOT FOUND.");
  }
}
