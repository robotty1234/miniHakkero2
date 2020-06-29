void settingTask(){
  int re = value;
  switch(lk.select){
    //timeSet
    case 0:{
      rtc.get(&secs, &mins, &hours, &days, &months, &years);
      howTime[0] = years;
      howTime[1] = months;
      howTime[2] = days;
      howTime[3] = hours;
      howTime[4] = mins;
      howTime[5] = secs;
      //int re = value;
      int val=-1;
      beginLCD(cont);
      lcd.setCursor(0,0);
      lcd.print("WhatDay");
      //年設定
      value = howTime[0];
      while(digitalRead(MAINSW) == HIGH){
        if(value>3000){
          value = 0; 
        }else if(value<0){
          value = 3000;
        }
        if(val != value){
          lcd.setCursor(0,1);
          lcd.print("  ");
          lcd.setCursor(0,1);
          lcd.print(value);
          delay(10);
          val = value;
        }
      }
      while(digitalRead(MAINSW) == LOW){}
      howTime[0] = value;
      //月設定
      value = howTime[1];
      while(digitalRead(MAINSW) == HIGH){
        if(value>12){
          value = 0; 
        }else if(value<0){
          value = 12;
        }
        if(val != value){
          lcd.setCursor(0,1);
          lcd.print("  / ");
          lcd.setCursor(0,1);
          lcd.print(value);
          delay(10);
          val = value;
        }
      }
      while(digitalRead(MAINSW) == LOW){}
      howTime[1] = value;
      //日にち設定
      value = howTime[2];
      while(digitalRead(MAINSW) == HIGH){
        if(value>31){
          value = 0; 
        }else if(value<0){
          value = 31;
        }
        if(val != value){
          lcd.setCursor(3,1);
          lcd.print("  ");
          lcd.setCursor(3,1);
          lcd.print(value);
          delay(10);
          val = value;
        }
      }
      while(digitalRead(MAINSW) == LOW){}
      howTime[2] = value;
      
      beginLCD(cont);
      lcd.setCursor(0,0);
      lcd.print("WhatTime");
      lcd.setCursor(2,1);
      lcd.print(":");
      lcd.setCursor(5,1);
      lcd.print(":");
      delay(10);
      //時設定
      value = howTime[3];
      while(digitalRead(MAINSW) == HIGH){
        if(value>24){
          value = 0; 
        }else if(value<0){
          value = 24;
        }
        if(val != value){
          lcd.setCursor(0,1);
          lcd.print("  ");
          lcd.setCursor(0,1);
          lcd.print(value);
          delay(10);
          val = value;
        }
      }
      while(digitalRead(MAINSW) == LOW){}
      howTime[3] = value;
      //分設定
      value = howTime[4];
      while(digitalRead(MAINSW) == HIGH){
        if(value>59){
          value = 0; 
        }else if(value<0){
          value = 59;
        }
        if(val != value){
          lcd.setCursor(3,1);
          lcd.print("  ");
          lcd.setCursor(3,1);
          lcd.print(value);
          delay(10);
          val = value;
        }
      }
      while(digitalRead(MAINSW) == LOW){}
      howTime[4] = value;
      //秒設定
      value  = howTime[5];
      while(digitalRead(MAINSW) == HIGH){
        if(value>59){
          value = 0; 
        }else if(value<0){
          value = 59;
        }
        if(val != value){
          lcd.setCursor(6,1);
          lcd.print("  ");
          lcd.setCursor(6,1);
          lcd.print(value);
          delay(10);
          val = value;
        }
      }
      while(digitalRead(MAINSW) == LOW){}
      howTime[5]  = value;
      //value = re;
      rtc.set(howTime[5],howTime[4],howTime[3],howTime[2],howTime[1],howTime[0]); //sec, min, hour, day, month, year
      //Serial.println(h);
    break;}

    //contrastSet
    case 1:{
    //re = value;
    cont = -1;
    while(digitalRead(MAINSW) == HIGH){
      if(value != cont){
        if(value >= 30){
          value = 30;
        }else if(value <= 0){
          value = 0;
        }
        cont = value;
        beginLCD(cont);
        lcd.setCursor(0,0);
        lcd.print("contrast");
        lcd.setCursor(0,1);
        lcd.print(cont);
      }
    }while(digitalRead(MAINSW) == LOW){}
    //value = re1;
    break;}

    //backLightSet
    case 2:{
    backLED = -1;
    while(digitalRead(MAINSW) == HIGH){
      if(value != backLED){
        if(value >= 255){
          value = 255;
        }else if(value <= 0){
          value = 0;
        }
        backLED = value;
        beginLCD(cont);
        lcd.setCursor(0,0);
        lcd.print("backlight");
        lcd.setCursor(0,1);
        lcd.print(backLED);
        analogWrite(BACKLIGHT,backLED);
      }
    }while(digitalRead(MAINSW) == LOW){}
    analogWrite(BACKLIGHT,0);
    break;}
  }
  value = re;
}

