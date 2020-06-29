#include <MsTimer2.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <ST7032.h>
#include <DS1307.h>
#include "define.h"
//初期設定
void setup(){
  int i;
  //ピンをデフォルトでアウトプットに設定
  /*for(i=0;i<=19;i++){
    pinMode(i,OUTPUT);
  }*/
  //シリアル通信の設定
  Serial.begin(9600);
  //ピンの入出力の設定
  for(i=0;i<SWT;i++){
    pinMode(sw[i],INPUT_PULLUP);
  }
  pinMode(MAINLED,OUTPUT);
  pinMode(ENC_A,INPUT_PULLUP);
  pinMode(ENC_B,INPUT_PULLUP);
  pinMode(BACKLIGHT,OUTPUT);
  pinMode(BATTERY,INPUT);
  //pinMode(ENCRED,OUTPUT);
  //pinMode(ENCBLUE,OUTPUT);
  //ロータリーエンコーダーの割り込みの設定
  attachInterrupt(0, ENC_READ, CHANGE);
  attachInterrupt(1, ENC_READ, CHANGE);
  //フルカラーLEDの光を消す命令
  RGBLED.begin() ;
  RGBLED.setBrightness(0);
  RGBLED.show() ; 
  //LCDの初期設定
  lcd.begin(8,2);
  beginLCD(cont);
  //時間の初期設定
 ///rtc.set(secs,mins,hours,days,months,years); //sec, min, hour, day, month, year
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);
}
void loop(){
  //ロータリエンコーダー数値が変わっていたら最適化
  if(value != value2 || swbool == true){
    RGBLED.setBrightness(0);
    RGBLED.show() ; 
    setValue();
    value2 = value;
    Serial.println(value);
    //表示
    transPrint(cont,value);
    swbool = false;
    //フルカラーLEDの光を消す命令
    //RGBLED.begin() ;
    //RGBLED.setBrightness(0);
    //RGBLED.show() ; 
  }
  //スイッチの確認(優先度が高いものから確認していきどれか押されていたら抜け出す) 
  int i=0;
  int swValue = SWT;
  int howlong = 0;
  int t = 0;
  boolean swF = false;
  for(i=0;i<=SWT;i++){
    //Serial.println(i);
    if(digitalRead(sw[i])==LOW){
      while(digitalRead(sw[i])==LOW&&t<=LONG){
        delay(1);
        t++;
      }
      swValue = i;
    }
  }
  //スイッチが検知したとき
  if(swValue<SWT){
    //長押しの場合
    if(t>=LONG){
      howlong = 3;
    }else{
      t=0;
      while(digitalRead(sw[swValue])==HIGH&&t<=SHORT){
        delay(1);
        t++;
      }
      while(digitalRead(sw[swValue])==LOW){}
      //ダブルクリックの場合
      if(t<=SHORT){
        howlong = 2;
      }else{//ただのクリックの場合
        howlong = 1;
      }
    }
    switch(swValue){
      //メインスイッチが押されたとき
      case 0:
        mainSW(howlong);
        swbool = true;
        break;
      //バックスイッチが押されたとき
      case 1:
        backSW(howlong);
        swbool = true;
        break;
      //バックライトスイッチが押されたとき
      case 2:
        backlightSW(howlong);
        swbool = true;
        break;
      //マルチスイッチが押されたとき
      case 3:
        multiSW(howlong);
        swbool = true;
        break;
     //イヤホンジャックのスイッチが押されたとき
     case 4:
        jyackSW(howlong);
        swbool = true;
        break; 
     default:
      break;
    }
  }
  //時間表示
  if(lk.select==-1&&lk.val==-1 && value == 0){
    printWatch(cont); 
    //batteryLED();
  }
  if(lk.select == 0 && lk.mode == 0 && lk.val >= 0){
    batteryLED();
    printBATTERY(cont);
  }
}
