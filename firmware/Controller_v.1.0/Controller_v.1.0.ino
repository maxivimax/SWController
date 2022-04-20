// =============== НАСТРОЙКИ ===============
#define PIN_RELAY 11
#define MENU_points 7 // Тут задается кол-во пунктов меню(1-999...)

// =============== ДЛЯ SIMPLEMENU ===============
#define MENU_pointType_SETVAL
#define MENU_pointType_SELECT
#define MENU_pointType_FUNCTIONCALLER
#define MENU_pointType_VIEWONLY 

// =============== БИБЛИОТЕКИ ===============
#include <EEPROM.h>
#include <EncButton.h>
#include <microWire.h>
#include <LiquidCrystal.h>
#include <SimpleMenu.h>

// =============== Символы ===============
byte heart[8] = {B00000,B11011,B11011,B11111,B01110,B00100,B00000,B00000};
byte PeaceLeft[8] = {0b00000,0b00000,0b00001,0b00001,0b00001,0b00001,0b00000,0b00000};
byte PeaceCenter[8] = {0b01110,0b10101,0b00100,0b00100,0b00100,0b01010,0b10001,0b01110};
byte PeaceRight[8] = {0b00000,0b00000,0b10000,0b10000,0b10000,0b10000,0b00000,0b00000};
byte HeartLeft[8] = {0b00110,0b01111,0b11111,0b11111,0b01111,0b00111,0b00011,0b00001};
byte HeartRight[8] = {0b01100,0b11110,0b11111,0b11111,0b11110,0b11100,0b11000,0b10000};
byte CodeLeft[8] = {0b00010,0b00100,0b01000,0b10000,0b01000,0b00100,0b00010,0b00000};
byte CodeRight[8] = {0b01000,0b00100,0b00010,0b00001,0b00010,0b00100,0b01000,0b00000};

byte customChar[] = {
  B00000,
  B00100,
  B00100,
  B10101,
  B10001,
  B10001,
  B01110,
  B00000
};

// =============== ПУНКТЫ МЕНЮ ===============
// P.S. Первый пункт матрицы (points[0]) - заголовок меню
const menuStruct PROGMEM points [MENU_structNum] = {
  {"SWC", 0, 0, 0},
  {"P. Run", pTYPE_caller, 0, 0},
  {"M. run", pTYPE_caller, 0, 0},
  {"Add profile", pTYPE_caller, 0, 0},
  {"Min. time", pTYPE_caller, 0, 0},
  {"Max. time", pTYPE_caller, 0, 0},
  {"Info", pTYPE_caller,   0, 0},
  {"Reset EEPROM", pTYPE_caller,   0, 0},
};

// =============== ПРОФИЛИ ===============
float profiles[][2] = {};
int profilesCount = 0;
float newThickness = 0;
float newTime = 0;

// =============== ТЕКУЩИЙ ПРОФИЛЬ ===============
int strNum = 0;

// =============== ОБЪЯВЛЕНИЕ ВСЕГО ===============
LiquidCrystal LCD(2,3,4,5,6,7);
simpleMenu menu(points, LCD);
EncButton<EB_TICK, 8, 9, 10> enc;
EncButton<EB_TICK, 8, 9, 10> enc2;

// =============== ПЕРЕМЕННЫЕ ===============
float mRun = 0;
float maxRun = 0;
float minRun = 0;
bool easter = false;
bool thick = false;
bool ok = false;

// =============== ФУНКЦИЯ "ПРОФИЛЬНЫЙ ЗАПУСК" ===============
void profileR(){
  // Внутренний чек энкодера
  enc2.tick();
  
  // Вывод текста на экран
  LCD.setCursor(0, 0);
  LCD.print("P. Run");
  LCD.setCursor(0, 2);
  LCD.print(String(profiles[strNum][0]) + "mm, " + String(profiles[strNum][1]) + "s.");

  // Отслеживание поворота
  if (enc2.left() and strNum<profilesCount){
    strNum++;
  }
  else if (enc2.right() and strNum>0){
    strNum--;
  }

  // Запуск при клике
  if(enc2.click()){
    digitalWrite(PIN_RELAY, LOW);
    delay(profiles[strNum][1]*1000);
    digitalWrite(PIN_RELAY, HIGH);
  }
}

// =============== ФУНКЦИЯ "РУЧНОЙ ЗАПУСК" ===============
void manualRun(){
  // Внутренний чек энкодера
  enc2.tick();
  
  // Вывод текста на экран
  LCD.setCursor(0, 0);
  LCD.print("M. Run");
  LCD.setCursor(0, 2);
  LCD.print(mRun);
  
  // Отслеживание поворота
  if (enc2.left() and mRun<maxRun){
    mRun=mRun+0.1;
  }
  else if (enc2.right() and mRun>minRun and mRun>0){
    mRun=mRun-0.1;
  }

  // Запуск при клике
  if(enc2.click()){
    digitalWrite(PIN_RELAY, LOW);
    delay(mRun*1000);
    digitalWrite(PIN_RELAY, HIGH);
  }
}

// =============== ФУНКЦИЯ "ДОБАВИТЬ ПРОФИЛЬ" ===============
void addProfile(){
  delay(1);
  // Внутренний чек энкодера
  enc2.tick();
  
  // Вывод текста на экран
  if (ok){
    LCD.setCursor(0, 0);
    LCD.print("Saved");
    LCD.setCursor(0, 2);
    LCD.print("D. click for new");
  } else if (!thick) {
    LCD.setCursor(0, 0);
    LCD.print("Thickness");
    LCD.setCursor(0, 2);
    LCD.print(newThickness);
  } else { 
    LCD.setCursor(0, 0);
    LCD.print("Time");
    LCD.setCursor(0, 2);
    LCD.print(newTime);
  }
  // Отслеживание поворота
  if (!thick) {
    if (enc2.left()) {
      newThickness=newThickness+0.05;
    }
    else if (enc2.right() and newThickness>0){
      newThickness=newThickness-0.05;
    }

    // Далее при клике
    if(enc2.click()){
      thick = true;
    }
  } else if (thick) {
    if (enc2.left() and newTime<maxRun) {
      newTime=newTime+0.1;
    }
    else if (enc2.right() and newTime>0){
      newTime=newTime-0.1;
    }
 
    // Сохранение при клике
    if(enc2.click()){
      profilesCount++;
      profiles[profilesCount][0] = newThickness;
      profiles[profilesCount][1] = newTime;
      thick = false;
      ok = true;
      EEPROM.put(208, profiles);
      EEPROM.put(232, profilesCount);
    }
  }
  // Снова
  if(ok and enc.hasClicks(2)){
    ok = false;
  }
}

// =============== ФУНКЦИЯ "МИНИМАЛЬНОЕ ВРЕМЯ" ===============
void minTime(){
  // Внутренний чек энкодера
  enc2.tick();
  
  // Вывод текста на экран
  LCD.setCursor(0, 0);
  LCD.print("Min. time");
  LCD.setCursor(0, 2);
  LCD.print(minRun);
  
  // Отслеживание поворота
  if (enc2.left() and minRun<maxRun) {
    minRun=minRun+0.1;
    // Приравнивание изначального времени для ручного запуска к минимуму
    mRun = minRun;
    EEPROM.put(192, minRun); 
  }
  if (enc2.right() and minRun>0){
    minRun=minRun-0.1;
    // Приравнивание изначального времени для ручного запуска к минимуму
    mRun = minRun;
    EEPROM.put(192, minRun); 
  }
}

// =============== ФУНКЦИЯ "МАКСИМАЛЬНОЕ ВРЕМЯ" ===============
void maxTime(){
  // Внутренний чек энкодера
  enc2.tick();

  // Вывод текста на экран
  LCD.setCursor(0, 0);
  LCD.print("Max. time");
  LCD.setCursor(0, 2);
  LCD.print(maxRun);

  // Отслеживание поворота
  if (enc2.left()) {
    maxRun=maxRun+0.1;
    EEPROM.put(200, maxRun); 
  }
  if (enc2.right() and maxRun>minRun){
    maxRun=maxRun-0.1;
    EEPROM.put(200, maxRun); 
  }
}

// =============== ФУНКЦИЯ "ИНФОРМАЦИЯ" ===============
void inform(){
  // Внутренний чек энкодера
  enc2.tick();
  
  // Вывод текста на экран
  if(easter == true){
    // Создание символов
    LCD.createChar(0, PeaceLeft);
    LCD.createChar(1, PeaceCenter);
    LCD.createChar(2, PeaceRight);
    LCD.createChar(3, HeartLeft);
    LCD.createChar(4, HeartRight);
    LCD.createChar(5, CodeLeft);
    LCD.createChar(6, CodeRight);

    // Вывод первой строки(Символы)
    LCD.setCursor(1, 0);
    LCD.write((uint8_t)0);
    LCD.setCursor(2, 0);
    LCD.write((uint8_t)1);
    LCD.setCursor(3, 0);
    LCD.write((uint8_t)2);
    LCD.setCursor(7, 0);
    LCD.write((uint8_t)3);
    LCD.setCursor(8, 0);
    LCD.write((uint8_t)4);
    LCD.setCursor(12, 0);
    LCD.write((uint8_t)5);
    LCD.setCursor(13, 0);
    LCD.write((uint8_t)6);

    // Вывод второй строки(Слова)
    LCD.setCursor(0, 1);
    LCD.print("Peace Love Code");
  } else {
    // Вывод стандартного текста на экран
    LCD.setCursor(0, 0);
    LCD.print("by Maxivimax");
    LCD.createChar(0, heart);
    LCD.setCursor(0, 2);
    LCD.print("With "); LCD.write((uint8_t)0);
  }

  // Включение/выключение пасхалки при 5-ом клике
  if(enc2.hasClicks(5)) easter = !easter;
}

// =============== СБРОС ДАННЫХ ===============
void resetEEPROM(){
  enc2.tick();
  
  LCD.setCursor(0, 0);
  LCD.print("Reset EEPROM");
  LCD.setCursor(0, 2);
  LCD.print("HT for reset");
  
  if (enc.leftH() or enc.rightH()) {
    LCD.setCursor(0, 0);
    LCD.print("Reset settings");
    for (byte i = 192; i < 255; i++) {
      EEPROM.put(i, 0);
      Serial.println(i);
    }
    LCD.setCursor(0, 1);
    LCD.print("Reset done");
  }
}

// =============== ПЕРВИЧНЫЕ ДЕЙСТВИЯ ===============
void setup(){
  // Инициализация монитора порта
  Serial.begin(9600);
  
  // Инициализация реле
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, HIGH);

  // Инициализация дисплея
  LCD.begin(16, 2);
  
  // Восстановление значений переменных из EEPROM
  EEPROM.get(192, minRun);
  EEPROM.get(200, maxRun);
  EEPROM.get(208, profiles);
  EEPROM.get(232, profilesCount);
}

// =============== ЦИКЛ ===============
void loop(){
  // Проверка энкодера
  enc.tick();
  
  // Переменная с необходимым действием для меню
  uint8_t direct = 0;

  // Настройка соотношения изменения энкодера с действиями в меню
  if (enc.held())      direct = 4; //назад
  else if (enc.left()) direct = 3; //вниз
  else if (enc.right()) direct = 2; //вверх
  else if (enc.hasClicks(1)) direct = 1; //выбор

  // Подключение переменной direct к управлению дисплеем
  menu.control(direct);

  // Настройка текста на главном экране
  menu.mainDisplay("SW Controller", "\r",
         "by Maxivimax");

  // Функции для пунктов меню
  menu.functionToCall(1, profileR);  
  menu.functionToCall(2, manualRun);  
  menu.functionToCall(3, addProfile);      
  menu.functionToCall(4, minTime);  
  menu.functionToCall(5, maxTime);      
  menu.functionToCall(6, inform); 
  menu.functionToCall(7, resetEEPROM); 
}      
