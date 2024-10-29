/*
 * led_display.h
 *
 *  Created on: Oct 19, 2024
 *      Author: ADMIN
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

void clearAllLED7(void);
void update_LED7_driver(uint8_t index);
void displayLED7(uint8_t index);
void update_all_clock_buffer(uint8_t time1, uint8_t time2);
void update_horizontal_clock_buffer(uint8_t time);
void update_vertical_clock_buffer(uint8_t time);

#endif /* INC_LED_DISPLAY_H_ */
