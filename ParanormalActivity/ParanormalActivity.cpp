// Do not remove the include below
#include "ParanormalActivity.h"
#include <XBee.h>
#include <SoftwareSerial.h>

int ir_out = 13;
int led = 9;

// 照明オン
//unsigned int data[] = {1022,505,64,190,64,189,64,189,65,62,64,62,64,190,64,189,64,190,64,62,64,62,64,190,64,189,64,62,64,62,64,62,64,62,64,189,64,190,64,189,64,62,64,190,64,62,64,62,64,190,64,62,64,62,64,62,64,190,64,62,64,190,64,190,64,62,64,4526,1022,250,64};
unsigned int data[] = {1022,505,67,186,67,186,67,187,66,59,67,60,67,187,66,187,67,187,66,59,67,59,68,186,67,187,67,60,67,60,66,60,66,60,67,187,66,187,66,187,66,60,67,187,66,60,66,60,66,187,66,60,66,60,64,62,67,187,64,62,64,190,64,190,64,62,64,4526,1022,250,67,10884,1022,250,67};

int last = 0;
unsigned long us = micros();

// セットアップ
void setup() {
  pinMode(ir_out, OUTPUT);
  pinMode(led, OUTPUT);
}

// dataからリモコン信号を送信
void sendSignal() {
  int dataSize = sizeof(data) / sizeof(data[0]);
  for (int cnt = 0; cnt < dataSize; cnt++) {
    unsigned long len = data[cnt]*10;  // dataは10us単位でON/OFF時間を記録している
    unsigned long us = micros();
    do {
      digitalWrite(ir_out, 1 - (cnt&1)); // cntが偶数なら赤外線ON、奇数ならOFFのまま
      delayMicroseconds(8);  // キャリア周波数38kHzでON/OFFするよう時間調整
      digitalWrite(ir_out, 0);
      delayMicroseconds(7);
    } while (long(us + len - micros()) > 0); // 送信時間に達するまでループ
  }
}

void loop() {
  digitalWrite(led, HIGH);
  sendSignal();
  digitalWrite(led, LOW);
  delay(3000);
}
