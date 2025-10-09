/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RTOS_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah AbdelMomen Shehawey
 *  Layer  : RTOS Stack
 *  SWC    : RTOS/Scheduler
 *
 */

#ifndef RTOS_PRIVATE_H_
#define RTOS_PRIVATE_H_
#include <stdint.h>
/*
  Hints :-
  1-the struct is used by me only so it is here (private.h)
  2-we will handle priority by another way so it is not here
    priority will be the index of tasks array
    we will check priority in voidScheduler
*/
typedef struct
{
  uint16_t Periodicity;
  void (*TaskFunc)(void);
  uint8_t State;
  uint16_t FirstDelay;
} Task_t;

static void voidScheduler(void);

#define TASK_RESUMED 0
#define TASK_SUSPENDED 1

#endif
