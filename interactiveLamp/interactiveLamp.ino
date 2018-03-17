#include <SoftwareSerial.h>
#include <Servo.h>
Servo servo_test1;
Servo servo_test2;

SoftwareSerial mySerial(6, 5); 
char c;
int pirState = LOW;
int inputPir1 = A1;
int inputPir2 = 11;
int pir_value1 = 0;
int pir_value2 = 0;
int count_study1 = 0;
int count_study2 = 0;
int DCmotor = LOW;
int Disco_led1 = 13;
int Disco_led2 = 8;
int dc_in1 = 2;
int dc_in2 = 4;
int dc_en = 3;
int candle_mode = LOW;
int led_candle = A0;
int night_mode = LOW;
int led_night = A4;
int study_led1 = A2;
int study_led2 = A5;
int final_value1 = 0;
int final_value2 = 0;
int temp = 0;



void setup() {
  pinMode(dc_in1, OUTPUT);
  pinMode(dc_in2, OUTPUT);
  pinMode(dc_en, OUTPUT);
  servo_test1.attach(10);
  servo_test2.attach(9);
  pinMode(inputPir1, INPUT);
  pinMode(inputPir2, INPUT);
  pinMode(led_candle, OUTPUT);
  pinMode(Disco_led1, OUTPUT);
  pinMode(Disco_led2, OUTPUT);
  pinMode(led_night, OUTPUT);
  pinMode(study_led1, OUTPUT);
  pinMode(study_led2, OUTPUT);
  mySerial.begin(9600);
}

void loop() {
 if (mySerial.available()>0 ){
  c = (char)mySerial.read();
  mySerial.println(c);
  if (c == 's' || c == 'n' || c == 'd' || c == 'c')
  {mode_off();}
  mode_on(c);
  }
  
if (pirState == HIGH)
{
  pir_value1 = digitalRead(inputPir1);
 


  if (pir_value1 == HIGH && count_study1 == 0) {
    count_study1 = 1;
    servo1(1, 130);
   // Serial.println("moving");
    digitalWrite(study_led1,HIGH);
  }
  
 pir_value2 = digitalRead(inputPir2);
  if (pir_value2 == HIGH && count_study2 == 0) {
    
    digitalWrite(study_led2,HIGH);
    count_study2 = 1;
    servo2(1, 60);
    }

  if (pir_value1 == LOW && count_study1 == 1){
    for (int t=1; t<=10; t++)
    {delay(1000);
   // pir_value2 = digitalRead(inputPir2);
    pir_value1=digitalRead(inputPir1);
    
    if (pir_value1 == HIGH) break;
    else if (pir_value1 == LOW && t == 10){
      digitalWrite(study_led1,LOW);
      count_study1 = 0;
      servo1(0,130);  
      //digitalWrite(study_led1,LOW);
      //Serial.println("notmoving");
    }
   }
  }

  if (pir_value2 == LOW && count_study2 == 1){
    for (int t=1; t<=10; t++)
    {delay(1000);
    pir_value2=digitalRead(inputPir2);
    if (pir_value2 == HIGH) break;
    else if (pir_value2 == LOW && t == 10){
      //Serial.println("hey");
      digitalWrite(study_led2,LOW);
      count_study2 = 0;
      servo2(0,60);   
    }
   }
  }
}  


if ( DCmotor == HIGH)
{
 digitalWrite(Disco_led1, HIGH);
 delay(500);
 //Serial.println("dcMotorMoving");
// digitalWrite(dc_in1,HIGH);
// digitalWrite(dc_in2,LOW);
// analogWrite(dc_en,250);
// delay(2000);
 //analogWrite(dc_en,0);
 digitalWrite(Disco_led1, LOW);
 digitalWrite(Disco_led2, HIGH);
 delay(500);
// digitalWrite(dc_in1 , LOW);
// digitalWrite(dc_in2 , HIGH);
// analogWrite(dc_en,250);
// delay(2000);
 //analogWrite(dc_en,0);
 digitalWrite(Disco_led2, LOW);
 }

if (candle_mode == HIGH && temp ==1)
{
 servo1(1, 100);
 servo2(1,100);
 //add delay according to time of coming down
 digitalWrite(led_candle, HIGH);
 temp = 0;
  }

if (night_mode == HIGH)
{
  
  digitalWrite(led_night, HIGH);}
}


void servo1(int a, int max_angle1)
{
  if (a == 1)
  {for(int angle = 10; angle < max_angle1; angle += 1)   // command to move from 0 degrees to 180 degrees 
  {                                  
    servo_test1.write(angle);                 //command to rotate the servo to the specified angle
    delay(50);                       
  }
    }
  else
  {
    for(int angle = max_angle1; angle>=10; angle-=4)     // command to move from 180 degrees to 0 degrees 
  {                                
    servo_test1.write(angle);              //command to rotate the servo to the specified angle
    delay(40);                       
  } 
 }
}

void servo2(int b, int max_angle2)
{
  if (b == 1)
  {for(int angle = 190; angle > max_angle2; angle -= 1)   // command to move from 0 degrees to 180 degrees 
  {                                  
    servo_test2.write(angle);                 //command to rotate the servo to the specified angle
    delay(50);                       
  }
  }
  else
  {    for(int angle = max_angle2; angle<=190; angle+=4)     // command to move from 180 degrees to 0 degrees 
  {                                
    servo_test2.write(angle);              //command to rotate the servo to the specified angle
    delay(50);}
}
}

void mode_on(char c)
{
 if (c == 's')
 {pirState = HIGH;}
 else if (c == 'd')
 {DCmotor = HIGH;}
 else if (c == 'c')
 {candle_mode = HIGH;
 temp = 1;}
 else if (c == 'n')
 {night_mode = HIGH;}
 }

 
void mode_off()
{
if (pirState == HIGH)
{ if (count_study1 == 1) {
  servo1(0,130);
  count_study1 = 0;
}
  if (count_study2 == 1) {
    servo2(0, 100);
    count_study2 = 0;}
  pirState = LOW;
 digitalWrite(A2,LOW);
 digitalWrite(A5,LOW);
  }


 else if (DCmotor == HIGH)
 {
  DCmotor = LOW;
  analogWrite(dc_en,0);
  digitalWrite(dc_in1, LOW);
  digitalWrite(dc_in2, LOW);}
  

else if (candle_mode == HIGH)
{ digitalWrite(led_candle, LOW);
  servo1(0,100);
  servo2(0,100);
  candle_mode = LOW;
  temp = 0;}

else if (night_mode == HIGH)
{ digitalWrite(led_night, LOW);
  night_mode = LOW;}
}

