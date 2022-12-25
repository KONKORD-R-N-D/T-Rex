//Функция красной кнопки - установка значения температуры с шагом 20 и 5
void RED_Button() {
  RED_Button_State = !digitalRead(RED_Button_pin);
  if (RED_Button_State == 1 && RED_Button_flag == 0 && millis() - Last_RED_Button_Press > TimerButton) {
    Last_RED_Button_Press = millis();
    RED_Button_flag = 1;
    if (BED_Temperature < 80) {
      BED_Temperature += 20;
    } else if (BED_Temperature >= 80 && BED_Temperature < 110) {
      BED_Temperature += 5;
    } else if (BED_Temperature >= 110) {
      BED_Temperature = 0;
    }
    //Serial.println("press");
  }
  if (RED_Button_State == 0 && RED_Button_flag == 1) {
    RED_Button_flag = 0;
    //Serial.println("realesed");
  }
}

void BLUE_Button() {
  BLUE_Button_State = !digitalRead(BLUE_Button_pin);
  if (BLUE_Button_State == 1 && BLUE_Button_flag == 0 && millis() - Last_BLUE_Button_Press > TimerButton) {
    Last_BLUE_Button_Press = millis();
    BLUE_Button_flag = 1;
    digitalWrite(2, LOW);

    //lcd.noDisplay();
    //Serial.println("press");
  }
  if (BLUE_Button_State == 0 && BLUE_Button_flag == 1) {
    BLUE_Button_flag = 0;
    //Serial.println("realesed");
  }
}

//Функция желтой кнопки - включение/выключение кулеров
//Два режима работы:
//      1. 50% мощности (125)
//      2. 95% мощности (250)
void YELLOW_Button() {
  YELLOW_Button_State = !digitalRead(YELLOW_Button_pin);
  if (YELLOW_Button_State == 1 && YELLOW_Button_flag == 0 && millis() - Last_YELLOW_Button_Press > TimerButton) {
    Last_YELLOW_Button_Press = millis();
    YELLOW_Button_flag = 1;
    FAN_ON_OFF();
    //Serial.println("press");
  }
  if (YELLOW_Button_State == 0 && YELLOW_Button_flag == 1) {
    YELLOW_Button_flag = 0;
    //FAN_OFF();
    //Serial.println("realesed");
  }
}

void FAN_ON_OFF() {
  if (FAN_Speed < 250) {
    FAN_Speed += 125;
  } else if (FAN_Speed >= 250) {
    FAN_Speed = 0;
  }
  analogWrite(FAN_01_pin, FAN_Speed);
  analogWrite(FAN_02_pin, FAN_Speed);
}

void DHT22_Read() {
  h_22 = dht_22.readHumidity();     //Считывание влажности
  t_22 = dht_22.readTemperature();  //Считывание температуры в градусах Цельсия
}

void DHT11_Read() {
  h_11 = dht_11.readHumidity();     //Считывание влажности
  t_11 = dht_11.readTemperature();  //Считывание температуры в градусах Цельсия
}

float NTC_Read(float sensorTemp_pin, float NTC3950_RESISTANS) {
  float RAW_Temp, Read_Temp;
  Read_Temp = NTC3950_RESISTANS / (1023.0 / analogRead(sensorTemp_pin) - 1.0);
  RAW_Temp = log(Read_Temp / THERMISTOR_R) / B;
  RAW_Temp += 1.0 / (NOMINAL_T + 273.15);
  RAW_Temp = 1.0 / RAW_Temp;
  RAW_Temp -= 273.15;
  return RAW_Temp;
}

void Temp_average() {
  float Temp_Data[4] = {};
  for (uint8_t i = 0; i < MEASURE; i++) {
    if (millis() - Tepmerature_Timer > Last_Temperature_Measure) {
      Tepmerature_Timer = millis();
      Temp_Data[0] = NTC_Read(sensorTemp_pin[0], NTC3950_RESISTANS[0]);
    }
    Temp_Data[0] += Temp_Data[0];
  }
  NTC_Result[0] = Temp_Data[0] / 100.0;
}