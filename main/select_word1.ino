const char nomalWORDS[] PROGMEM = "NORMAL";
const char colorWORDS[] PROGMEM = "COLOR";
const char fullWORDS[] PROGMEM = "FULL-LED";
const char motionWORDS[] PROGMEM = "MOTION";
const char songWORDS[] PROGMEM = "SONG";
const char volumeWORDS[] PROGMEM = "VOLUME";
//ナロー
const char naroWORDS[] PROGMEM = {0xC5, 0xDB, 0xB0};
//ドラゴン
const char doragonWORDS[] PROGMEM = {0xC4, 0xDE, 0xD7, 0xBA, 0xDE, 0xDD};
//マスター
const char masterWORDS[] PROGMEM = {0xCF, 0xBD, 0xC0, 0xB0};
const char timeWORDS[] PROGMEM = "TIME";
const char contrastWORDS[] PROGMEM = "CONTRAST";
const char backWORDS[] PROGMEM = "BACK";

const char *const slW0[] PROGMEM = {nomalWORDS,colorWORDS,fullWORDS,motionWORDS};
const char *const smW0[] PROGMEM = {songWORDS,volumeWORDS};
const char *const ssW0[] PROGMEM = {naroWORDS,doragonWORDS,masterWORDS};
const char *const seW0[] PROGMEM = {timeWORDS,contrastWORDS,backWORDS}; 

void returnSelectWord0(int i){
  char ans[20];
  //Serial.println(i);
  //Serial.println(gyou);
  switch(lk.mode){
    //LIGHT
    case 1:
    strcpy_P(wordsNAME, (char *)pgm_read_word(&(slW0[i])));
    break;
    //MUSIC
    case 2:
    strcpy_P(wordsNAME, (char *)pgm_read_word(&(smW0[i])));
    break;
    //スペルカード
    case 3:
    strcpy_P(wordsNAME, (char *)pgm_read_word(&(ssW0[i])));
    break;
    //SETTING
    case 4:
    strcpy_P(wordsNAME, (char *)pgm_read_word(&(seW0[i])));
    break;
    default:
    break;
  }
  Serial.println(wordsNAME);
}
