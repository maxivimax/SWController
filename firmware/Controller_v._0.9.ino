#define PIN_RELAY 11

#define _LCD_TYPE 2
#define MENU_points 6

#define MENU_pointType_SETVAL
#define MENU_pointType_SELECT
#define MENU_pointType_FUNCTIONCALLER
#define MENU_pointType_VIEWONLY 

#include <EEPROM.h>
#include <microWire.h>
#include <EncButton.h>
#include <LiquidCrystal.h>
#include <SimpleMenu.h>

byte customChar[8] = {
  B00000,
  B11011,
  B11011,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000};

const menuStruct PROGMEM points [MENU_structNum] = {
  {"SWC - Menu", 0, 0, 0},
  {"Run", pTYPE_view, 0, 0},
  {"M. Run", pTYPE_caller, 0, 0},
  {"Profiles", pTYPE_view, 0, 0},
  {"Min. time", pTYPE_view, 0, 0},
  {"Max. time", pTYPE_view, 0, 0},
  {"Info", pTYPE_caller,   0, 0},
};

LiquidCrystal LCD(2,3,4,5,6,7);
simpleMenu menu(points, LCD);
EncButton<EB_TICK, 8, 9, 10> enc;
EncButton<EB_TICK, 8, 9, 10> enc2;

float mRun = 0;

float maxRun = 1.5;
float minRun = 0.1;

void manualRun(){
  enc2.tick();
  
  LCD.setCursor(0, 0);
  LCD.print("M. Run");
  LCD.setCursor(0, 2);
  LCD.print(mRun);
  
  if (enc2.left() and mRun<maxRun){
    mRun=mRun+0.1;
  }
  
  if (enc2.right() and mRun>minRun){
    mRun=mRun-0.1;
  }

  if(enc2.click()){
      digitalWrite(PIN_RELAY, LOW);
      delay(mRun*1000);
      digitalWrite(PIN_RELAY, HIGH);
  }
}

//void minTime(){
//  enc2.tick();
//  
//  LCD.setCursor(0, 0);
//  LCD.print("Min. time");
//  LCD.setCursor(0, 2);
//  LCD.print(minRun);
//  
//  if (enc2.left()) {minRun=minRun+0.1;EEPROM.put(1003, minRun); }
//  if (enc2.right()){
//    minRun=minRun-0.1;EEPROM.put(1003, minRun); 
//  }
//}
//
//void maxTime(){
//  enc2.tick();
//  
//  LCD.setCursor(0, 0);
//  LCD.print("Max. time");
//  LCD.setCursor(0, 2);
//  LCD.print(maxRun);
//  
//  if (enc2.left()) {maxRun=maxRun+0.1;EEPROM.put(1002, maxRun); }
//  if (enc2.right() and not maxRun-0.1<0){
//    maxRun=maxRun-0.1;
//    EEPROM.put(1002, maxRun); 
//  }
//}
void inform(){
  LCD.setCursor(0, 0);
  LCD.print("by Maxivimax");
  LCD.createChar(0, customChar);
  LCD.setCursor(0, 2);
  LCD.print("With "); LCD.write((uint8_t)0);
}

void setup(){
  Serial.begin(9600);
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, HIGH);
  
  if (mRun==NAN){ 
    mRun = 0;
  }if (maxRun==NAN){ 
    maxRun = 1.5;
  }if (minRun==NAN){ 
    minRun = 0.1;
  }
  LCD.begin(16, 2);

  if (EEPROM.read(0) == 122) {
    MAX_ONDATA = EEPROM.read(2);
    MAX_ONDATA += (long)(EEPROM.read(3) << 8);
    VIS_ONDATA = EEPROM.read(4);
    VIS_ONDATA += (long)(EEPROM.read(5) << 8);
    mode0scr = EEPROM.read(6);
    bigDig = EEPROM.read(7);
    LED_BRIGHT = EEPROM.read(8);
    LCD_BRIGHT = EEPROM.read(9);
    LEDType = EEPROM.read(10);
  }
}

void loop(){
  enc.tick();
  
  uint8_t button = 0;
  
  if (enc.held())      button = 4; //esc
  else if (enc.left()) button = 3; //down
  else if (enc.right()) button = 2; //up
  else if (enc.hasClicks(1)) button = 1; //enter
  
  menu.control(button);

  menu.mainDisplay("SW Controller", "\r",
         "by Maxivimax");
  
  menu.showValue(1, "WIP");  
  menu.functionToCall(2, manualRun);      
//  menu.functionToCall(3, minTime);  
//  menu.functionToCall(4, maxTime);   
  menu.showValue(3, "WIP"); 
  menu.showValue(4, "WIP");
  menu.showValue(5, "WIP");    
  menu.functionToCall(6, inform);       
}      
