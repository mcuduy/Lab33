/*
 * led_display.c
 *
 *  Created on: Oct 19, 2024
 *      Author: ADMIN
 */

#include "main.h"
#include "led_display.h"

#define NUMBER_OF_7_SEG_LED 4

static uint8_t LED7Conversion[10]={
		0x3f,  // 0
		0x06,  // 1
		0x5b,  // 2
		0x4f,  // 3
		0x66,  // 4
		0x6d,  // 5
		0x7d,  // 6
		0x07,  // 7
		0x7f,  // 8
		0x67   // 9
};

// Buffer to store number after update LED7 time
static uint8_t numBuffer[NUMBER_OF_7_SEG_LED];

// Buffer to store value of LED7 conversion
static uint8_t buffer[NUMBER_OF_7_SEG_LED];

// Turn off all LED7
void clearAllLED7(void){
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN3_Pin, SET);
}

// Update all buffers when in modify time
void update_all_clock_buffer(uint8_t time1, uint8_t time2){
	numBuffer[0] = time1/10;
	numBuffer[1] = time1%10;
	numBuffer[2] = time2/10;
	numBuffer[3] = time2%10;
}

// Update buffer0 and buffer1 when modify time in horizontal
void update_horizontal_clock_buffer(uint8_t time) {
	numBuffer[0] = time/10;
	numBuffer[1] = time%10;
}

// Update buffer2 and buffer3 when modify time in vertical
void update_vertical_clock_buffer(uint8_t time) {
	numBuffer[2] = time/10;
	numBuffer[3] = time%10;
}

// Scan LED7 before display
void update_LED7_driver(uint8_t index){
	clearAllLED7();
	switch (index){
	case 0:
		buffer[0]=LED7Conversion[numBuffer[0]];
		displayLED7(0);
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,0);
		break;
	case 1:
		buffer[1]=LED7Conversion[numBuffer[1]];
		displayLED7(1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,0);
		break;
	case 2:
		buffer[2]=LED7Conversion[numBuffer[2]];
		displayLED7(2);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,0);
		break;
	case 3:
		buffer[3]=LED7Conversion[numBuffer[3]];
		displayLED7(3);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,0);
		break;
	}
}

// Display LED7
void displayLED7(uint8_t index){
	HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, !((buffer[index]>>0)&0x01));
	HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, !((buffer[index]>>1)&0x01));
	HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, !((buffer[index]>>2)&0x01));
	HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, !((buffer[index]>>3)&0x01));
	HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, !((buffer[index]>>4)&0x01));
	HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, !((buffer[index]>>5)&0x01));
	HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, !((buffer[index]>>6)&0x01));
}
