/**
Version: 0a
Tecnocoli - 06/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F411CE6 - HotPlate Soldier
**/
#include <Arduino.h>

#include "io_defines.h"
#include "defines.h"

void pwm_output_begin();
void write_output();

extern float celsius;
extern int pwm1;
extern int pwm2;
extern bool zeroChangeDetect;
extern bool run_on;
extern int program_cycle;
int maximum_firing_delay = 8333;


void pwm_output_begin(){
    pinMode(PWM_OUT, OUTPUT);


}


void write_output(){
     //This delay controls the power
    if ((pwm1>0) && (run_on)){ 
        digitalWrite(PWM_OUT,HIGH);
        delayMicroseconds( pwm1);
        digitalWrite(PWM_OUT,LOW);
        digitalWrite(P2_LED,LOW);
        digitalWrite(P1_LED,HIGH);
    }else if(run_on){
        digitalWrite(P2_LED,HIGH);
        digitalWrite(P1_LED,LOW);

    }else{
        digitalWrite(P2_LED,LOW);
        digitalWrite(P1_LED,LOW);

    }
    zeroChangeDetect = false;

}