//LCD初期化用関数
void beginLCD(int i){
  lcd.setContrast(i);
  lcd.setCursor(0,0);
  lcd.print("        "); 
  lcd.setCursor(0,1);
  lcd.print("        ");
}
//表示切替
void transPrint(int ans,int valval){
  //どの階層にいるか判断
  //まずはモード選択状態
  /*if(lk.mode == 0 ){
    printWatch(cont);  
  }*/
  if(lk.select == -1 && lk.val == -1){
    //フルカラーLEDの光を消す命令
    RGBLED.begin() ;
    RGBLED.setBrightness(0);
    RGBLED.show() ; 
    //初期分
    if(valval == 0){
      printWatch(cont); 
    }
    else if(valval < MODE){
      printMODE(cont,valval,"NONE");
    }
    //追加分
    else{
      readSerial(0,8);
      printMODE(cont,lk.mode,words);
    }
  }
  //セレクト画面
  else if(lk.val == -1){
    //初期分
    if( lk.mode == 0){
      printYear(cont);
    }
    else if(lk.mode < MODE){
      printSELECT(cont,valval,"NONE","NONE");
    }
    //追加分
    else{
      readSerial(0,8);
      printSELECT(cont,lk.select,words,words1);
    }
  }
  //タスク
  else{
    if(lk.mode == 0){
      printBATTERY(cont);
    }else if(lk.mode < MODE){
      systemTask();
    }
  }
}
//時間表示
void printWatch(int i){
  rtc.get(&secs, &mins, &hours, &days, &months, &years);
  beginLCD(i);
  lcd.setCursor(0,0);
  lcd.print(months);
  lcd.setCursor(2,0);
  lcd.print("/");
  lcd.setCursor(3,0);
  lcd.print(days);
  lcd.setCursor(0,1);
  lcd.print(hours);
  lcd.setCursor(2,1);
  lcd.print(":");
  lcd.setCursor(3,1);
  lcd.print(mins);
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(secs);
  delay(1);
  int h,m;
  //時
  int hh = hours % 12;
  if(hh == 0){
    h = 0;
  }else if(hh == 1 || hh == 2){
    h = 1;
  }else if(hh == 3){
    h = 2;
  }else if(hh == 4 || hh == 5){
    h = 3;
  }else if(hh == 6){
    h = 4;
  }else if(hh == 7 ||hh == 8){
    h = 5; 
  }else if(hh == 9){
    h = 6;
  }else if(hh == 10 || hh == 11){
    h = 7;
  }
  //分
  if(mins < 5){
    m = 0;
  }else if(5 <= mins && mins <15){
    m = 1;
  }else if(15 <= mins && mins < 20){
    m = 2;
  }else if(20 <= mins && mins < 30){
    m = 3;
  }else if(30 <= mins && mins <35){
    m = 4;
  }else if(35 <= mins && mins < 45){
    m = 5; 
  }else if(45 <= mins && mins < 50){
    m = 6;
  }else if(50 <= mins && mins <= 59){
    m = 7;
  }
  RGBLED.setBrightness(100);
  if(h == m){
    //朱色
    int i2ci;
    for(i2ci=0;i2ci<8;i2ci++){
      if(i2ci == h){
        RGBLED.setPixelColor(rgbLED[i2ci],rgb[0][0],rgb[0][1],rgb[0][2]);
      }else{
        RGBLED.setPixelColor(rgbLED[i2ci],0,0,0);
      }
    }
  }else{
    int i2ci;
    for(i2ci=0;i2ci<8;i2ci++){
      if(i2ci == h){
        //黄色
        RGBLED.setPixelColor(rgbLED[i2ci],rgb[4][0],rgb[4][1],rgb[4][2]);
      }else if(i2ci == m){
        //白色
        RGBLED.setPixelColor(rgbLED[i2ci],rgb[7][0],rgb[7][1],rgb[7][2]);
      }else{
        RGBLED.setPixelColor(rgbLED[i2ci],0,0,0);
      }
    }
  }
  RGBLED.show() ;
}
//年、月、日
void printYear(int i){
  rtc.get(&secs, &mins, &hours, &days, &months, &years);
  beginLCD(i);
  lcd.setCursor(0,0);
  lcd.print(years);
  lcd.setCursor(5,0);
  lcd.print("R");
  lcd.setCursor(6,0);
  lcd.print(years-GANNEN+1);
  lcd.setCursor(3,1);
  lcd.print(months);
  lcd.setCursor(5,1);
  lcd.print("/");
  lcd.setCursor(6,1);
  lcd.print(days);
  delay(1);
}
//バッテリー残量表示
void printBATTERY(int i){
  beginLCD(i);
  lcd.setCursor(1,0);
  lcd.print(battery);
  lcd.setCursor(5,0);
  lcd.print("[V]");
  lcd.setCursor(1,1);
  lcd.print(batPasent);
  lcd.setCursor(5,1);
  lcd.print("[%]");
  int batLED = batPasent * (8.0/100.0);
  int j;
  RGBLED.setBrightness(100);
  Serial.print("batLED");
  Serial.println(batLED);
  for(j=1;j<=8;j++){
    if(j < batLED){ 
      RGBLED.setPixelColor(rgbLED[j],rgb[3][0],rgb[3][1],rgb[3][2]);
    }else if(batLED == j){
      RGBLED.setPixelColor(rgbLED[j],rgb[0][0],rgb[0][1],rgb[0][2]);
    }else{
      RGBLED.setPixelColor(rgbLED[j],0,0,0);
    }
  }
  RGBLED.show() ;
}
//モード表示用関数
void printMODE(int i,int modess,char *a){
  beginLCD(i);
  returnModeWord(modess); 
  //最初からあるモード
  if(modess < MODE){
    lcd.setCursor(0,0);
    lcd.print(wordsNAME); 
  }
  //追加分
  else{
    lcd.setCursor(0,0);
    lcd.print(a);
    delay(1);
  }
  lcd.setCursor(0,1);
  lcd.print("    MODE");
  delay(1);
}
//セレクト画面用関数
void printSELECT(int i,int modess,char *a,char *b){
  beginLCD(i);
  //char *modes0 = returnSelectWord0(modess); 
  //char *modes1 = returnSelectWord1(modess); 
  //最初からあるモード
  if(lk.mode < MODE){
    returnSelectWord0(modess); 
    lcd.setCursor(0,0);
    lcd.print(wordsNAME); 
    delay(1);
    returnSelectWord1(modess); 
    lcd.setCursor(gyouStart,1);
    lcd.print(wordsNAME); 
    gyouStart = 0;
    delay(10);
  }
  //追加分
  else{
    lcd.setCursor(0,0);
    lcd.print(a);
    lcd.setCursor(0,1);
    lcd.print(b);
    delay(10);
  }
}
