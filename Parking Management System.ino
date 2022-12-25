#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // Name and address of LiquidCrystal_I2C
Servo servo;                    //Name given to Servo motor
int pos = 0;                    //Position variable for position of Servo
int s1, s2;                     //IR SENSOR 1 and IR SENSOR 2
int ps1, ps2, ps3, ps4;         //IR Sensors at the parking slots 1,2,3 and 4 respectively.
int Vacancy, Occupancy;         //Variable names for calculating the number of vacant and occupied slots

void setup() 
{
 lcd.init();          //To initialize the LCD
 lcd.backlight();     //To turn ON the back light of LCD
 servo.attach(9);     //Output pin of servo is connected
 pinMode(A0,OUTPUT);  //Buzzer is Connected
 pinMode(3,INPUT);    //s1 for sensor outside the gate
 pinMode(4,INPUT);    //s2 for sensor inside the gate
 pinMode(8,INPUT);    //ps1 for sensor in parking slot no 1
 pinMode(7,INPUT);    //ps2 for sensor in parking slot no 2
 pinMode(6,INPUT);    //ps3 for sensor in parking slot no 3
 pinMode(5,INPUT);    //ps4 for sensor in parking slot no 4
 pinMode(13,OUTPUT);  //LED for ps1
 pinMode(12,OUTPUT);  //LED for ps2
 pinMode(11,OUTPUT);  //LED for ps3
 pinMode(10,OUTPUT);  //LED for ps4
 lcd.setCursor(1,0);  
 lcd.print("PARKING MANAGEMENT");
 lcd.setCursor(7,2);
 lcd.print("SYSTEM");
 delay(1000);
 lcd.clear();         //Clear the entire LCD screen
} 
void loop()
{
  s1 = digitalRead(3);
  s2 = digitalRead(4);
  ps1 = digitalRead(8);
  ps2 = digitalRead(7);
  ps3 = digitalRead(6);
  ps4 = digitalRead(5);

  Vacancy = ps1 + ps2 + ps3 + ps4;          //Formula for Calculating Number of Vacant Slots
  Occupancy = 4 - Vacancy;                 //It gives Number of Slots which are Occupied
  
  lcd.setCursor (1,0);
  lcd.print("   Vacancy = "); 
  lcd.print(Vacancy);
  lcd.setCursor(4,3);
  lcd.print("Occupancy = ");
  lcd.setCursor(15,3);
  lcd.print(Occupancy);
  
  if((Vacancy == 0) and (Occupancy == 4))
  {
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("!!!SORRY!!! ");
    lcd.setCursor(6,1);
    lcd.print("NO ENTRY ");
    lcd.setCursor(1,3);
    lcd.print("All Slots Are Full ");
    delay(1000);
    lcd.clear();
  }
  else
  {
    lcd.setCursor (0,1);
    (ps1==0 ? lcd.print("PS1:FULL ") : lcd.print("PS1:EMPTY"));
    
    lcd.setCursor (11,1);
    (ps2==0 ? lcd.print("PS2:FULL ") : lcd.print("PS2:EMPTY"));
    
    lcd.setCursor (0,2);
    (ps3==0 ? lcd.print("PS3:FULL ") : lcd.print("PS3:EMPTY"));
    
    lcd.setCursor (11,2); 
    (ps4==0 ? lcd.print("PS4:FULL ") : lcd.print("PS4:EMPTY"));
  }
  if((s1==0 or s2==0) and (ps1==1 or ps2==1 or ps3==1 or ps4==1)) //For opening gate from both sides
  {                                              
    for(pos=0; pos<=90; pos+=90)
    {
      servo.write(pos);
      digitalWrite(A0,HIGH);                     //For turning the BUZZER ON
      delay(100);
      digitalWrite(A0,LOW);                      //For turning the BUZZER OFF
      delay(500);
      break;
    }
  }
  if(s1==1 and s2==1)
  {                                              //For closing gate from both sides
    for(pos=90; pos>=0; pos-=90)
    {
      servo.write(pos);
      break;
    }
  }
  (ps1==0 ? digitalWrite(13,LOW) : digitalWrite(13,HIGH));    //For Turning ON and OFF LED at ps1
  (ps2==0 ? digitalWrite(12,LOW) : digitalWrite(12,HIGH));    //For Turning ON and OFF LED at ps2
  (ps3==0 ? digitalWrite(11,LOW) : digitalWrite(11,HIGH));    //For Turning ON and OFF LED at ps3
  (ps4==0 ? digitalWrite(10,LOW) : digitalWrite(10,HIGH));    //For Turning ON and OFF LED at ps4
 }
