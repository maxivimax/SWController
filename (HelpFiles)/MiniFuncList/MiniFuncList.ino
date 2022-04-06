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
  // обычный поворот
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
    //Serial.println(enc.fast());   // проверить быстрый поворот
    //Serial.println(enc.getDir()); // направление поворота
  }

  // "нажатый поворот"
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
    //Serial.println(enc.fast());   // проверить быстрый поворот
    //Serial.println(enc.getDir()); // направление поворота
  }

  //if (enc.left()) Serial.println("Налево");     // поворот налево
  //if (enc.right()) Serial.println("Направо");   // поворот направо
  //if (enc.leftH()) Serial.println("Нажатый налево");   // нажатый поворот налево
  //if (enc.rightH()) Serial.println("Нажатый направо"); // нажатый поворот направо

  // =============== КНОПКА ===============
  if (enc.click()){ 
    lcd.setCursor(10, 1);
    lcd.print(enc.clicks);
  }
  if (enc.press()) Serial.println("Нажатие");
  if (enc.release()) Serial.println("Отпускание");

  if (enc.held()) Serial.println("Удержаниие");

  // вывести количество кликов
  if (enc.hasClicks()) {
    Serial.print("Кликов: ");
    
    lcd.setCursor(7, 1);
    lcd.print(enc.clicks);
  }
}
