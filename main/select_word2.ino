//スパーク
const char suparkWORDS[] PROGMEM = {0xBD, 0xCA, 0xDF, 0xB0, 0xB8};
//メテオ
const char meteoWORDS[] PROGMEM = {0xD2, 0xC3, 0xB5};

const char *const splW1[] PROGMEM = {suparkWORDS,meteoWORDS,suparkWORDS};
const char *const moW1[] PROGMEM = {lightMODE,settingMODE};

void returnSelectWord1(int i){
  const int spellNum[3] = {3,5,3};
  //Serial.println(i);
  //Serial.println(gyou);
  switch(lk.mode){
    //LIGHT
    case 1:
    strcpy_P(wordsNAME, (char *)pgm_read_word(&(moW1[0])));
    gyouStart = 3;
    break;
    //MUSIC
    case 2:
    strcpy_P(wordsNAME, (char *)pgm_read_word(&(moW1[1])));
    gyouStart = 1;
    break;
    //スペルカード
    case 3:
    strcpy_P(wordsNAME, (char *)pgm_read_word(&(splW1[i])));
    gyouStart = spellNum[value];
    break;
    //SETTING
    case 4:
    strcpy_P(wordsNAME, (char *)pgm_read_word(&(moW1[1])));
    gyouStart = 1;
    break;
    default:
    gyouStart = 0;
    break;
  }
  Serial.println(wordsNAME);
}
