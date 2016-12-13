/*! **********************************************************************************************
* 2014  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*  
*
* @file:      MTIM.c
* @author(s): Mauricio Capistrán  
*
* @brief (Theory of Operation)
*   Pretty straight forward. It configures the MTIM hardware and implements the interrupt, on which
*   it calls the registered callback (if any)
**************************************************************************************************/



/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include "MTIM.h"
#include "derivative.h"

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#if (MTIM_PRESCALER_VAL == 1)
   #define MTIM_PRESCALER_SETTING  0x00
#elif (MTIM_PRESCALER_VAL == 2)
   #define MTIM_PRESCALER_SETTING  0x01
#elif (MTIM_PRESCALER_VAL == 4)
   #define MTIM_PRESCALER_SETTING  0x02
#elif (MTIM_PRESCALER_VAL == 8)
   #define MTIM_PRESCALER_SETTING  0x03
#elif (MTIM_PRESCALER_VAL == 16)
   #define MTIM_PRESCALER_SETTING  0x04
#elif (MTIM_PRESCALER_VAL == 32)
   #define MTIM_PRESCALER_SETTING  0x05
#elif (MTIM_PRESCALER_VAL == 64)
   #define MTIM_PRESCALER_SETTING  0x06
#elif (MTIM_PRESCALER_VAL == 128)
   #define MTIM_PRESCALER_SETTING  0x07
#elif (MTIM_PRESCALER_VAL == 256)
   #define MTIM_PRESCALER_SETTING  0x08
#endif

/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/
interrupt VectorNumber_Vmtim void MTIM_isr();

/*************************************************************************************************/
/*********************                  Static Variables                    **********************/
/*************************************************************************************************/
static ISR_callback sMtimIsrCallback;

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
void MTIM_Init(void)
{
	MTIMSC  =  0x50; /* Enable timer interrupts, reset count, stop timer */
	MTIMCLK = MTIM_PRESCALER_SETTING; /* Select clock source to be bus clock, and configure the prescaler */
	MTIMMOD = MTIM_COUNTER_MODULE_VAL;
}

/* --------------------------------------------------------------------------------------------- */
void MTIM_RegisterIsrCallback(ISR_callback isrPtr)
{
    if(isrPtr) /* check for a NULL pointer */
    {
    	sMtimIsrCallback = isrPtr;
    }
    else
    {
        /*INVALID*/
    }
                              
}
/*************************************************************************************************/
/*********************				    Private Functions					**********************/
/*************************************************************************************************/

interrupt VectorNumber_Vmtim void MTIM_isr()
{
	/* Clear TOF by reading the MTIMSC register while TOF is set, then writing a 0 to TOF */
	char dummyRead;
	dummyRead = MTIMSC;
	MTIMSC_TOF = 0;
	
	/* If the ISR Callback has been registered, then call it */
	if (sMtimIsrCallback)  
	{
		(*sMtimIsrCallback)();
	}
}
