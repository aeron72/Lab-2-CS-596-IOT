#include <Arduino.h>
#include<TFT_eSPI.h>
#include<SPI.h>
/*
 * Traffic Light & Pedestrian Crossing System
 * ------------------------------------------
 * This program simulates a traffic light with a pedestrian crossing system.
 * It uses an ESP32, a TFT display, LEDs, a buzzer, and a push button.
 *
 * - Green, Yellow, and Red lights operate in a cycle.
 * - When the push button is pressed, the cycle adapts for pedestrian crossing.
 * - A buzzer provides sound feedback during red and green signals.
 * - The TFT display visually represents the traffic lights.
 *
 * Hardware: ESP32, TFT_eSPI Display, LEDs, Buzzer, Push Button.
 */


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
void soundgreen()
{
  tone(BELL,800); // Play buzzer tone at 800 Hz
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

// Activate RED light for pedestrian crossing (10 seconds)
void red()
{
  unsigned long start_time=millis();  //flag the current millis()
  unsigned long mytime=0;
  tft.fillCircle(66,30,30,TFT_RED);
  while(mytime<ten_sec)
  {
    mytime=millis()-start_time;
    digitalWrite(LEDPIN_RED,HIGH);  // Turn on red LED
    
    soundred();  // Play short buzzer sounds
  }
  digitalWrite(LEDPIN_RED,LOW);  // Turn off red LED
  tft.fillCircle(66,30,30,TFT_BLACK);  // Clear the red circle
  tft.drawCircle(66,30,30,TFT_RED);  // Redraw the outline
}

void yellow()
{
  unsigned long  start_time=millis();  //flag the millis()
  unsigned long  mytime=0;
  tft.fillCircle(66,120,30,TFT_YELLOW);
  while(mytime<=two_sec)
  {
    mytime=millis()-start_time;
    digitalWrite(LEDPIN_YELLOW,HIGH); //ON
     
  
  }
  digitalWrite(LEDPIN_YELLOW,LOW); //OFF
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

void setup() 
{
  Serial.begin(11520);
  //initialize i/o  
  pinMode(LEDPIN_GREEN,OUTPUT);  
  pinMode(LEDPIN_YELLOW,OUTPUT);
  pinMode(LEDPIN_RED,OUTPUT);
  pinMode(PUSH_BUTTON,INPUT);

  tft.init();
  tft.fillScreen(TFT_BLACK);  //erase all OLED
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  // Draw the three traffic light circles on the display
  tft.drawCircle(66,120,30,TFT_YELLOW);
  tft.drawCircle(66,30,30,TFT_RED);
  tft.drawCircle(66,209,30,TFT_GREEN);

  red(); //start up goes from red, yellow, green and stays there
  yellow();
  green10();
  
  
}




void loop() 
{
  if(digitalRead(PUSH_BUTTON)==HIGH)  // read button if pushed
  {
    delay(50); // debuff
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
