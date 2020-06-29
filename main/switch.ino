//メインスイッチが押されたときの関数
void mainSW(int how){
  Serial.print("mainSW");
  Serial.println(how);
  //モード選択の場合
  if(lk.select==-1&&lk.val==-1){
    Serial.println("mode");
    //次のとこに移る
    lk.mode = value;
    lk.select = 0;
    value = 0;
    returnModeWord(lk.mode);
    //Serial.println(a);
  }
  //機能選択の場合
  else if(lk.val == -1){
    Serial.println("select");
    //次のとこに移る
    lk.select = value;
    lk.val = 0;
    value = 0;
    //仕事に移る
    systemTask();
    Serial.println("lost3");
    if(lk.mode == 4){
      backSW(0);
    }
  }
  //値選択
  else{
    Serial.println("value");
    lk.val = value;
    lk.juge = !lk.juge;
  }
  delay(50);
}
//バックスイッチが押されたときの関数
void backSW(int how){
  Serial.println("backSW");
  //機能選択に戻る
  if(lk.val != -1 & lk.select != -1){
    Serial.println("bakcselsect");
    lk.juge = false;
    lk.val = -1;
    forceValue(lk.select);
  }
  //モード選択に戻る
  else if(lk.select != -1){
    Serial.println("backmode");
    lk.select = -1;
    forceValue(lk.mode);
  }
  delay(500);
}
//バックライトスイッチが押されたときの関数
void backlightSW(int how){
  Serial.println("backlightSW");
  if(backLightLED == false){
    backLightLED = true;
    analogWrite(BACKLIGHT,backLED);
  }else{
    backLightLED = false;
    analogWrite(BACKLIGHT,0);
  }
}
//マルチスイッチが押されたときの関数
void multiSW(int how){
  Serial.println("multiSW");
  delay(500);
}
//イヤホンジャックスイッチが押されたときの関数
void jyackSW(int how){
  Serial.print("jyackSW");
  Serial.println(how);
  delay(500);
}
