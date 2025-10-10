/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RTOS_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah AbdelMomen Shehawey
 *  Layer  : RTOS Stack
 *  SWC    : RTOS/Scheduler
 *
 */

#include <stdint.h>

#include "../GIE/GIE_interface.h"
#include "../TIMER/TIMER_interface.h"


#include "OS_config.h"
#include "OS_interface.h"
#include "OS_private.h"

/* Global Array of struct for tasks (uses in two functions)  */
Task_t SystemTasks[TASK_NUM] = {{NULL}}; /* All Structures = NULL */

void RTOS_voidStart(void)
{
  /* initialize the system */
  TIMER_u8SetCallBack(&voidScheduler, 0);
  GIE_vEnable();
  TIMER0_vInit();
}

uint8_t RTOS_uint8_tCreateTask(uint8_t Copy_uint8_tPriority, uint16_t Copy_uint16_tPeriodicity, void (*Copy_pvTaskFunc)(void), uint16_t Copy_uint16_tFirstDelay)
{
  uint8_t Local_uint8_tErrorState = OK;

  /*Check if the required priority is empty or used before for another task*/
  if (SystemTasks[Copy_uint8_tPriority].TaskFunc == NULL)
  {
    SystemTasks[Copy_uint8_tPriority].Periodicity = Copy_uint16_tPeriodicity;
    SystemTasks[Copy_uint8_tPriority].TaskFunc = Copy_pvTaskFunc;
    SystemTasks[Copy_uint8_tPriority].State = TASK_RESUMED; // Initialize the task state
    SystemTasks[Copy_uint8_tPriority].FirstDelay = Copy_uint16_tFirstDelay;
  }
  else
  {
    /*Priority is reserved before, don't create the task*/
    Local_uint8_tErrorState = NOK;
  }

  return Local_uint8_tErrorState;
}

void RTOS_voidDeleteTask(uint8_t Copy_uint8_tPriority)
{
  SystemTasks[Copy_uint8_tPriority].TaskFunc = NULL;
}

void RTOS_voidSuspendTask(uint8_t Copy_uint8_tPriority)
{
  SystemTasks[Copy_uint8_tPriority].State = TASK_SUSPENDED;
}

void RTOS_voidResumeTask(uint8_t Copy_uint8_tPriority)
{
  SystemTasks[Copy_uint8_tPriority].State = TASK_RESUMED;
}

/* This func run in Timer ISR  */
static void voidScheduler(void)
{
  uint8_t Local_uint8_tTaskCounter;

  /*loop on all tasks to check their periodicity*/
  for (Local_uint8_tTaskCounter = 0; Local_uint8_tTaskCounter < TASK_NUM; Local_uint8_tTaskCounter++)
  {
    /*Check if the task is suspended or not*/
    if (SystemTasks[Local_uint8_tTaskCounter].State == TASK_RESUMED)
    {
      if (SystemTasks[Local_uint8_tTaskCounter].FirstDelay == 0)
      {
        /*Invoke the task function*/
        if (SystemTasks[Local_uint8_tTaskCounter].TaskFunc != NULL)
        {
          SystemTasks[Local_uint8_tTaskCounter].TaskFunc();

          /*Assign the first delay parameter to the periodicity minus 1*/
          SystemTasks[Local_uint8_tTaskCounter].FirstDelay = SystemTasks[Local_uint8_tTaskCounter].Periodicity - 1;
        }
        else
        {
          /*Decrement the first delay*/
          SystemTasks[Local_uint8_tTaskCounter].FirstDelay--;
        }
      }
    }
    else
    {
      /*Task is suspended, do nothing*/
    }
  }
}
