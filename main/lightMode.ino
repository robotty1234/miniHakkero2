const char red[] PROGMEM = "RED";
const char purple[] PROGMEM = "PURPLE";
const char blue[] PROGMEM = "BLUE";
const char cyan[] PROGMEM = "CYAN";
const char yellow[] PROGMEM = "YELLOW";
const char amber[] PROGMEM = "AMBER";
const char green[] PROGMEM = "GREEN";
const char white[] PROGMEM = "WHITE";
const char magenta[] PROGMEM = "MAGENTA";
const char rain[] PROGMEM = "RAINBOW";

const char *const colorTITLE[] PROGMEM = {red,purple,blue,cyan,yellow,amber,green,white,magenta,rain};

void lightTask(){
  int re = value;
  switch(lk.select){
    //normal
    case 0:{
      beginLCD(cont);
      lcd.setCursor(0,0);
      lcd.print("POWER[%]");
      lcd.setCursor(0,1);
      lcd.print(value);
      if(lk.juge == true){
        analogWrite(MAINLED,value);
      }else{
        analogWrite(MAINLED,0);
      }
    break;}
    case 1:{
      int fulli;
      beginLCD(cont);
      lcd.setCursor(0,0);
      strcpy_P(wordsNAME, (char *)pgm_read_word(&(colorTITLE[value])));
      lcd.print(wordsNAME);  
      RGBLED.setBrightness(100);
      if(value <= 8){
        for(fulli=0;fulli<8;fulli++){
          RGBLED.setPixelColor(rgbLED[fulli],rgb[value][0],rgb[value][1],rgb[value][2]);
        }
      }else{
        for(fulli=0;fulli<8;fulli++){
          RGBLED.setPixelColor(rgbLED[fulli],rgb[rainbow[fulli]][0],rgb[rainbow[fulli]][1],rgb[rainbow[fulli]][2]);
        }
      }
      RGBLED.show();
      break;}
    //full
    case 2:{
      int fuli;
      beginLCD(cont);
      lcd.setCursor(0,0);
      lcd.print("POWER[%]");
      lcd.setCursor(0,1);
      lcd.print(value);
      RGBLED.setBrightness(value);
      if(lk.juge == true){
        analogWrite(MAINLED,value);
        for(fuli=0;fuli<8;fuli++){
          RGBLED.setPixelColor(rgbLED[fuli],rgb[7][0],rgb[7][1],rgb[7][2]);
        }
      }else{
        analogWrite(MAINLED,0);
        for(fuli=0;fuli<8;fuli++){
          RGBLED.setPixelColor(rgbLED[fuli],0,0,0);
        }
      }
      RGBLED.show();
    break;}
  }
  value = re;
}
