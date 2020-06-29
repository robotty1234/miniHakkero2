//定義
#define RGBLED_OUTPIN 8
#define NUMRGBLED 8
#define MAINLED 6
#define TIME 5
#define MAINSW 12
#define BACKSW A1
#define BACKLIGHTSW A3
#define MULTISW A2
#define JACKSW 7
#define ENC_A 2
#define ENC_B 3
#define SWT 5
#define LONG 1500
#define SHORT 200
#define MODE 5
#define BACKLIGHT 9
#define GANNEN 2019
#define BATTERY A0
#define ENCBLUE 10
#define ENCRED 11
//グローバル変数
volatile byte pos;
volatile int  value;
int value2 = -1;
int mode = 5;//時計、ライト、音楽、スペルカード、設定
volatile int cont = 30;
char words[20];
char words1[20];
int selectManue[MODE] = {0,4,2,3,3};
int secs,mins,hours,days,months,years;
boolean swbool = false;
int gyouStart;
int backLED = 150;
float battery;
float batPasent;
char wordsNAME[8];

//モード変換用の構造体
struct LINK{
  int mode;
  int select;
  int val;
  boolean juge;
};
//追加分の構造体
struct plus{
  int select;
  int val;
};
//モード変換用の構造体の初期化
LINK lk = {1,-1,-1,false};
//コンパイルの都合上
plus add = {-1,-1};
//スイッチピンの配列
const int sw[SWT] = {MAINSW,BACKSW,BACKLIGHTSW,MULTISW,JACKSW};
//時刻設定
int howTime[6] = {2019,3,17,0,0,0};//年、月、日、時、分、秒
//LED
const int rgb[][3] = {
  {225,40,25},//朱色(赤)
  {100,0,100},//紫
  {0,0,225},//青
  {15,82,188},//シアン(水色)
  {200,200,0},//黄
  {255,94,25},//柿色
  {0,100,0},//緑色
  {250,250,250},//白
  {255,0,255}//マゼンタ
};
//RGBLEDピン配置
const int rgbLED[] = {0,7,6,5,4,3,2,1,0};
//虹色
const int rainbow[8] = {0,4,5,6,3,2,1,8};
//関数プロトタイプ宣言
void ENC_READ();
void beginLCD(int i);
void transPrint(int ans,int valval);
void printWatch(int i);
void printMODE(int i,int modess,char *a);
void returnModeWord(int i);
void setValue();
void forceValue(int math);
void readSerial(byte key,int longs);
void mainSW(int how);
void backSW(int how);
void backlightSW(int how);
void multiSW(int how);
void jyackSW(int how);
void printSELECT(int i,int modess,char *a);
void returnSelectWord0(int i);
void returnSelectWord1(int i);
void systemTask();
void settingTask();
void lightTask();
bool backLightLED = false;
void batteryLED();
void printYear(int i);
void printBATTERY(int i);
//フルカラーLEDを使う設定
Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(NUMRGBLED, RGBLED_OUTPIN, NEO_RGB + NEO_KHZ800);
//LCDを使う設定
ST7032 lcd;
//rtcを使う設定
DS1307 rtc;
