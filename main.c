/*
 * main.c
 *
 *  Created on: 24 feb 2022
 *      Author: garci
 */
#include "MK64F12.h"
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#include "Bits.h"

#define DELAY_TIME 2.0f
#define SYSTEM_CLOCK (21000000U)

void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock , My_float_pit_t delay);

typedef struct
{
	void* ColorMatrix[2];
	float_t delay;
	void(*fptrdelay)(PIT_timer_t pit_timer, My_float_pit_t system_clock , My_float_pit_t delay);
	uint8_t next[3];
}State_t;

typedef enum {No_Color, Secuence_1, Secuence2, Secuence_3} Color_Secuences;
const State_t FSM[4] =
{
		{{off, off, off}, DELAY_TIME, PIT_delay, {No_Color, Secuence_1, Secuence2, Secuence_3}},
		{{yellow, red, purple}, DELAY_TIME, PIT_delay, {No_Color, Secuence_1, Secuence2, Secuence_3}},
		{{green, red, white}, DELAY_TIME, PIT_delay, {No_Color, Secuence_1, Secuence2, Secuence_3}},
		{{blue, green, white}, DELAY_TIME, PIT_delay, {No_Color, Secuence_1, Secuence2, Secuence_3}}
};
int main()
{
	while(1)
	{

	}
	return 0;
}
