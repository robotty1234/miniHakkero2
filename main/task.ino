void systemTask(){
  //どのモードか？
  switch(lk.mode){
    //watchMode
    case 0:
    break;
    //lightMode
    case 1:
    lightTask();
    //Serial.println("lost");
    break;
    //musicMode
    case 2:
    break;
    //spellMode
    case 3:
    break;
    //settingMode
    case 4:
    settingTask();
    //Serial.println("lost");
    break;
  }
 //Serial.println("lost2");
}

