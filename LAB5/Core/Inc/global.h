/*
 * global.h
 *
 *  Created on: Nov 20, 2024
 *      Author: Administrator
 */


#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <command_parser_fsm.h>
#include <uart_communiation_fsm.h>
#include <software_timer.h>
#include <string.h>
#include <stdio.h>


#define MAX_BUFFER_SIZE 30
#define CMD_IDLE 11
#define CMD_CHECK 22
#define CMD_WAIT 33
#define UART_SEND 44
#define UART_RESEND 55

extern int state;
int comPareStrings(uint8_t *buffer, uint8_t *input);
#endif /* INC_GLOBAL_H_ */
