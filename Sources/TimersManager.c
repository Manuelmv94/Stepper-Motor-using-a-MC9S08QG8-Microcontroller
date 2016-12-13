/*! **********************************************************************************************
* 2014  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*  
*
* @file:      TimersManager.c
* @author(s): 	Mauricio Capistrán
*  updated by:  Rodrigo Mendoza Sánchez			A01224462 
* 				Tlakaelel Axayaktl Ceja Valadez	A01224781 
*
* @brief (Theory of Operation)
*
**    This module provides an array of software timers, which are all derived from the same hardware
*    timer.
*    Each software timer can be started and stopped independently.
*    Each timer contains two elements (in a struct called TimerObj):
*      1. A count. The value, in microseconds, that the timer will count down to.
*      2. An event callback (a function to be called when the timer expires).
*    The resolution of these timers is not great, so they should not be used when very precise
*    timing is required. The reasons for the inaccuracy of the software timers are:
*      a. It is based on the MTIM. Depending on the clock source frequency, the 1 ms tick required
*         by the software timers might be slightly off.
*      b. A single HW timer is used to update all software timers, it 
*    To get the best possible timer resolution, you should call the TimersMngr_PeriodicTask() function
*    as quickly as possible. 
*		The software timers sit on top of the S08 Modulo Timer (MTIM). It requires the MITM HAL to be
*    configured to call the TimersMngr_UpdateCount function every millisecond or less.
**************************************************************************************************/


/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include "TimersManager.h"
#include "MTIM.h"

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define TIMER_INACTIVE                   (u32) 0xFFFFFFFF
#define M_NULL (0)
/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/
/* Timer object. Each timer has a timer count and a function pointer for a callback event */
typedef struct
{
    i32 i32TimerCount;
    pFunc_t pTimerEvent;
}TimerObj;

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/
void TimersMngr_UpdateCount(void); /* This is the function registerd as callback for the MTIM */

/*************************************************************************************************/
/*********************                  Static Variables                    **********************/
/*************************************************************************************************/
static TimerObj sTimersObjArray[TIMERS_MANAGER_MAX_TIMERS]; /* array that holds all the timers */
static u8 su8Timers;          /* Number of timers that have been created */
static u16 su16ElapsedTime;   /* Keeps the number of microseconds elapsed since the last time the timers were updated */
static u8 su8ActiveTimers;    /* Keeps the number of active timers */

/*************************************************************************************************/
/*********************					Global Variables					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Static Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Global Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************				   Exported Functions					**********************/
/*************************************************************************************************/
void TimersMngr_Init(void)
{
	/* Initialize the structure that holds all software timers */
    u8 i = TIMERS_MANAGER_MAX_TIMERS;
    while (i--)
    {
    	sTimersObjArray[i].i32TimerCount = TIMER_INACTIVE;	/* Set all timers inactive */
    	sTimersObjArray[i].pTimerEvent   = M_NULL;
    }
    su8ActiveTimers = 0;
    
    /* Initialize the number of created timers to zero */
    su8Timers = 0;

    /* Initialize the HAL for the timer and register the callback */
    MTIM_Init();
    MTIM_RegisterIsrCallback(&TimersMngr_UpdateCount);
	MTIM_Start();
}

/* --------------------------------------------------------------------------------------------- */
void TimersMngr_PeriodicTask(void)
{
    u8 i;
    u16 time = su16ElapsedTime;
    /* Reset the time elapsed since the last time the periodic task was called */
	su16ElapsedTime = 0u;
            
    if(time > 0u)  /* Update the timers if needed */
    {
        for(i=0; i<su8Timers; i++) /* loop through all created timers */
        {
        	/* Decrement time on active timers */
            if(sTimersObjArray[i].i32TimerCount != TIMER_INACTIVE)	
            {
            	/*Updates count of the timer*/
                if(sTimersObjArray[i].i32TimerCount > time )
                {
                	sTimersObjArray[i].i32TimerCount -= time;
                }
                else { 
                	sTimersObjArray[i].i32TimerCount = TIMER_INACTIVE;
                }
                
                /* Call callback if timer has elapsed and if there is a registered callback for the expired timer */
                if(TIMER_INACTIVE == sTimersObjArray[i].i32TimerCount) 
                {
                	//TimersMngr_StopTimer(i);  /* Stop the timer so that the callback only get's called once */
					if (sTimersObjArray[i].pTimerEvent != M_NULL){
						sTimersObjArray[i].pTimerEvent();		/* execute timer's callback function */
					}
                }
            } // if(sTimersObjArray[i].i32TimerCount != TIMER_INACTIVE)	
        } // for(i=0; i<su8Timers; i++)
    } // if(time > 0u)
}

/* --------------------------------------------------------------------------------------------- */
u8 TimersMngr_CreateTimer(pFunc_t pCallbackFunc)
{
    /* If the max number of timers has not been exceeded, then create a new timer and increase the
     * number of timers active. 
     */
    if(su8Timers < TIMERS_MANAGER_MAX_TIMERS)
    {
        if(pCallbackFunc != M_NULL)
        {
        	sTimersObjArray[su8Timers].pTimerEvent = pCallbackFunc;
        }
        return su8Timers++;
    }
   	return TIMERS_MANAGER_INVALID_ID;
}

/* --------------------------------------------------------------------------------------------- */
void TimersMngr_StartTimer(u8 u8TimerId, i32 i32Microseconds)
{
	
	if (u8TimerId <= su8Timers && sTimersObjArray[u8TimerId].i32TimerCount == TIMER_INACTIVE) /* Check the timerID is valid */
	{
		sTimersObjArray[u8TimerId].i32TimerCount = i32Microseconds;
		su8ActiveTimers++;
	}
}

/* --------------------------------------------------------------------------------------------- */
void TimersMngr_StopTimer(u8 u8TimerId)
{
	if (u8TimerId <= su8Timers) /* Check the timerID is valid */
	{
		su8ActiveTimers--;
		sTimersObjArray[u8TimerId].i32TimerCount = TIMER_INACTIVE;
	}
}

/* --------------------------------------------------------------------------------------------- */
bool TimersMngr_TimerHasElapsed(u8 u8TimerId)
{
    return (TIMER_INACTIVE == sTimersObjArray[u8TimerId].i32TimerCount);
}

/* --------------------------------------------------------------------------------------------- */
void  TimersMngr_SetPointer(u8 u8TimerID, pFunc_t pCallbackFunc)
{
	if(u8TimerID <= su8Timers)
	{
		if(pCallbackFunc != M_NULL)
		{
			sTimersObjArray[u8TimerID].pTimerEvent = pCallbackFunc;
		}
	}
}

/*************************************************************************************************/
/*********************				    Private Functions					**********************/
/*************************************************************************************************/
void TimersMngr_UpdateCount(void)
{
	/* This function should be called by the HAL timer every us */
	su16ElapsedTime += MTIM_TICK_TIME_US;
}
