/**
Version: 0a
Tecnocoli - 06/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F411CE6 - HotPlate Soldier
**/

#ifndef __BUTTONS_H__
#define __BUTTONS_H__

void buttons_begin();
void checkPosition();
void check_button();
void dec_ana();
void inc_ana();
void choice_item_select(int chg);

#endif