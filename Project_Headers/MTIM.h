/*! **********************************************************************************************
* 2014  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*
* @file:      MTIM.h
* @author(s): Mauricio Capistrán 
*
* @brief (User's Manual)
*    Used to configure the Modulo Timer (MTIM) for the S08QGMCU. 
*     *** Only compile-time configuration is allowed ***  
*     In other words, the timer cannot be reconfigured while the program is running.
*    
*    This driver currently only works using the BUS Clk. No support for external clock has been
*    implemented. 
*
**************************************************************************************************/

#ifndef MTIM_H_
#define MTIM_H_

 
/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include "types.h"  /* For the ISR Function Pointer typdef */
#include "derivative.h"

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/

/* These are user-configurable values */
#define MTIM_CLK_SRC_FREQ_MHZ  4     /* 4 Mhz Clock source. Change this value to the bus clock that you are using. Only 1, 2, 4, 8, 16 and 32 MHz are supported */
#define MTIM_PRESCALER_VAL     2     /* Set the watned prescaler value. Valid prescaler values are: 1, 2, 4, 8 16, 32, 64 */
#define MTIM_TICK_TIME_US      100   /* Set the desired period for the timer to generate events (in microseconds) */


/* Do not touch this code. It is used to verify at compile thime that the specified MTIM_TICK_TIME_US can be achieved with the selected MTIM_PRESCALER_VAL*/
#if (MTIM_CLK_SRC_FREQ_MHZ != 1 && MTIM_CLK_SRC_FREQ_MHZ != 2 && MTIM_CLK_SRC_FREQ_MHZ != 4 && MTIM_CLK_SRC_FREQ_MHZ != 8 && MTIM_CLK_SRC_FREQ_MHZ != 16 && MTIM_CLK_SRC_FREQ_MHZ != 32)
	#error "MTIM Invalid clock source frequency (MTIM_CLK_SRC_FREQ_MHZ). Valid valus are 1, 2, 4, 8, 16, 32"
#endif

#if (MTIM_PRESCALER_VAL != 1 && MTIM_PRESCALER_VAL != 2 && MTIM_PRESCALER_VAL != 4 && MTIM_PRESCALER_VAL != 8 && MTIM_PRESCALER_VAL != 16 && MTIM_PRESCALER_VAL != 32 && MTIM_PRESCALER_VAL != 64 && MTIM_PRESCALER_VAL != 128 && MTIM_PRESCALER_VAL != 256)
	#error "MTIM Invalid prescaler value (MTIM_PRESCALER_VAL). Valid values are: 1, 2, 4, 8, 16, 32, 64, 128, 256."
#endif

/* This vaulue specifies the terminal count on which the timer will get to MTIM_TICK_TIME_US */
#define MTIM_COUNTER_MODULE_VAL ( (128*MTIM_TICK_TIME_US) / (128*MTIM_PRESCALER_VAL/MTIM_CLK_SRC_FREQ_MHZ) )

#if (MTIM_COUNTER_MODULE_VAL > 255)
	#error "MTIM tick time unreachable, a bigger prescaler is needed"
#endif


/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************			 	 Functions Like Macros					**********************/
/*************************************************************************************************/
/*!*-----------------------------------------------------------------------------------------------
* \name     MTIM_Start
* \brief    Starts the timer (it does not restart the count). Implemented as function-like macro to
*           minimize footprint.
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
#define MTIM_Start()  (MTIMSC_TSTP = 0)

/*!*-----------------------------------------------------------------------------------------------
* \name     MTIM_Stop
* \brief    Stops the timer (it does not restart the count). Implemented as function-like macro to
*           minimize footprint.
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
#define MTIM_Stop()  (MTIMSC_TSTP = 1)


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
* \name     MTIM_Init
* \brief    This function will enable timer interrupts, reset and stop the timer, selects the clock 
*           source to be the bus clk, configures the prescaler, and configures the count modulo
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void MTIM_Init(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     MTIM_RegisterIsrCallback
* \brief    Registers a function to be called whenever the timer expires (period set by 
*           macro MTIM_TICK_TIME_MS). In the MTIM ISR, this function will be called.
* \param    MTIM_callback. Function pointer to the callback function
* \return   void
-------------------------------------------------------------------------------------------------*/
void MTIM_RegisterIsrCallback(ISR_callback isrPtr);


/*************************************************************************************************/
#endif /* MTIM_H_ */
