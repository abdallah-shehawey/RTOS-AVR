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

u8 RTOS_u8CreateTask(u8 Copy_u8Priority, u16 Copy_u16Periodicity, void (*Copy_pvTaskFunc)(void), u16 Copy_u16FirstDelay)
{
  u8 Local_u8ErrorState = OK;

  /*Check if the required priority is empty or used before for another task*/
  if (SystemTasks[Copy_u8Priority].TaskFunc == NULL)
  {
    SystemTasks[Copy_u8Priority].Periodicity = Copy_u16Periodicity;
    SystemTasks[Copy_u8Priority].TaskFunc = Copy_pvTaskFunc;
    SystemTasks[Copy_u8Priority].State = TASK_RESUMED; // Initialize the task state
    SystemTasks[Copy_u8Priority].FirstDelay = Copy_u16FirstDelay;
  }
  else
  {
    /*Priority is reserved before, don't create the task*/
    Local_u8ErrorState = NOK;
  }

  return Local_u8ErrorState;
}

void RTOS_voidDeleteTask(u8 Copy_u8Priority)
{
  SystemTasks[Copy_u8Priority].TaskFunc = NULL;
}

void RTOS_voidSuspendTask(u8 Copy_u8Priority)
{
  SystemTasks[Copy_u8Priority].State = TASK_SUSPENDED;
}

void RTOS_voidResumeTask(u8 Copy_u8Priority)
{
  SystemTasks[Copy_u8Priority].State = TASK_RESUMED;
}

/* This func run in Timer ISR  */
static void voidScheduler(void)
{
  u8 Local_u8TaskCounter;

  /*loop on all tasks to check their periodicity*/
  for (Local_u8TaskCounter = 0; Local_u8TaskCounter < TASK_NUM; Local_u8TaskCounter++)
  {
    /*Check if the task is suspended or not*/
    if (SystemTasks[Local_u8TaskCounter].State == TASK_RESUMED)
    {
      if (SystemTasks[Local_u8TaskCounter].FirstDelay == 0)
      {
        /*Invoke the task function*/
        if (SystemTasks[Local_u8TaskCounter].TaskFunc != NULL)
        {
          SystemTasks[Local_u8TaskCounter].TaskFunc();

          /*Assign the first delay parameter to the periodicity minus 1*/
          SystemTasks[Local_u8TaskCounter].FirstDelay = SystemTasks[Local_u8TaskCounter].Periodicity - 1;
        }
        else
        {
          /*Decrement the first delay*/
          SystemTasks[Local_u8TaskCounter].FirstDelay--;
        }
      }
    }
    else
    {
      /*Task is suspended, do nothing*/
    }
  }
}
