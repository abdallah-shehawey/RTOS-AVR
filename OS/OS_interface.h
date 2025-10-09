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
#include <stdint.h>

void RTOS_voidStart(void);

uint8_t RTOS_u8CreateTask(uint8_t Copy_u8Priority, uint16_t Copy_u16Periodicity, void (*Copy_pvTaskFunc)(void),
                          uint16_t Copy_u16FirstDelay);

void RTOS_voidSuspendTask(uint8_t Copy_u8Priority);

void RTOS_voidResumeTask(uint8_t Copy_u8Priority);

void RTOS_voidDeleteTask(uint8_t Copy_u8Priority);

#endif
