/*! **********************************************************************************************
* 2014  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*
*
* @file:      TimersManager.h
* @author(s): 	Mauricio Capistrán
*  updated by:  Rodrigo Mendoza Sánchez			A01224462 
* 				Tlakaelel Axayaktl Ceja Valadez	A01224781 
*
* @brief (User's Manual)
*    This module provides an array of software timers, which are all derived from the same hardware
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
*    The software timers sit on top of the S08 Modulo Timer (MTIM). It requires the MITM HAL to be
*    configured such that minimum error can be achieved for a 1ms count.
*    For timers with callback, when the timer expires the callback is called and the timer is stopped. 
*    Calling the TimersMngr_HasElapsed function on a timer with callback will always return false.
*    For timers without callback, the SwTimers_bHasElapsed function returns
*    
*    This software has a better resolution as the time intervals increase, but it has a bad resolution
*    as it gets smaller the time intervals.
**************************************************************************************************/

#ifndef TIMERS_MANAGER_H
#define TIMERS_MANAGER_H

 
/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include "types.h"

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define TIMERS_MANAGER_MAX_TIMERS   2 /* This macro specifies the max number of software timers allowed. 
                             	 	 	 Making it larger uses more memory, so keep it real */
#define TIMERS_MANAGER_INVALID_ID  	(0xFF)	/* After creating a timer, check against this to make sure 
                                        	you did get a valid ID */
#define TIMERS_MANAGER_MAX_COUNT    (0xFFFFFFFE) /* This is the largest allowed value for the timer count. 
                                            	 0xFFFFFFFF will disable the timer */

/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************			 	 Functions Like Macros					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Extern Variables					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Extern Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/
/*!*-----------------------------------------------------------------------------------------------
* \name     TimersMngr_Init
* \brief    Initialise software timers and hardware timers
* \param    None
* \return   None
-------------------------------------------------------------------------------------------------*/
void TimersMngr_Init(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     TimersMngr_PeriodicTask
* \brief    Update all active timers. This function should be called periodically inside the infinite loop.
* \param    None
* \return   None
-------------------------------------------------------------------------------------------------*/
void TimersMngr_PeriodicTask(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     TimersMngr_CreateTimer
* \brief    Create one timer id and its corresponding callback function. If the max number of
*           timers has been exceeded, then the function returns SWTIMERS_INVALID_ID
* \param    pCallbackFunc. pointer function to execute once the timer reach zero. The callback is optional
* \return   timer id
-------------------------------------------------------------------------------------------------*/
u8 TimersMngr_CreateTimer(pFunc_t pCallbackFunc);

/*!*-----------------------------------------------------------------------------------------------
* \name     TimersMngr_StartTimer
* \brief    Set time to decrement
* \param    timerId. The timerID acquired by the SwTimers_CreateTimer() function.
			microseconds. Timer value to count down from.
* \return   None
-------------------------------------------------------------------------------------------------*/
void TimersMngr_StartTimer(u8 timerId, i32 l32Microseconds);

/*!*-----------------------------------------------------------------------------------------------
* \name     TimersMngr_StopTimer
* \brief    Stops counting on the specified timer
* \param    timerId. The timerID acquired by the SwTimers_CreateTimer() function.
* \return   None
-------------------------------------------------------------------------------------------------*/
void TimersMngr_StopTimer(u8 timerId);

/*!*-----------------------------------------------------------------------------------------------
* \name     TimersMngr_TimerHasElapsed
* \brief    For timers with callback this function always returns false. It should only be used for
*           timers created without callback function.
* \param    timerId. The timerID acquired by the TimersMngr_newTimer() function.
* \return   true if the time has elapsed
-------------------------------------------------------------------------------------------------*/
bool TimersMngr_TimerHasElapsed(u8 u8TimerId);

/*!*-----------------------------------------------------------------------------------------------
* \name     TimersMngr_SetPointer
* \brief    Sets the pointer of a specific timer.
* \param    timerId. The timerID acquired by the TimersMngr_newTimer() function.
* \param	PCallbackFunc. Is the function that will be call when the timer elapsed.
* \return   none.
-------------------------------------------------------------------------------------------------*/
void  TimersMngr_SetPointer(u8 timerId, pFunc_t pCallbackFunc);

/*************************************************************************************************/
#endif /* TIMERS_MANAGER_H */
