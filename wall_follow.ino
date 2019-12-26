#include<NewPing.h>
#include<AFMotor.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
#define trigPin1  A8
#define trigPin2  A10
#define trigPin3  A12
#define echoPin1  A9
#define echoPin2  A11
#define echoPin3  A13

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

int duration, distance1 ,distance2 , distance3 , left , right , mid ,countDE=0,countCB=0; 
int l=0,r=0,m=0;
void forward(){
  motor1.setSpeed(71);
  motor2.setSpeed(87); 
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  
}

void left1(){
  delay(100);
  motor1.setSpeed(68);
  motor2.setSpeed(87);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(100);
  motor1.setSpeed(71);
  motor2.setSpeed(87); 
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  
}
void power_left(){
  motor1.setSpeed(71);
  motor2.setSpeed(87);
  motor1.run(RELEASE);
  motor2.run(FORWARD);
  Serial.println("FUCK TECHKRITI");
  delay(80);
}

void power_right(){
  motor1.setSpeed(71);
  motor2.setSpeed(87);
  motor1.run(FORWARD);
  motor2.run(RELEASE);
  Serial.println("FUCK TECHKRITI");
  delay(80);
}
void right1(){
  delay(100);
  motor1.setSpeed(68);
  motor2.setSpeed(87);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(100);
  motor1.setSpeed(71);
  motor2.setSpeed(87); 
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}

void backward(){
  delay(100);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}


int dist1(){
  delay(100);
  digitalWrite(trigPin1,HIGH);
  delay(50);
  digitalWrite(trigPin1,LOW);
  duration=pulseIn(echoPin1,HIGH);
  distance1=(duration/2)/29.1;
  Serial.print("Distance 1 : ");
  Serial.print(distance1);
  Serial.print(" ");
  return distance1;
}

int dist2(){
  delay(100);
  digitalWrite(trigPin2,HIGH);
  delay(50);
  digitalWrite(trigPin2,LOW);
  duration=pulseIn(echoPin2,HIGH);
  distance2=(duration/2)/29.1;
  Serial.print("Distance 2 : ");
  Serial.print(distance2);
  Serial.print(" ");
  return distance2;
}

int dist3(){
  delay(100);
  digitalWrite(trigPin3,HIGH);
  delay(50);
  digitalWrite(trigPin3,LOW);
  duration=pulseIn(echoPin3,HIGH);
  distance3=(duration/2)/29.1;
  Serial.print("Distance 3 : ");
  Serial.print(distance3);
  Serial.print(" ");
  return distance3;
}

void setup()
{
  //delay(1500);
  motor1.setSpeed(73);
  motor2.setSpeed(87);
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight
  lcd.setCursor(1,0);
  lcd.print("RACE BEGINS");
  //delay(500);
  lcd.clear();
  int l=0,r=0,m=0;
  Serial.begin(9600);

pinMode (trigPin1, OUTPUT);
pinMode (echoPin1, INPUT); 
pinMode (trigPin2, OUTPUT);
pinMode (echoPin2, INPUT); 
pinMode (trigPin3, OUTPUT);
pinMode (echoPin3, INPUT); 

}
void loop()
{
  l=0,r=0,m=0;
left = dist1();
mid = dist2();
right = dist3();
Serial.println(" ");
lcd.setCursor(1,0);
lcd.print(left);lcd.print(" ");
//delay(500);
lcd.setCursor(6,0);
lcd.print(mid);lcd.print(" ");
//delay(500);
lcd.setCursor(11,0);
lcd.print(right);lcd.print(" ");delay(2000);
int bc=40,cd=40,md=10;

motor1.setSpeed(71);
motor2.setSpeed(87);
//motor1.run(FORWARD);
//motor2.run(FORWARD);
//
//motor1.run(BACKWARD);
//motor2.run(BACKWARD);

      if(mid<15&&right<15){        
      left1();
      }
      else if(mid<15&&left<15){         
      right1();
      }
      else if (left<15){
      forward();
      l=1;Serial.println("l = ");
      Serial.println(l);
      }
      else if(right<15){
      forward();
      r=1;Serial.println("r = ");
      Serial.println(r);
      }
      else if(left>15&&mid>15&&right>15){
      //backward();
      Serial.print("l = ");
      Serial.println(l);
      Serial.print("r = ");
      Serial.println(r);
      delay(1000);
      if(l==1){
      power_left();
      delay(80);
      // forward();
      l=0;
      }
      else if(r==1){
      power_right();
      delay(80);
      // forward();
      // r=0;
      }
     }
     lcd.clear();
}
