//Подключение библиотеки для дисплея
#include <LiquidCrystal.h>


//Инициализация подключеных входов в дисплей
LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

//Аналоговые входа - инициализация(Мониторинг температуры)
float Temperature_1;
int Temperature_2;
int Temperature_3;
int Temperature_4;
int Temperature_5;

//Дискретные сигналы - инициализация(Управляющие кнопки)
byte Read_btn_up = 8;
byte Read_btn_down = 7;
byte btn_up;
byte btn_down;

//Счетчик
int count = 1;

//Переменные для реализация нажатия без дребезга
bool flag_1 = false;
unsigned long last_press;

//Переменная для расчёта значения 75%
float member = 0.0; 


void setup()  
{
  Serial.begin(9600);  
  
  //Настройка дисплея - число столбцов и строк
  LCD.begin(16, 2);
  //Инициализация кнопок как входов
  pinMode(btn_up, INPUT);
  pinMode(btn_down, INPUT);
  
  
}

void loop()
{  
  //Чтение с аналоговых входов
  Temperature_1 = analogRead(A0);
  Temperature_2 = analogRead(A1);
  Temperature_3 = analogRead(A2);
  Temperature_4 = analogRead(A3);
  Temperature_5 = analogRead(A4);
  
  //Чтение дискретных сигналов
  btn_up = digitalRead(Read_btn_up);  
  btn_down = digitalRead(Read_btn_down);  
  
  //Вызов функии для кнопок
  Function_btn(btn_up);
  Function_btn(btn_down); 
  
  //Счетчик для переключения отображения
  if (flag_1 == HIGH && btn_up)
  {    
    count++;
  }
  else if (flag_1 == HIGH && btn_down)
  {    
    count--;
  }
  
  //сброс счетчика 
  if (count > 8)
  {    
    count = 1;
  }
  else if(count < 0)
  {
    count = 8;
  }
    
  
  //Вызов функции для температуры
  
  int tmp_1 = Function_temperature(Temperature_1);
  int tmp_2 = Function_temperature(Temperature_2);
  int tmp_3 = Function_temperature(Temperature_3);
  int tmp_4 = Function_temperature(Temperature_4);
  int tmp_5 = Function_temperature(Temperature_5);
  
      
//Вывод определного окна с результатом
  switch (count) 
  {
    case 1:     
      LCD.clear();      
  	  LCD.setCursor(0,0);
  	  LCD.print("TEMP 1= ");
  	  LCD.print(tmp_1);      
  	  LCD.print("C");
      delay(250);
      break;      
    case 2:
      LCD.clear();      
  	  LCD.setCursor(0,0);
  	  LCD.print("TEMP 2= ");
  	  LCD.print(tmp_2);      
  	  LCD.print("C"); 
  	  delay(250);
      break;    
    case 3:   
      LCD.clear();      
  	  LCD.setCursor(0,0);
  	  LCD.print("TEMP 3= ");
  	  LCD.print(tmp_3);
  	  LCD.print("C");
      delay(250);
      break;     
    case 4:
      LCD.clear();      
  	  LCD.setCursor(0,0);
  	  LCD.print("TEMP 4= ");
  	  LCD.print(tmp_4);
  	  LCD.print("C");
      delay(250);
      break;     
    case 5:
      LCD.clear();      
  	  LCD.setCursor(0,0);
  	  LCD.print("TEMP 5= ");
  	  LCD.print(tmp_5);
  	  LCD.print("C");  
      delay(250);
      break;     
    case 6:    
      LCD.clear();
      member = (Temperature_1/4)*3;      
  	  LCD.setCursor(0,0);
  	  LCD.print("FUNC= ");
  	  LCD.print(member);
      delay(250);
      break;     
    case 7:    
      LCD.clear();      
  	  LCD.setCursor(0,0);
  	  LCD.print("ALL");    	  
      LCD.setCursor(4,0);
      LCD.print(tmp_1);
      LCD.print("C");
      LCD.setCursor(10,0);
      LCD.print(tmp_2);
      LCD.print("C");
      LCD.setCursor(0,1);
      LCD.print(tmp_3);
      LCD.print("C");
      LCD.setCursor(6,1);
      LCD.print(tmp_4);
      LCD.print("C");
      LCD.setCursor(12,1);
      LCD.print(tmp_5);
      LCD.print("C");
      delay(300);
      break;  
     
  }      
}
//Защита от дребезга контактов кнопки
void Function_btn(bool btn)
{    
  if (btn == 1 && flag_1 == 0 && millis() - last_press > 100)
  {
    flag_1 = 1; 
    last_press = millis();    
  }
    
  if (btn == 0 && flag_1 == 1 && millis() - last_press > 100)
  {
    flag_1 = 0;    
  }
}
//Расчет температур от аналоговых сигналов с датчика ТМР
float Function_temperature(float tmp)
{     
  float temp=0.0; 
  float voltage = 0.0;    
  voltage = (tmp * 0.004882814);
  return temp = (voltage - 0.508) * 100.0; 
  delay(50);
}










