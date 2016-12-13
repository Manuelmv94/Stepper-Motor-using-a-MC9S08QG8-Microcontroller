/*! **********************************************************************************************
* 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*  
*
* @file:      StepManager.c
* @author(s): Manuel Madrigal Valenzuela; Efraín Duarte López
*
* @brief (Theory of Operation)
*     This driver uses the GPIO driver to induce a coil of the stepper motor at a time. It keeps 
*     the current step in a static variable (u8CurrentStep) which is the index of the array that
*     contains each of the half steps of the sequence (u8StepArray).
*
**************************************************************************************************/


/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include "GPIO.h"
#include "StepManager.h"

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define STEPPER_FIRST_STEP    0     /* Specify which is the first step on the sequence (It is not recommended to modify) */
#define STEPPER_LAST_STEP     7     /* Specify which is the last step on the sequence*/
#define STEPPER_OVERFLOW_CONDITION  8
#define STEPPER_UNDERFLOW_CONDITION 255

/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/
void StepManager_SetValue (u8 val); 
void StepManager_ResetClockwiseMode(void);
void StepManager_ResetCounterClockwiseMode(void);
bool StepManager_Overflow(void);
bool StepManager_Underflow(void);

/*************************************************************************************************/
/*********************                  Static Variables                    **********************/
/*************************************************************************************************/
static u8 u8CurrentStep;  // This variable will keep the current step of the sequence
static u8 u8StringVal;    //This variable contains the current value on the PORT

/*************************************************************************************************/
/*********************					Global Variables					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Static Constants                    **********************/
/*************************************************************************************************/

static const u8 u8StepArray[]={0x01,0x03,0x02,0x06,0x04,0x0C,0x8,0x09}; //This array contains each of the values that make each of the half steps of the sequence

/*************************************************************************************************/
/*********************                  Global Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************				   Exported Functions					**********************/
/*************************************************************************************************/

void StepManager_Init(void)
{
	u8CurrentStep = STEPPER_FIRST_STEP;
	StepManager_SetValue(u8StepArray[u8CurrentStep]);
	GPIO_CONFIG_PORT_OUT(STEPPER_PORT, STEPPER_PIN_START, STEPPER_PIN_OUTS);
}

//-------------------------------------------------------------------------------------------------
void StepManager_RotateClockWise(void)
{
   StepManager_SetValue(u8StepArray[u8CurrentStep++]);
   if(StepManager_Overflow())      //If we finished the sequence
   {
      StepManager_ResetClockwiseMode();  //Start over again
   }
}

//-------------------------------------------------------------------------------------------------
void StepManager_RotateCounterClockWise(void)
{
   StepManager_SetValue(u8StepArray[u8CurrentStep--]);
   if(StepManager_Underflow())     //If we finished the sequence
   {
      StepManager_ResetCounterClockwiseMode(); //Start over again
   }
}



/*************************************************************************************************/
/*********************				    Private Functions					**********************/
/*************************************************************************************************/
void StepManager_SetValue (u8 val)
{
	u8 u8PortVal = GPIO_READ_PORT(STEPPER_PORT) & !STEPPER_MASK;	// Read the port and keep all the bits that are not part of the stepper, so those bits are not modified
	u8StringVal = (val  << STEPPER_PIN_START) & STEPPER_MASK;				// Set the internal variable to the value passed as parameter.			
	GPIO_WRITE_PORT (STEPPER_PORT, u8StringVal | u8PortVal);		// Write the value to the port
}

/*!*-----------------------------------------------------------------------------------------------
* \name     StepManager_ResetClockwiseMode
* \brief    Sets the stepper to it's initial condition (configured as Clockwise )
* \param    void.
* \return   void
-------------------------------------------------------------------------------------------------*/
void StepManager_ResetClockwiseMode(void)
{
   u8CurrentStep=STEPPER_FIRST_STEP; // Set the first step of the sequence on Clockwise mode
}


/*!*-----------------------------------------------------------------------------------------------
* \name     StepManager_ResetCounterClockwiseMode
* \brief    Sets the stepper to it's initial condition (configured as Counter Clockwise )
* \param    void.
* \return   void
-------------------------------------------------------------------------------------------------*/
void StepManager_ResetCounterClockwiseMode(void)
{
   u8CurrentStep=STEPPER_LAST_STEP; // Set the first step of the sequence on Counter Clockwise mode
}


/*!*-----------------------------------------------------------------------------------------------
* \name     StepManager_Overflow
* \brief    Notifies if the there is an overflow on the array containing the steps
* \param    void
* \return   bool
-------------------------------------------------------------------------------------------------*/
bool StepManager_Overflow(void)
{
   return (u8CurrentStep == STEPPER_OVERFLOW_CONDITION );
}

/*!*-----------------------------------------------------------------------------------------------
* \name     StepManager_Underflow
* \brief    Notifies if the there is an underflow on the array containing the steps
* \param    void
* \return   bool
-------------------------------------------------------------------------------------------------*/
bool StepManager_Underflow(void)
{
   return (u8CurrentStep == STEPPER_UNDERFLOW_CONDITION );
}


