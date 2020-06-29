//文字列を呼んで、wordsに移すための関数
void  readSerial(byte key,int longs){
  //byte a =1;
  Serial.write(key);
  while(Serial.available()< longs){
  }
  int lp;
  for(lp=0;lp<=longs;lp++){
    words[lp] = Serial.read();
    //Serial.println(words[lp]);
  }
}
