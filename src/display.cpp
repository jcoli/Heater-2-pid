/**
Version: 0a
Tecnocoli - 06/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F411CE6 - HotPlate Soldier
**/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "io_defines.h"
#include "analog_input.h"
#include "pid.h"

void display_begin();
void show_display();

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

extern float celsius;
extern int pwm1;
extern int pwm2;
extern int spValue;
extern int program_cycle;

void display_begin(){

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    display.setRotation(2);
    display.clearDisplay();
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    Serial.println("start display");
    display.println("Hello, Tecnocoli!");
   
    delay(1000);

}


void show_display(){
      display.clearDisplay();
      // display.display(); 

    //   display.display(); 
      // Serial.println("show display");
      // display.setTextSize(1);
      display.setTextColor(WHITE);
      // display.setCursor(0, 0);
      display.setCursor(0, 10);
      display.setTextSize(3);
      display.print(program_cycle);
      display.setCursor(60, 10);
      display.setTextSize(3);
      display.print(celsius, 0);
      display.setTextSize(2);
      display.setCursor(0, 40);
      display.print(spValue);   
      display.setCursor(80, 40);
      display.print(pwm1);
      // display.setTextSize(2);
      display.display(); 

}
