/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RTOS_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah AbdelMomen Shehawey
 *  Layer  : RTOS Stack
 *  SWC    : RTOS/Scheduler
 *
 */

#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_


#define OK                     0
#define NOK                    1
#define NULL_POINTER           2
#define BUSY_STATE             3
#define TIMEOUT_STATE          4

#define NULL                   0

#include <stdint.h>

void RTOS_voidStart(void);

uint8_t RTOS_uint8_tCreateTask(uint8_t Copy_uint8_tPriority, uint16_t Copy_uint16_tPeriodicity, void (*Copy_pvTaskFunc)(void),
                          uint16_t Copy_uint16_tFirstDelay);

void RTOS_voidSuspendTask(uint8_t Copy_uint8_tPriority);

void RTOS_voidResumeTask(uint8_t Copy_uint8_tPriority);

void RTOS_voidDeleteTask(uint8_t Copy_uint8_tPriority);

#endif
