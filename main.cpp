#include <Arduino.h>
#include<TFT_eSPI.h>
#include<SPI.h>

//set pins
int LEDPIN_RED=26;
int LEDPIN_YELLOW=32;
int LEDPIN_GREEN=17;
int PUSH_BUTTON=37;
int BELL=15;

const unsigned long  ten_sec =10000;
const unsigned long  five_sec=5000;
const unsigned long  two_sec =2000;

TFT_eSPI tft= TFT_eSPI();


void setup() 
{
  Serial.begin(11520);
  //initialize i/o  
  pinMode(LEDPIN_GREEN,OUTPUT);  
  pinMode(LEDPIN_YELLOW,OUTPUT);
  pinMode(LEDPIN_RED,OUTPUT);
  pinMode(PUSH_BUTTON,INPUT);

  //Make this work
  tft.init();
  tft.fillScreen(TFT_BLACK);  //erase all OLED
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawCircle(66,120,30,TFT_YELLOW);
  tft.drawCircle(66,30,30,TFT_RED);
  tft.drawCircle(66,209,30,TFT_GREEN);
  
  
}


void soundgreen()
{
  tone(BELL,800);
  delay(500);
  noTone(BELL);
  delay(1500);
}

void soundred()
{
  tone(BELL,800);
  delay(250);
  noTone(BELL);
  delay(250);
}

void red()
{
  unsigned long start_time=millis();  //flag the current millis()
  unsigned long mytime=0;
  tft.fillCircle(66,30,30,TFT_RED);
  while(mytime<ten_sec)
  {
    mytime=millis()-start_time;
    digitalWrite(LEDPIN_RED,HIGH);
    
    soundred();
  }
  digitalWrite(LEDPIN_RED,LOW);
  tft.fillCircle(66,30,30,TFT_BLACK);
  tft.drawCircle(66,30,30,TFT_RED);
}

void yellow()
{
  unsigned long  start_time=millis();  //flag the millis()
  unsigned long  mytime=0;
  tft.fillCircle(66,120,30,TFT_YELLOW);
  while(mytime<=two_sec)
  {
    mytime=millis()-start_time;
    digitalWrite(LEDPIN_YELLOW,HIGH);
     
  
  }
  digitalWrite(LEDPIN_YELLOW,LOW);
  tft.fillCircle(66,120,30,TFT_BLACK);
  tft.drawCircle(66,120,30,TFT_YELLOW);
}


void  green5()
{
  unsigned long  start_time=millis();  //flag the millis()
  unsigned long  mytime=0;
  tft.fillCircle(66,209,30,TFT_GREEN);
  while(mytime<=five_sec)// ten sec green light
  {
    mytime=millis()-start_time;
    digitalWrite(LEDPIN_GREEN,HIGH);
  }
  digitalWrite(LEDPIN_GREEN,LOW);
  tft.fillCircle(66,209,30,TFT_BLACK);// erase
  tft.drawCircle(66,209,30,TFT_GREEN);
}


void green10()
{
  unsigned long  start_time=millis();  //flag the millis()
  unsigned long  mytime=0;
  tft.fillCircle(66,209,30,TFT_GREEN);
  while(mytime<ten_sec)// ten sec green light
  {
    mytime=millis()-start_time;
    digitalWrite(LEDPIN_GREEN,HIGH);  
    soundgreen(); //call sound
  }
  digitalWrite(LEDPIN_GREEN,LOW);
  tft.fillCircle(66,209,30,TFT_BLACK); //erase green light
  tft.drawCircle(66,209,30,TFT_GREEN);
  
}

void loop() 
{
  if(digitalRead(PUSH_BUTTON)==HIGH)  // read button if pushed
  {
    delay(15); // debuff
    if(digitalRead(PUSH_BUTTON)==HIGH)
    {
      Serial.println("Wait 7 seconds to cross");
      green5();  //stays green for 5 sec
      yellow(); // stays yellow for 2 sec


      //pedestrian  could cross while cars are stopped
      red();  // has 10 sec to cross
      yellow(); // 2 second warning
    }
  }
  
  green10();
}
