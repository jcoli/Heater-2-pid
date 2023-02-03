/**
Version: 0a
Tecnocoli - 06/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F411CE6 - HotPlate Soldier
**/
#include <Arduino.h>
#include <Bounce2.h>
#include <RotaryEncoder.h>

#include "defines.h"
#include "io_defines.h"
#include "pid.h"
#include "display.h"


void buttons_begin();
void checkPosition();
void check_button();
void dec_ana();
void inc_ana();
void choice_item_select(int chg);


RotaryEncoder *encoder = nullptr;

#define NUM_BUTTONS 3 
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {BT0, BT1, BT2};
Bounce * buttons = new Bounce[NUM_BUTTONS];

int oldPosition  = 0;
int newPosition  = 0;
unsigned long encoderDelay = millis();
volatile uint32_t encoderCount;

extern int spValue;
extern bool run_on;
extern int program_cycle;

void buttons_begin(){
    for (int i = 0; i < NUM_BUTTONS; i++) {
      buttons[i].attach( BUTTON_PINS[i] , INPUT_PULLUP  );       //setup the bounce instance for the current button
      buttons[i].interval(55);              // interval in ms
    }
    encoder = new RotaryEncoder(ENC0, ENC1, RotaryEncoder::LatchMode::TWO03);
    attachInterrupt(digitalPinToInterrupt(ENC0), checkPosition, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC1), checkPosition, CHANGE);

    
  
}

void check_button(){

    if ((millis() - encoderDelay > 200)) {
      encoderDelay = millis();
      
      newPosition = encoder->getPosition(); 
      if (newPosition != oldPosition) {
        if (oldPosition>newPosition){
          dec_ana();
        }   
        if (oldPosition<newPosition){
          inc_ana();
        }
        oldPosition = newPosition;
      }
    }

    for (int i = 0; i < NUM_BUTTONS; i++)  {
        buttons[i].update();
        if ( buttons[i].fell() ) {
        switch (i) {
            case 0:
            Serial.println("button0");
            choice_item_select(0);
            break;
            case 1:
            Serial.println("button1");
            choice_item_select(1);
            break;
            case 2:
            Serial.println("button2");
            choice_item_select(2);
            break;

            }
        }
    }
}  


void choice_item_select(int chg) {
  switch (chg) {
      case 0:
        run_on = !run_on;
        if (run_on){
          digitalWrite(PW_LED,LOW);
          digitalWrite(RUN_LED,HIGH);
          digitalWrite(P3_LED,HIGH);
        }else{
          digitalWrite(PW_LED,HIGH);
          digitalWrite(RUN_LED,LOW);
          digitalWrite(P3_LED,LOW);
        }
        break;
      case 1:
        program_cycle--;
        if (program_cycle<0){
          program_cycle=0;
        }
        show_display();
        

      break;
      case 2:
        
        program_cycle++;
        if (program_cycle>4){
          program_cycle=4;
        }
        show_display();
      

      break;


  }   

}


void checkPosition(){
  encoder->tick(); // just call tick() to check the state.
  // Serial.println("tick");
}

void inc_ana(){
    
    spValue += 5;
    if (spValue >= TEMP_MAX){
      spValue = TEMP_MAX;
    }
    Serial.print("inc: ");
    Serial.println(spValue);
    show_display();
}

void dec_ana(){
    
    spValue -= 5;
    if (spValue <= TEMP_MIN){
      spValue=TEMP_MIN;
    }
    Serial.print("dec: ");
    Serial.println(spValue);
    show_display();

}