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
  {"SWC", 0, 0, 0},
  {"Run", pTYPE_view, 0, 0},
  {"M. Run", pTYPE_caller, 0, 0},
  {"Profiles", pTYPE_view, 0, 0},
  {"Min. time", pTYPE_caller, 0, 0},
  {"Max. time", pTYPE_caller, 0, 0},
  {"Info", pTYPE_caller,   0, 0},
};

LiquidCrystal LCD(2,3,4,5,6,7);
simpleMenu menu(points, LCD);
EncButton<EB_TICK, 8, 9, 10> enc;
EncButton<EB_TICK, 8, 9, 10> enc2;

float mRun = 0;

float maxRun = 0;
float minRun = 0;

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

void minTime(){
  enc2.tick();
  
  LCD.setCursor(0, 0);
  LCD.print("Min. time");
  LCD.setCursor(0, 2);
  LCD.print(minRun);
  
  if (enc2.left()) {minRun=minRun+0.1;EEPROM.put(192, minRun); }
  if (enc2.right()){
    minRun=minRun-0.1;EEPROM.put(192, minRun); 
  }
}

void maxTime(){
  enc2.tick();
  
  LCD.setCursor(0, 0);
  LCD.print("Max. time");
  LCD.setCursor(0, 2);
  LCD.print(maxRun);
  
  if (enc2.left()) {maxRun=maxRun+0.1;EEPROM.put(200, maxRun); }
  if (enc2.right() and not maxRun-0.1<0){
    maxRun=maxRun-0.1;
    EEPROM.put(200, maxRun); 
  }
}
void inform(){
  LCD.setCursor(0, 0);
  LCD.print("by Maxivimax");
  LCD.createChar(0, customChar);
  LCD.setCursor(0, 2);
  LCD.print("With "); LCD.write((uint8_t)0);
}

//void resetEEPROM(){
//  enc2.tick();
//  
//  LCD.setCursor(0, 0);
//  LCD.print("Reset EEPROM");
//  LCD.setCursor(0, 2);
//  LCD.print("HRT for reset");
//  
//  if (enc.leftH()) {
//    LCD.setCursor(0, 0);
//    LCD.print("Reset settings");
//    for (byte i = 192; i < 255; i++) {
//      EEPROM.put(i, 0);
//      Serial.println(i);
//    }
//    LCD.setCursor(0, 1);
//    LCD.print("Reset done");
//  }
//}

void setup(){
  enc2.tick();
  Serial.begin(9600);
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, HIGH);
  EEPROM.get(192, minRun);
  EEPROM.get(200, maxRun);
  
  LCD.begin(16, 2);

  for (byte i = 192; i < 255; i++) {
    float test = 0;
    Serial.println(EEPROM.get(i, test));
    Serial.println(i);
    Serial.println(test);
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
  menu.showValue(3, "WIP");     
  menu.functionToCall(4, minTime);  
  menu.functionToCall(5, maxTime);      
  menu.functionToCall(6, inform); 
}      
