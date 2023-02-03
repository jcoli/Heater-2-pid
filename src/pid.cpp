/**
Version: 0a
Tecnocoli - 06/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F411CE6 - HotPlate Soldier
**/
#include <Arduino.h>

#include "io_defines.h"
#include "analog_input.h"

void calc_pid();

float kp = 10.0;  //constante ganho proporcional
float ki = 25.2;
float kd = 28.5;
float Ti = 3000;   //Tempo Integral
float Td = 3000;    //Tempo Integral
float erro = 0;   //Erro
float erro_ant = 0; //erro anterior para ação derivativa
float P = 0;    //Ação Proporcional
float S = 0;    //Integrador
float I = 0;    //Ação Integral
float D = 0;    //Ação Integral

int pwm1 = 0;
int pwm2 = 0;

int spValue = 20;
int pvValue = 0;
int sensorValue = 0;
const int pin_mv = 9;
const int lim_int_sup = 29000;
const int lim_int_inf = -29000;
const int lim_pwm_sup = 8333;

extern float celsius;


void calc_pid(){
      read_analog();
      // Serial.println("PID");
      //leitura do valor de setpoint
      pvValue = celsius; //leitura do valor de setpoint
      erro = (spValue) - pvValue;


      P = erro * kp;


//       S = (S + erro) - (S/300);    //fórmula do integrador
      
      I = I + (ki * (I / Ti)); //fórmula da ação integral




//       D = (erro - erro_ant) * (Td*kd);
      D = kd * ((erro - erro_ant)/3000); 
      erro_ant = erro;
      pwm1 = (P + I + D);   //cálculo da ação final do controlador PI
      if (pwm1 > lim_pwm_sup) //limitador saída superior pwm
      {
             pwm1 = lim_pwm_sup;
      }
      if (pwm1 < 0) //limitador saída inferior pwm
      {
             pwm1 = 0;
      }


}