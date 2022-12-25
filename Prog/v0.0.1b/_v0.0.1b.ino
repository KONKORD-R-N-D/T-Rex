//Поджключение библиотек
#include "DHT.h"
#include "LiquidCrystal_I2C.h"
#include "Wire.h"

//Объявление пинов сенсоров

//Датчики температуры NTC3950
#define SERIAL_R1 108000     // сопротивление последовательного резистора R1, 108 кОм
#define SERIAL_R2 108300     // сопротивление последовательного резистора R2, 102 кОм
#define SERIAL_R3 100200     // сопротивление последовательного резистора R3, 102 кОм
#define SERIAL_R4 102400     // сопротивление последовательного резистора R4, 102 кОм
#define NOMINAL_T 25         // номинальная температура (при которой TR = 100 кОм)
#define THERMISTOR_R 100000  // номинальное сопротивления термистора, 100 кОм
#define B 3950               // B-коэффициент                //      ---------
#define TempSensorPin_01 A0  //Сенсор снануры камеры         //      |       |$1 <- внешний
#define TempSensorPin_02 A1  //Сенсор верхний                //      |     $2|   <- верхний
#define TempSensorPin_03 A2  //Сенсор средний                //      |     $3|   <- средний
#define TempSensorPin_04 A3  //Сенсор нижний                 //      |     $4|   <- нижний \
                                                             //      ---------
//Объявление DHT22
#define DHT_22Pin 2
#define DHT_22 DHT22

//Объявление DHT11
#define DHT_11Pin 3
#define DHT_11 DHT11

//Подключение кулера
#define FanPin_01 5

//Пины виртуальной кнопик
#define ButtonPin_INPUT 8
#define ButtonPin_OUTPUT 10

//Символ градуса
byte grad[8] = {
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

float h_22, f_22, t_22, hif_22, hic_22;
float h_11, f_11, t_11, hif_11, hic_11;
int t1, t2, t3, t4;
float tr1, tr2, tr3, tr4;
float steinhart1, steinhart2, steinhart3, steinhart4;

//Инициализация
DHT dht_22(DHT_22Pin, DHT_22);  //DHT22 |HI| - для считывания показаний внутри сушильной камеры
DHT dht_11(DHT_11Pin, DHT_11);  //DHT11 |HO| - для считывания показаний снаружи сушильной камеры
LiquidCrystal_I2C lcd(0x27, 20, 4);

void DHT22_Read() {
  h_22 = dht_22.readHumidity();     //Считывание влажности
  t_22 = dht_22.readTemperature();  //Считывание температуры в градусах Цельсия
  f_22 = dht_22.readTemperature(true);
  hif_22 = dht_22.computeHeatIndex(f_22, h_22);
  hic_22 = dht_22.computeHeatIndex(t_22, h_22, false);
}

void DHT11_Read() {
  h_11 = dht_11.readHumidity();     //Считывание влажности
  t_11 = dht_11.readTemperature();  //Считывание температуры в градусах Цельсия
  f_11 = dht_11.readTemperature(true);
  hif_11 = dht_11.computeHeatIndex(f_11, h_11);
  hic_11 = dht_11.computeHeatIndex(t_11, h_11, false);
}

void NTC3950_01_Read() {
  t1 = analogRead(TempSensorPin_01);
  tr1 = 1023.0 / t1 - 1;
  tr1 = SERIAL_R1 / tr1;
  steinhart1 = tr1 / THERMISTOR_R;           // (R/Ro)
  steinhart1 = log(steinhart1);              // ln(R/Ro)
  steinhart1 /= B;                           // 1/B * ln(R/Ro)
  steinhart1 += 1.0 / (NOMINAL_T + 273.15);  // + (1/To)
  steinhart1 = 1.0 / steinhart1;             // Invert
  steinhart1 -= 273.15;
}

void NTC3950_02_Read() {
  t2 = analogRead(TempSensorPin_02);
  tr2 = 1023.0 / t2 - 1;
  tr2 = SERIAL_R2 / tr2;
  steinhart2 = tr2 / THERMISTOR_R;           // (R/Ro)
  steinhart2 = log(steinhart2);              // ln(R/Ro)
  steinhart2 /= B;                           // 1/B * ln(R/Ro)
  steinhart2 += 1.0 / (NOMINAL_T + 273.15);  // + (1/To)
  steinhart2 = 1.0 / steinhart2;             // Invert
  steinhart2 -= 273.15;
}

void NTC3950_03_Read() {
  t3 = analogRead(TempSensorPin_03);
  tr3 = 1023.0 / t3 - 1;
  tr3 = SERIAL_R2 / tr3;
  steinhart3 = tr3 / THERMISTOR_R;           // (R/Ro)
  steinhart3 = log(steinhart2);              // ln(R/Ro)
  steinhart3 /= B;                           // 1/B * ln(R/Ro)
  steinhart3 += 1.0 / (NOMINAL_T + 273.15);  // + (1/To)
  steinhart3 = 1.0 / steinhart3;             // Invert
  steinhart3 -= 273.15;
}

void NTC3950_04_Read() {
  t4 = analogRead(TempSensorPin_04);
  tr4 = 1023.0 / t4 - 1;
  tr4 = SERIAL_R2 / tr4;
  steinhart4 = tr4 / THERMISTOR_R;           // (R/Ro)
  steinhart4 = log(steinhart4);              // ln(R/Ro)
  steinhart4 /= B;                           // 1/B * ln(R/Ro)
  steinhart4 += 1.0 / (NOMINAL_T + 273.15);  // + (1/To)
  steinhart4 = 1.0 / steinhart4;             // Invert
  steinhart4 -= 273.15;
}

void fan_on_off() {
  if (digitalRead(ButtonPin_INPUT) == HIGH) {
    analogWrite(FanPin_01, HIGH);
  } else {
    analogWrite(FanPin_01, LOW);
  }
}

//Подключение кнопки
void Virtual_Button() {
  pinMode(ButtonPin_OUTPUT, OUTPUT);
  pinMode(ButtonPin_INPUT, INPUT);
  digitalWrite(ButtonPin_OUTPUT, HIGH);
}

void displey_info() {
  //DHT11 |HO|
  lcd.setCursor(0, 0);
  lcd.print("HI:    ");
  lcd.setCursor(0, 1);
  lcd.print("TI:    ");

  //DHT22 |HI|
  lcd.setCursor(8, 0);
  lcd.print("HO:     ");
  lcd.setCursor(8, 1);
  lcd.print("TO:    ");

  //Нужная температура
  lcd.setCursor(16, 0);
  lcd.print("T:    ");

  //Нынешняя температура
  lcd.setCursor(8, 1);
  lcd.print("T:   ");
  //Скорость кулера
  lcd.setCursor(8, 2);
  lcd.print("F:   ");
  //Время работы

  //NTC3950_01
  lcd.setCursor(0, 2);
  lcd.print("T1:     ");
  //NTC3950_02
  lcd.setCursor(11, 2);
  lcd.print("T2:     ");
  //NTC3950_03
  lcd.setCursor(0, 3);
  lcd.print("T3:     ");
  //NTC3950_04
  lcd.setCursor(11, 3);
  lcd.print("T4:     ");
}

void setup() {
  //Настройка режима пинов
  pinMode(FanPin_01, OUTPUT);

  lcd.init();               //Включение дисплея
  lcd.createChar(0, grad);  //Создание спец символа "градус"
  lcd.clear();              //Очистка дисплея при включении
  lcd.backlight();
  dht_22.begin();
  dht_11.begin();
  delay(2000);  //Задержка для загрузки всех система

  //Вывод информации на LCD дисплей
  displey_info();
  Virtual_Button();
}

void loop() {
  //Запуск функций считывания показаний с сенсоров
  DHT22_Read();
  DHT11_Read();
  NTC3950_01_Read();
  NTC3950_02_Read();
  NTC3950_03_Read();
  NTC3950_04_Read();
  fan_on_off();

  //Вывод информации на LCD дисплей
  //Показания сенсора DHT22
  lcd.setCursor(3, 0);
  lcd.print(h_22);
  lcd.setCursor(3, 1);
  lcd.print(t_22);
  //Показания сенсора DHT11
  lcd.setCursor(14, 0);
  lcd.print(h_11);
  lcd.setCursor(14, 1);
  lcd.print(t_11);
  //Показания сенсоров NTC3950
  lcd.setCursor(3, 2);
  lcd.print(steinhart1);
  lcd.setCursor(14, 2);
  lcd.print(steinhart2);
  lcd.setCursor(3, 3);
  lcd.print(steinhart3);
  lcd.setCursor(14, 3);
  lcd.print(steinhart4);

  delay(1000);
}
