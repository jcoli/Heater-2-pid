/**
Version: 0a
Tecnocoli - 06/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F411CE6 - HotPlate Soldier
**/
#include <Arduino.h>

#include "io_defines.h"

void digital_output_begin();

void digital_output_begin(){
    pinMode(PW_LED, OUTPUT);
    pinMode(RUN_LED, OUTPUT);  
    pinMode(OVER_LED, OUTPUT);  
    pinMode(P1_LED, OUTPUT);  
    pinMode(P2_LED, OUTPUT);  
    pinMode(P3_LED, OUTPUT); 
    digitalWrite(PW_LED,HIGH);
    delay(500); 
    digitalWrite(PW_LED,LOW);
    digitalWrite(RUN_LED,HIGH);
    delay(500); 
    digitalWrite(RUN_LED,LOW);
    digitalWrite(OVER_LED,HIGH);
    delay(500); 
    digitalWrite(OVER_LED,LOW);
    digitalWrite(P1_LED,HIGH);
    delay(500); 
    digitalWrite(P1_LED,LOW);
    digitalWrite(P2_LED,HIGH);
    delay(500); 
    digitalWrite(P2_LED,LOW);
    digitalWrite(P3_LED,HIGH);
    delay(500); 
    digitalWrite(P3_LED,LOW);
    digitalWrite(PW_LED,HIGH);


}

