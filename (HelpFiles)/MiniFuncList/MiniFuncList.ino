#include <EncButton.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);
EncButton<EB_TICK, 8, 9, 10> enc;

byte heart[8] = {
  B00000,
  B11011,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000};

void resetEEPROM(){
  enc2.tick();
  
  LCD.setCursor(0, 0);
  LCD.print("Reset EEPROM");
  LCD.setCursor(0, 2);
  LCD.print("HRT for reset");
  
  if (enc.leftH()) {
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

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  lcd.createChar(0, heart);
  
  lcd.setCursor(0, 0);
  for(int i=1; i<9; i++){
    lcd.write((uint8_t)0);
    lcd.write((uint8_t)0);
  }
}

void loop() {
  enc.tick();

  // =============== ЭНКОДЕР ===============
  if (enc.turn()) {
    Serial.println("Поворот");
    
    lcd.setCursor(0, 1);
    lcd.print("");
    lcd.setCursor(1, 1);
    lcd.print("");
    lcd.setCursor(2, 1);
    lcd.print("");
    lcd.setCursor(0, 1);
    lcd.print(enc.counter);
    Serial.println(enc.fast());
    Serial.println(enc.getDir());
  }

  if (enc.turnH()) {
    Serial.println("Удержание + поворот");

    lcd.setCursor(3, 1);
    lcd.print("");
    lcd.setCursor(4, 1);
    lcd.print("");
    lcd.setCursor(5, 1);
    lcd.print("");
    lcd.setCursor(4, 1);
    lcd.print(enc.counter);
    Serial.println(enc.fast());
    Serial.println(enc.getDir());
  }

  if (enc.left()) Serial.println("Налево");
  if (enc.right()) Serial.println("Направо");
  if (enc.leftH()) Serial.println("Нажатый налево");
  if (enc.rightH()) Serial.println("Нажатый направо");

  // =============== КНОПКА ЭНКОДЕРА ===============
  if (enc.click()){ 
    lcd.setCursor(10, 1);
    lcd.print(enc.clicks);
  }
  if (enc.press()) Serial.println("Нажатие");
  if (enc.release()) Serial.println("Отпускание");

  if (enc.held()) Serial.println("Удержаниие");

  if (enc.hasClicks()) {
    Serial.print("Кликов: ");
    
    lcd.setCursor(7, 1);
    lcd.print(enc.clicks);
  }
}
