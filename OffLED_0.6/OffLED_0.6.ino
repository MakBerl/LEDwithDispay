//РАЗБОРКИ С ДИСПЛЕЕМ
//---- ПИНЫ ----
byte SCLK = 6;
byte RCLK = 5;
byte DIO = 2;
#include <TM74HC595Display.h>
#include <TimerOne.h>
TM74HC595Display disp(SCLK, RCLK, DIO);
unsigned char SYM[31];//Массив символов

//LED ЛЕНТА
#define CURRENT_LIMIT 3000  // лимит по току в миллиамперах, автоматически управляет яркостью (пожалей свой блок питания!) 0 - выключить лимит
#define NUM_LEDS 119         // количсетво светодиодов в одном отрезке ленты
#define NUM_STRIPS 1        // количество отрезков ленты (в параллели)
#define LED_PIN 13           // пин ленты 

#include <FastLED.h>
CRGB leds[NUM_LEDS];
CRGBPalette16 gPal;

float time=0;//типа счетчик времени
unsigned long timing;


//

uint8_t MODE_L=0, MRGB[3]={0,0,0},
BRIGHT_MAX=150,BRIGHT_MIN=10,lenght=(BRIGHT_MAX-BRIGHT_MIN)/2,hight=(BRIGHT_MAX+BRIGHT_MIN)/2;
byte HUE=0;
uint8_t SPEED=10;
float SPEEDfl=0;



//////////////////////////
//ОРГАНЫ УПРАВЛЕНИЯ
#define POT 0                     // Подключение к 0-му аналоговому входу потенциометра
#define UP_pin 12
#define DOWN_pin 3
#define OK_pin 11
#define BACK_pin 4
//Наверное надо будет расписать еще состояния пинов?
bool UP = 0; 
bool DOWN = 0;
bool OK = 0;
bool BACK = 0;
//Для перехода по менюшкам
bool InDarkMode=0;
bool InMenu=1;
bool InSettings = 0;
bool InColorRGBSet = 0;
bool InColorHUESet = 0;
bool InRedSet=0;
bool InBlueSet=0;
bool InGreenSet=0;
//bool InHueSet=0;
//bool InColorHUESet = 0;
bool InSpeedSet = 0;
bool InBrightMaxSet = 0;
bool InBrightMinSet = 0;
bool InSplitSet = 0;
bool placeholder = 0;
bool InEffects = 0;
bool UseRGB=0;

/////////////////////////////
//Изменяемые настройки ленты
//








void MENU(){
  if(InMenu){
  int val = analogRead(POT);
  Serial.print(val);
  Serial.print("-->");
  int mode = map(val, 0, 512, 1, 0);
  Serial.println(mode);
  switch (mode)
  {    
  case 0://Effects
    ShowSign(4,5,5,15);//EffS
     Obrabotka_knopok_menu(InDarkMode,InMenu,InEffects);
    break;
  case 1://Settings
  ShowSign(15,4,16,16);//Sett
  Obrabotka_knopok_menu(InDarkMode,InMenu,InSettings);
    break;
  }
}
}
void SETTINGS(){//Сюда впендюрь useRBG
  if(InSettings){
  int val = analogRead(POT);
  Serial.print(val);
  Serial.print("-->");
  int mode = map(val, 0, 950, 5, 0);
  Serial.println(mode);
  switch (mode)
  {    
  case 0://ColorRGB
    UseRGB=1;
    ShowSign(20,6,1,30);//EffS
     Obrabotka_knopok_menu(InMenu,InSettings,InColorRGBSet);
    break;
  case 1://ColorHUE
     UseRGB=0;
     ShowSign(7,17,4,30);//EffS
     Obrabotka_knopok_menu(InMenu,InSettings,InColorHUESet);
    break;
  case 2://Speed
  ShowSign(15,13,4,3);//Sped
  Obrabotka_knopok_menu(InMenu,InSettings,InSpeedSet);
    break;
    case 3://BrightMax
    ShowSign(1,20,11,0);//Brma
     Obrabotka_knopok_menu(InMenu,InSettings,InBrightMaxSet);
    break;
    case 4://BrightMin
    ShowSign(1,20,11,8);//Brmi
     Obrabotka_knopok_menu(InMenu,InSettings,InBrightMinSet);
    break;
    case 5://Split
    ShowSign(15,13,10,16);//SPLT
     Obrabotka_knopok_menu(InMenu,InSettings,InSplitSet);
    break;
  }
}
}

void EFFECTS(){
  if(InEffects){
  int val = analogRead(POT);
  Serial.print(val);
  Serial.print("-->");
  int mode = map(val, 0, 970, 5, 0);
  Serial.println(mode);
  MODE_L=mode;
  switch (mode)
  {//Названия
  case 0://Color
    ShowSign(2,10,20,30);//Color
    //Тут тоже темповские штуки поставить для перемотки режима
     Obrabotka_knopok_menu(InMenu,InEffects,InDarkMode);
    break;
  case 1://Puls
  ShowSign(13,17,10,15);//EffS
  Obrabotka_knopok_menu(InMenu,InEffects,InDarkMode);
    break;
    case 2://Colors
    ShowSign(2,10,20,15);//EffS
     Obrabotka_knopok_menu(InMenu,InEffects,InDarkMode);
    break;
    case 3://Rainbow
    ShowSign(20,0,8,11);//EffS
     Obrabotka_knopok_menu(InMenu,InEffects,InDarkMode);
    break;
    case 4://Fire
    ShowSign(5,8,20,4);//EffS
     Obrabotka_knopok_menu(InMenu,InEffects,InDarkMode);
    break;
        case 5://
    ShowSign(4,5,5,26);//EffS
     Obrabotka_knopok_menu(InMenu,InEffects,InDarkMode);
    break;
  }
}
}

void COLORRGB(){
  if(InColorRGBSet){
  int val = analogRead(POT);
  Serial.print(val);
  Serial.print("-->");
  int mode = map(val, 0, 1000, 2, 0);
  Serial.println(mode);
  switch (mode)
  {    
  case 0://Red
    ShowSign(30,20,4,3);//EffS
     Obrabotka_knopok_menu(InSettings,InColorRGBSet,InRedSet);
    break;
  case 1://Green
     ShowSign(6,20,4,11);//EffS
     Obrabotka_knopok_menu(InSettings,InColorRGBSet,InGreenSet);
    break;
  case 2://Blue
  ShowSign(1,10,17,4);//Sped
  Obrabotka_knopok_menu(InSettings,InColorRGBSet,InBlueSet);
    break;
  }
  }
}

bool CanChange=1;
int temp;
void Obrabotka_knopok_menu2(bool &prev,bool &current, bool &next, uint8_t &chto_menyaem, uint8_t &chem_menyaem)//Mode_l тут вообще не нужен
{
  {
  //Test
  if(CanChange) //наш флажок
    {
      temp=chto_menyaem;
      CanChange=0;
    }
  //
  chto_menyaem=chem_menyaem;
  OK = !digitalRead(OK_pin);
    BACK = !digitalRead(BACK_pin);
    if (OK)
    {
     delay(200);
     next=1;    
     current=0;
     //Test2
     //MODE_L=mode;
     CanChange=1;
    }
    if (BACK)
    {
      delay(200);
      prev=1;
      current=0;
    //Test
      chto_menyaem=temp;
      CanChange=1;
    //
    }
    }
  }


uint8_t changefunvalue;
  uint8_t WhatChange;
void CHANGEFUN()
{
  
  if(InBrightMaxSet || InBrightMinSet ||
  InBlueSet || InGreenSet || InRedSet || 
  InSpeedSet || InColorHUESet)
  {
//ShowLetterWithPointAndNumbers
  int val = analogRead(POT);
  changefunvalue = map(val, 0, 970, 255, 0);
  
  }
if(InColorHUESet)
  {
  ShowLetter(7);
  Obrabotka_knopok_menu2(InSettings,InColorHUESet,InSettings,HUE,changefunvalue);
  }
  if(InSpeedSet)
  {
    SPEEDfl=SPEED/5;
  ShowLetter(15);
  Obrabotka_knopok_menu2(InSettings,InSpeedSet,InSettings,SPEED,changefunvalue);
    }
  if(InRedSet)
  {//Другие prev и next
    ShowLetter(20);
  Obrabotka_knopok_menu2(InColorRGBSet,InRedSet,InColorRGBSet,MRGB[0],changefunvalue);
    }
  if(InGreenSet)
  {
    ShowLetter(6);
  Obrabotka_knopok_menu2(InColorRGBSet,InGreenSet,InColorRGBSet,MRGB[1],changefunvalue);
    }
  if(InBlueSet)
  {
    ShowLetter(1);
  Obrabotka_knopok_menu2(InColorRGBSet,InBlueSet,InColorRGBSet,MRGB[2],changefunvalue);
    }
  if(InBrightMinSet)
  {
    ShowLetter(8);
  Obrabotka_knopok_menu2(InSettings,InBrightMinSet,InSettings,BRIGHT_MIN,changefunvalue);
          lenght=(BRIGHT_MAX-BRIGHT_MIN)/2;
        hight=(BRIGHT_MAX+BRIGHT_MIN)/2;
    }
  if(InBrightMaxSet)
  {
    ShowLetter(0);
  Obrabotka_knopok_menu2(InSettings,InBrightMaxSet,InSettings,BRIGHT_MAX,changefunvalue);
         lenght=(BRIGHT_MAX-BRIGHT_MIN)/2;
        hight=(BRIGHT_MAX+BRIGHT_MIN)/2;
    }
  
 }

void ShowLetter(int i){
  //Serial.print("Я здесь");
  disp.set(SYM[i]-0x80,3);//E//Замени функцией
  disp.digit4(changefunvalue);
}

void ShowSign(int i1,int i2,int i3,int i4)
{
 // Serial.print("Я здесь");
    disp.set(SYM[i1],3);//E//Замени функцией
    disp.set(SYM[i2],2);//f
    disp.set(SYM[i3],1);//f
    disp.set(SYM[i4],0);//s
}

/*


*///
/*//Мб просто след функцию модифицировать и что меняем и на что меняем поставить -1 по умолчанию и на ифах не использвать это
void primenenie_izmeneniy_znachenyi(bool& chto_menyaem,bool& chem_menyaem, bool &prev, bool &current,){
//  //Также как с пред начало, но в итоге 
    OK = !digitalRead(OK_pin);
    BACK = !digitalRead(BACK_pin);
    if (OK)
    {
     delay(200);
     chto_menyaem=chem_menyaem;    
     current=0;
    }
    if (BACK)
    {
      delay(200);
      prev=1;
      current=0;
    }
    }
*/
//  }
//void for_effects(bool& chto_vkluchaem, bool& prev)//Просто в дарк мод переводим, данная функция не нужна)
//{}//Делаем через switch?
//Все зануляй и в свиче врубай 1



    void Obrabotka_knopok_menu(bool &prev,bool &current, bool &next){
    OK = !digitalRead(OK_pin);
    BACK = !digitalRead(BACK_pin);
    if (OK)
    {
     delay(200);
     next=1;    
     current=0;
    }
    if (BACK)
    {
      delay(200);
      prev=1;
      current=0;
    }
    }

/////////////////
bool clr=1;
void DARKMODE()
{

  
  if(InDarkMode)
  {
    if(clr)
      disp.clear();
    clr=0;
    OK = !digitalRead(OK_pin);
    if (OK)
    {
     delay(200);
     InDarkMode=0;    
     InMenu=1;
    }
  }
  else
  {
  delay(50);
  disp.clear();
  clr=1;
  }
}
//////////////////



void timerIsr() {   // прерывание таймера
  disp.timerIsr();  // пнуть дисплей
}

void symbols() {
  // буквы //Вычти 80 чтоб было с точкой
  SYM[0] = 0x88; //A
  SYM[1] = 0x83; //b
  SYM[2] = 0xC6; //C
  SYM[3] = 0xA1; //d
  SYM[4] = 0x86; //E
  SYM[5] = 0x8E; //F
  SYM[6] = 0xC2; //G
  SYM[7] = 0x89; //H
  SYM[8] = 0xF9; //I
  SYM[9] = 0xF1; //J
  SYM[10] = 0xC7; //L
  SYM[11] = 0xAb; //n
  SYM[12] = 0xC0; //O
  SYM[13] = 0x8C; //P
  SYM[14] = 0x98; //q
  SYM[15] = 0x92; //S
  SYM[16] = 0x87; //t
  SYM[17] = 0xC1; //U
  SYM[18] = 0x91; //Y
  SYM[19] = 0b11110111; // _
  SYM[20]= 0xcc; //r
  SYM[21] = 0xF9; //1
  SYM[22] = 0xA4; //2
  SYM[23] = 0xB0; //3
  SYM[24] = 0x99; //4
  SYM[25] = 0x92; //5
  SYM[26] = 0x82; //6
  SYM[27] = 0xF8; //7
  SYM[28] = 0x80; //8
  SYM[29] = 0x90; //9
  SYM[30]= 0xFF;//empty
}

byte hue;
void LED_control()
{ 
  //if(Timer.isReady())
  //{
  if (millis() - timing > SPEED){
    timing=millis();
  switch (MODE_L)
  {
  //case 4: fire();
    //break;
  case 2: colors();
    break;
  case 3: rainbow();
    break;
  case 0: FillColor();
    break;
  case 1: Pulse();
 // }
  }
  }
}
// залить все
void fillAll(CRGB newcolor) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = newcolor;
  }
}

void colors()//доработай скорость
{
  delay(SPEED);
  hue += 2;
  CRGB thisColor = CHSV(hue, 255, 255);
  fillAll(CHSV(hue, 255, 255));
}
void rainbow()//доработай скорость
{
  delay(SPEED);
  hue += 2;
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CHSV((byte)(hue + i * float(255 / NUM_LEDS)), 255, 255);
}
void FillColor()
{
  //fillAll(CRGB(RGB[0],RGB[1],RGB[2]));
  if(UseRGB)
  {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = MRGB[0];
    leds[i].g = MRGB[1];
    leds[i].b = MRGB[2];
  }
  }
  else
  fillAll(CHSV(HUE, 255, 255));
}
//End
void Pulse()
{ //Впиньдюрь таймер
  delay(SPEED);
   FastLED.setBrightness(hight+lenght*sin(time*5));
     if(UseRGB){
     for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = MRGB[0];
    leds[i].g = MRGB[1];
    leds[i].b = MRGB[2];
   }}
   else
   {
    fillAll(CHSV(HUE, 255, 255));
    }
   time=time+0.005;
}

void setup() {
  symbols();                         // объявление пачки символов для работы дисплея
  Timer1.initialize(1500);           // установка таймера на каждые 1500 микросекунд
  Timer1.attachInterrupt(timerIsr);  // запуск таймера

  pinMode(UP_pin, INPUT_PULLUP); //Сказали что на жтих пинах кнопки
  pinMode(DOWN_pin, INPUT_PULLUP); 
  pinMode(OK_pin, INPUT_PULLUP); 
  pinMode(BACK_pin, INPUT_PULLUP); 
   
  Serial.begin(9600);


FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT / NUM_STRIPS);
  FastLED.setBrightness(BRIGHT_MAX);
  FastLED.show();

}

void loop() {
  DARKMODE();
  CHANGEFUN();
  COLORRGB();
  EFFECTS();
  SETTINGS();
  MENU();
  /*
  Serial.print("HUE -> ");
  Serial.println(HUE);
  Serial.print("SPEED -> ");
  Serial.println(SPEED);
    Serial.print("R-> ");
  Serial.println(MRGB[0]);  
    Serial.print("G-> ");
  Serial.println(MRGB[1]);    
  Serial.print("B-> ");
  Serial.println(MRGB[2]);
  Serial.print("BRIGHT_MAX-> ");
  Serial.println(BRIGHT_MAX);
  */
  //InDarkMode
  //delay(50);
  //disp.clear();

if (MODE_L!=5)
    FastLED.setBrightness(BRIGHT_MAX);
  LED_control();
  FastLED.show();

}
