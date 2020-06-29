//ロータリーエンコーダー用の割り込み関数
void ENC_READ() {
  byte cur = (!digitalRead(ENC_B) << 1) + !digitalRead(ENC_A);
  byte old = pos & B00000011;
  byte dir = (pos & B00110000) >> 4;
 
  if (cur == 3){
    cur = 2;
  }else if (cur == 2){
    cur = 3;
  }
  if (cur != old)
  {
    if (dir == 0)
    {
      if (cur == 1 || cur == 3) dir = cur;
    } else {
      if (cur == 0)
      {
        if (dir == 1 && old == 3){
          value++;//プラス方向
        }
        else if (dir == 3 && old == 1){
          value--;//マイナス方向
        }
        dir = 0;
      }
    }
    
    bool rote = 0;
    if (cur == 3 && old == 0) rote = 0;
    else if (cur == 0 && old == 3) rote = 1;
    else if (cur > old) rote = 1;
 
    pos = (dir << 4) + (old << 2) + cur;
  }
  setValue();
}
//valueの値を最適化する
void setValue(){
  int maximam;
  //モード選択状態
  if(lk.select == -1 && lk.val == -1){
    maximam = mode;
    if(value>maximam-1){
      value = 0;
    }
    //負の数になったら
    else if(value<=-1){
      value = maximam-1;
    }
  }
  //セレクト画面状態
  else if(lk.val == -1){
    maximam = selectManue[lk.mode];
      if(value>maximam-1){
      value = 0;
    }
    //負の数になったら
    else if(value<=-1){
      value = maximam-1;
    }
  }
  //タスク状態
  else{
    switch(lk.mode){
      //lightMODE
      case 1:{
        switch(lk.select){
          //normalLight
          case 0:{
            if(value > 100){
              value = 0;
            }else if(value < 0){
              value = 100;
            }
          break;}
          //color
          case 1:{
            if(value > 9){
              value = 0;
            }else if(value < 0){
              value = 9;
            }
          break;}
          //fullLight
          case 2:{
            if(value > 100){
              value = 0;
            }else if(value < 0){
              value = 100;
            }
          break;}
        }
      break;}
      default:{
      break;}
    }
  }
}
//valueの値を強制的に変える
void forceValue(int math){
  value = math;
  Serial.println(value);
}
//バッテリーの電圧を調べ、ロータリーエンコーダーのLEDで残量を表示させる
void batteryLED(){
  battery = analogRead(BATTERY);
  battery = battery * (3.3/1023) * 2.0;//1:1で分圧しているので実際の電池の電圧は測定値の2倍になる
  if(battery >= 4.2){//電池の最大が4.2V
    batPasent = 100;
  }else if(battery <= 2.7){//電池の最低が2.7V
    batPasent = 0;
  }else{
    batPasent = (battery - 2.7) * (100/(4.2-2.7));
  }
  //Serial.print("batter[V]=");
  //Serial.println(battery);
  Serial.print("batPasent[%]=");
  Serial.println(batPasent);
  //ロータリエンコーダーのLEDで残量を知らせる
  //LED故障
  //analogWrite(ENCRED,100-batPasent);
  //analogWrite(ENCBLUE,batPasent);
}
