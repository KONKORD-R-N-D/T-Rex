void setup() {
  //Подключение систем
  dht_22.begin();
  dht_11.begin();
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  //Режим работы пинов
  pinMode(RED_Button_pin, INPUT_PULLUP);
  pinMode(BLUE_Button_pin, INPUT_PULLUP);
  pinMode(YELLOW_Button_pin, INPUT_PULLUP);


  digitalWrite(2, HIGH);
  pinMode(2, OUTPUT);
}

void loop() {
  RED_Button();
  YELLOW_Button();
  BLUE_Button();
  Temp_average();

  //Считывание показаний с датчиков
  DHT11_Read();
  DHT22_Read();

  //Вывод информации на LCD
  Screen_01();
  LCD_Screen_01_INFO();

  //DEBBUG встроенных функций
  //Timer_debbug();
  //Button_debbug();
  //NTC_debbug();
  NTC_Plotter();
}
