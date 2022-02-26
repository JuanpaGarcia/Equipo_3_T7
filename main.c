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

extern uint8_t g_flag_port_C;
extern uint8_t g_flag_port_A;
extern uint8_t g_PIT0_flag;

typedef struct
{
	void* ColorMatrix[2];
	float_t delay;
	void(*fptrdelay)(PIT_timer_t pit_timer, My_float_pit_t system_clock , My_float_pit_t delay);
	uint8_t next[3];
}State_t;

typedef enum {No_Color, Secuence_1, Secuence2, Secuence_3} Color_Secuences;

const State_t FSM[3] =
{
		{{off, off, off}, DELAY_TIME, PIT_delay, {No_Color, Secuence_1, Secuence2, Secuence_3}},
		{{yellow, red, purple}, DELAY_TIME, PIT_delay, {No_Color, Secuence_1, Secuence2, Secuence_3}},
		{{green, red, white}, DELAY_TIME, PIT_delay, {No_Color, Secuence_1, Secuence2, Secuence_3}},
		{{blue, green, white}, DELAY_TIME, PIT_delay, {No_Color, Secuence_1, Secuence2, Secuence_3}}
};

void init_interrupt();
void init();

int main()
{
	init();
	init_interrupt();
	uint8_t state_port_C = 0;
	uint8_t state_port_A = 0;

	while(1)
	{

	}
	return 0;
}

void init()
{
	gpio_pin_control_register_t input_intr_config = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE; // SW interrupt config
	gpio_pin_control_register_t pcr_gpioe_pin_led = GPIO_MUX1;

	GPIO_clock_gating(GPIO_A);
	GPIO_clock_gating(GPIO_B);
	GPIO_clock_gating(GPIO_C);

	GPIO_pin_control_register(GPIO_A,4, &input_intr_config);
	GPIO_pin_control_register(GPIO_C,6, &input_intr_config);
	GPIO_pin_control_register(GPIO_B,21,&pcr_gpioe_pin_led);
	GPIO_pin_control_register(GPIO_B,22,&pcr_gpioe_pin_led);
	GPIO_pin_control_register(GPIO_E,26,&pcr_gpioe_pin_led);

	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_21);
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_22);
	GPIO_data_direction_pin(GPIO_E, GPIO_OUTPUT, bit_26);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_6);
	GPIO_data_direction_pin(GPIO_A, GPIO_INPUT, bit_4);

	PIT_clock_gating();
	PIT_enable();

	PIT_delay(PIT_0, SYSTEM_CLOCK, DELAY);
}



void init_interrupt()
{

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_set_basepri_threshold(PRIORITY_10);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_3);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_4);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ, PRIORITY_4);

	NVIC_global_enable_interrupts;

}
