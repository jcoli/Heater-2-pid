/**
Version: 0a
Tecnocoli - 06/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F411CE6 - HotPlate Soldier
**/

#include <Arduino.h>
#include "STM32TimerInterrupt.h"
#include "STM32_ISR_Timer.h"

#include "io_defines.h"
#include "defines.h"
#include "buttons.h"
#include "analog_input.h"
#include "display.h"
#include "pwm_output.h"
#include "digital_output.h"
#include "analog_input.h"

STM32Timer ITimer(TIM1);
STM32_ISR_Timer ISR_Timer;

#define TIMER_INTERVAL_0_3S           300L
#define TIMER_INTERVAL_1S             1000L
#define TIMER_INTERVAL_1_5S           1500L
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0
#define TIMER_INTERVAL_MS         100
#define HW_TIMER_INTERVAL_MS      50

void show_display();
void read_analog();
void calc_pid();
void TimerHandler();
void zeroDetect(); 

float celsius = 0;

bool flash_led = false;

//PID


//zero detect
bool zeroChangeDetect = false;
bool lastZeroState = false;
bool run_on = false;
int program_cycle = 0;


unsigned long loopDelay = millis();
unsigned long loopDelayRead = millis();
unsigned long loopDelayWrite = millis();

extern float erro;
extern float erro_ant;
extern float P;
extern float S;
extern float I;
extern float D;
extern int pwm1;
extern int spValue;
extern int pvValue;


void setup() {
  Serial.begin(115200);
  Serial.println("setup");
  delay(7000);
  
  
  pinMode(INT_LED, OUTPUT);
  pinMode(INT_ZERO, INPUT_PULLDOWN);

  display_begin();
  buttons_begin(); 
  digital_output_begin();
  analog_input_begin();
  pwm_output_begin();

  delay(1000);

  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler))
  {
    Serial.print(F("Starting ITimer OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer. Select another freq. or timer"));

  attachInterrupt(digitalPinToInterrupt(INT_ZERO), zeroDetect, FALLING);

  delay(300);
  
  
  ISR_Timer.setInterval(TIMER_INTERVAL_0_3S,  calc_pid);
  ISR_Timer.setInterval(TIMER_INTERVAL_1S,  show_display);


}

void loop() {
  check_button();
  if (millis() - loopDelay > 2000)
  {
      loopDelay = millis();    
      digitalWrite(INT_LED, flash_led);
      Serial.println(celsius);
      flash_led = !flash_led;
        // if (zeroChangeDetect){
        Serial.print("pwm: ");
        Serial.println(pwm1);
        //   zeroChangeDetect = false;
        // }  
  }    
      
      
  
  
}

void zeroDetect(){
    if (!digitalRead(INT_ZERO)){
       zeroChangeDetect = true; 
       write_output();
    }
}




void TimerHandler()
{
  ISR_Timer.run();
}

