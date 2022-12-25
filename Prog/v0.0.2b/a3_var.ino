//Переменные кнопок
bool YELLOW_Button_flag, YELLOW_Button_State, RED_Button_State, RED_Button_flag, BLUE_Button_flag, BLUE_Button_State;
uint64_t Last_RED_Button_Press, Last_YELLOW_Button_Press, Last_BLUE_Button_Press;



uint64_t Last_Debbug_Message;
uint64_t last_time, LCD_lastTime, Tepmerature_Timer;

uint8_t second = 0;

float a = 20.32343;

//Переменные кулеров
uint8_t FAN_Speed;

//Переменные PID регулятора
uint8_t BED_Temperature;

//Переменный датчика DHT
float h_22, t_22;
float h_11, t_11;

float NTC_Result[4] = {};
float NTC3950_RAW_result[5] = {};
float TempComputer[5] = {};
float NTC3950_RESISTANS[5] = { NTC3950_RESISTANS_01, NTC3950_RESISTANS_02, NTC3950_RESISTANS_03, NTC3950_RESISTANS_04, NTC3950_RESISTANS_05 };
int sensorTemp_pin[5] = { TempSensorPin_01, TempSensorPin_02, TempSensorPin_03, TempSensorPin_04, TempSensorPin_04 };