#include<NewPing.h>
#include<AFMotor.h>
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
int t=0;
void forward(){
  motor1.setSpeed(85);
  motor2.setSpeed(120); 
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  
}

void left1(){
  delay(120);
  motor1.setSpeed(80);
  motor2.setSpeed(110);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(120);
  motor1.setSpeed(85);
  motor2.setSpeed(120); 
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  
}
void nor_left(){
  //delay(120);
  motor1.run(RELEASE);
  motor2.run(FORWARD);
}
void nor_right(){
  //delay(120);
  motor1.run(FORWARD);
  motor2.run(RELEASE);
}
void right1(){
  delay(120);
  motor1.setSpeed(80);
  motor2.setSpeed(110);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(120);
  motor1.setSpeed(85);
  motor2.setSpeed(120); 
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}
void brake(){
  motor1.setSpeed(0);
  motor2.setSpeed(0);
}
void backward(){
  delay(120);
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

  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  
  delay(1500);
  motor1.setSpeed(85);
  motor2.setSpeed(120);
  
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
  lcd.setCursor(3,1);
  lcd.print("BASANT-E");
left = dist1();
mid = dist2();
right = dist3();
Serial.println(" ");
int bc=40,cd=40,md=10;

motor1.setSpeed(85);
motor2.setSpeed(120);
//motor1.run(FORWARD);
//motor2.run(FORWARD);
//
//motor1.run(BACKWARD);
//motor2.run(BACKWARD);

if(mid<15&&right<15)        
{ left1();
  t=6;}
else if(mid<15&&left<15)         
{ right1();
  t=3;}
      else if (left<15){
      forward();
      t=1;
      }
      else if(right<15){
      forward();
      t=4;
      }
     else{
      brake();
      //while((left>15||left<0) && (right>15||right<0)){
      if(t==1){
      left1();
      delay(80);
      //forward();
      t=0;
      }
      else if(t==4){
      right1();
      delay(80);
      //forward();
      t=0;
      }
      else if(t==3){
        right1();
        delay(80);
       t=0;
      }
      else if(t==6){
        left1();
        delay(80);
        t=0;
        }

}
}
