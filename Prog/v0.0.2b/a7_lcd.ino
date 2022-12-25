
void Screen_01() {
  //lcd.backlight();

  //Первая колонка
  lcd.setCursor(0, 0);
  lcd.print("TO:");
  lcd.setCursor(0, 1);
  lcd.print("TI:");
  lcd.setCursor(0, 2);
  lcd.print("HO:");
  lcd.setCursor(0, 3);
  lcd.print("HI:");

  //Вторая колонка
  lcd.setCursor(8, 0);
  lcd.print("T1:");
  lcd.setCursor(8, 1);
  lcd.print("T2:");
  lcd.setCursor(8, 2);
  lcd.print("T3:");
  lcd.setCursor(8, 3);
  lcd.print("T4:");

  //Третья колонка
  lcd.setCursor(16, 0);
  lcd.print("T");
  lcd.setCursor(16, 1);
  lcd.print("T");
  lcd.setCursor(16, 2);
  lcd.print("F");
  lcd.setCursor(16, 3);
  lcd.print("F");
}

void LCD_Screen_01_INFO() {
  if (millis() - LCD_lastTime > LCD_Timer) {
    LCD_lastTime = millis();
    lcd.clear();

    //Первая колонка
    lcd.setCursor(3, 0);
    lcd.print(t_11, 1);
    lcd.setCursor(3, 1);
    lcd.print(t_22, 1);
    lcd.setCursor(3, 2);
    lcd.print(h_11, 1);
    lcd.setCursor(3, 3);
    lcd.print(h_22, 1);

    //Вторая колонка
    lcd.setCursor(11, 0);
    lcd.print(a, 1);
    lcd.setCursor(11, 1);
    lcd.print(a, 1);
    lcd.setCursor(11, 2);
    lcd.print(a, 1);
    lcd.setCursor(11, 3);
    lcd.print(a, 1);

    //Третья колонка
    lcd.setCursor(17, 0);
    lcd.print(BED_Temperature);
    lcd.setCursor(17, 1);
    lcd.print(a, 1);
    lcd.setCursor(17, 2);
    lcd.print(FAN_Speed);
    lcd.setCursor(17, 3);
    lcd.print(a, 1);
  }
}