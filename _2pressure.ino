#include <Keypad.h>
#include <LiquidCrystal.h>
#define threshold 100 // threshold value to decide weather the detected value will be displayed or not.
int flag =0;
int piezoPin1 = A0;// the positive pin of piezo element 1 is connected to analog pin 0
int piezoPin2 = A1;// the positive pin of piezo element 2 is connected to analog pin 1
int sensorReading1 = 0; // variable to store the value read from the sensor pin
int sensorReading2 = 0; // variable to store the value read from the sensor pin
const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 16, 17, 18, 19 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 8, 9, 10 }; 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup() 
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Distance=");
} 

void loop()
{
 float time1,time2,t,time3;
  int a=0;
    int val;
    char key = kpd.getKey();
    while(1)
    {
      char key = kpd.getKey();
      if(key=='*')
      {
         flag=1 ;
         break;      
      }
      if(key)  // Check for a valid key.
      {
        if(key=='1')
          val=1;
        if(key=='2')
          val=2;
        if(key=='3')
          val=3;
        if(key=='4')
          val=4;
        if(key=='5')
          val=5;
        if(key=='6')
          val=6;
        if(key=='7')
          val=7;
        if(key=='8')
          val=8;
        if(key=='9')
          val=9;
        if(key=='0')
          val=0;
        a=a*10+val;
        lcd.print(key);
      }
    }
    float s;
    while(1)
    {
     sensorReading1 = analogRead(piezoPin1);
     // If the sensor reading is greater than the threshold
     if (sensorReading1 >= threshold) 
    {
        digitalWrite(13,1);
        t=0;
        while(1)
        {
          t++;
          sensorReading2=analogRead(piezoPin2);
          if(sensorReading2>threshold)
          break;
          delay(1);
        }
        digitalWrite(13,0); 
        t=t/1000;
        s=a/t;
        lcd.setCursor(0, 1);
        lcd.print("Speed=");
        lcd.print(s);
        lcd.print(" m/s");
        Serial.print(t);    
        while(1);
    }
  }  
}



 

