void Timer_debbug() {
  if (millis() - last_time > 500) {
    last_time = millis();
    Serial.println("sec: " + String(second));
    second++;
  }
}

void Button_debbug() {
  if (millis() - Last_Debbug_Message > Timer_Debbug_Message) {
    Last_Debbug_Message = millis();
    Serial.print("Fan_01: " + String(FAN_Speed) + " But_St: " + String(YELLOW_Button_State));  //Проверка работоспособности желтой кнопки
    Serial.print("\t");
    Serial.print("Temp: " + String(BED_Temperature) + " But_St: " + String(RED_Button_State));  //Проверка работоспособности красной кнопки
    Serial.print("\t");
    Serial.print("Temp_11: " + String(t_11) + "   Hum_11: " + String(h_11));  //Вывод информации с DHT11
    Serial.print("\t");
    Serial.print("Temp_22: " + String(t_22) + "   Hum_22: " + String(h_22));  //Вывод информации с DHT22
    Serial.println();
  }
}

void NTC_debbug() {
  if (millis() - Last_Debbug_Message > Timer_Debbug_Message) {
    Last_Debbug_Message = millis();
    Serial.print("RAW: " + String(NTC_Read(sensorTemp_pin[0], NTC3950_RESISTANS[0])));
    Serial.println();
  }
}

void NTC_Plotter() {
  if (millis() - Last_Debbug_Message > Timer_Debbug_Message) {
    Last_Debbug_Message = millis();
    Serial.print(NTC_Read(sensorTemp_pin[0], NTC3950_RESISTANS[0])); //Вывод сырых показаний термистора
    Serial.print("\t");
    Serial.print(NTC_Result[0]);
    Serial.println();
  }
}