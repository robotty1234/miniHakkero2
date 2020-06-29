const char watchMODE[] PROGMEM = "WATCH";
const char lightMODE[] PROGMEM = "LIGHT";
const char musicMODE[] PROGMEM = "MUSIC";
const char spellMODE[] PROGMEM = "SPELL";
const char settingMODE[] PROGMEM = "SETTING";

const char *const modeNAME[] PROGMEM = {watchMODE,lightMODE,musicMODE,spellMODE,settingMODE}; 

void returnModeWord(int i){
  strcpy_P(wordsNAME, (char *)pgm_read_word(&(modeNAME[i])));
  //strcpy_P(ans, pgm_read_word(&(mW[i])));
  Serial.println(wordsNAME);
}
