//#define lighBulb_pin 3
//#define button1_pin 7
//#define button2_pin 12
//#define motor_pin 5
//
//int current_bulb=0;
//int current_motor=0;
//int button1_state = 0;
//int button2_state = 0;
//void setup(){
//  Serial.begin(9600);
//  pinMode(lighBulb_pin,OUTPUT);
//    pinMode(motor_pin,OUTPUT);
//  pinMode(button1_pin,OUTPUT);
//  pinMode(button2_pin,OUTPUT);
//}
//void loop(){
//  button1_state = digitalRead(button1_pin);
//   button2_state = digitalRead(button2_pin);
//  
//   if (button1_state == HIGH&& current_bulb<256) {
//  current_bulb=current_bulb+10;  
//    
//   delay(500);
// analogWrite(lighBulb_pin,current_bulb);
//   }
//  
//    if (button2_state == HIGH&& current_motor<256) {
//  current_motor=current_motor+10;  
//   delay(500);
// analogWrite(motor_pin,current_motor);
//   }
//  
//  
//}

#include <LiquidCrystal.h> 
#include "DHT.h"
#define dht_apin A0
DHT dht(A0,DHT11);
const int rs=12 , en=11, d4=5 , d5=4, d6=3, d7=2;
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);
// initialization

int fan =A1 ,buzzer=10;
int bulb=9;
float temp,min_temp=36.5,max_temp=37.5,t=0.5,humidity;
int temppin=0;
int inc1=8,dec1=13,inc2=6,dec2=7;

void setup()
{
 Serial.begin (9600); 
 dht.begin();
 pinMode(buzzer,OUTPUT);
 pinMode (fan, OUTPUT);
 pinMode(bulb,OUTPUT);
 pinMode(inc1, INPUT_PULLUP);
 pinMode(dec1, INPUT_PULLUP);
 pinMode(inc2, INPUT_PULLUP);
 pinMode(dec2, INPUT_PULLUP);
lcd.begin (16, 2); // Activating both Rows of LCD
delay (2000); 
lcd.clear();
lcd.print ("INCUBATOR");
lcd.print ("Temperature = ");
}
void loop ()
{ 
float humidity = dht.readHumidity();
float temp = dht.readTemperature();
byte inc1State = digitalRead(inc1);
byte dec1State = digitalRead(dec1);
byte inc2State = digitalRead(inc2);
byte dec2State = digitalRead(dec2);
Serial.println(inc1State);
delay(100);
Serial.println(dec1State);
delay(100);
Serial.println(inc2State);
delay(100);
Serial.println(dec2State);

if(inc1State==LOW){
  min_temp=min_temp+t;
}
//if(dec1State==HIGH){
// 
//}
//else{
//  min_temp=,im_temp-t;
//}
//
//if(inc2State==HIGH){
//  
//}
//else{
//  max_temp+=t;
//}
//
//if(dec2State==HIGH){
//  
//}
//else{
//  max_temp-=t;
//}
//if(inc1State==LOW){
//  min_temp+=t;
//}
//if(dec1State==LOW)
//{
//  min_temp-=t;
//}
//if(inc2State==LOW)
//{
//  max_temp+=t;
//}
//if(dec2State==LOW)
//{
//  max_temp-=t;
//} 
Serial.println (temp); // Printing in Serial Monitor
Serial.println (" C");
lcd.print ("Temperature = ");
lcd.setCursor (0, 1); // Selecting the LCD Cursor to 1st Line
lcd.print (temp);
lcd.print (" C");
delay (1000); 
lcd.clear();
lcd.print ("Temperature Range= ");
lcd.setCursor (0, 1); 
lcd.print (min_temp);
lcd.print (" : ");
lcd.print(max_temp);
delay (1000); 
lcd.clear();
lcd.print ("humidity = ");
lcd.setCursor (0, 1); // Selecting the LCD Cursor to 1st Line
lcd.print (humidity);
delay (1000); 
lcd.clear();
if (temp<min_temp) 
{
  digitalWrite (fan, LOW);
  digitalWrite (bulb, HIGH);
  tone(buzzer,1000);
  delay(1000);
  noTone(buzzer);
  delay(1000);
}
else if(temp>max_temp)
{
  digitalWrite (fan, HIGH);
  digitalWrite (bulb, LOW);
   tone(buzzer,1000);
   delay(1000);
  noTone(buzzer);
  delay(1000);
}
else 
{
digitalWrite (fan, LOW);
digitalWrite (bulb, LOW);
}

}
