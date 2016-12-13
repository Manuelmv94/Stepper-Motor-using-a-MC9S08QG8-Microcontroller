/*! **********************************************************************************************
* 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*
*
* @file:      StepManager.h
* @author(s): Manuel Madrigal Valenzuela; Efraín Duarte López
*
* @brief (User's Manual)
*  This manager controls which step of the sequence is active . It requires for all
*  outputs of the motor to be on the same PORT and in consecutive PINs. Then, you can use the functions 
*  to rotate right, left, or reset the sequence to the initial condition. 
*  
*  At Init, it starts on the step defined by STEPPER_FIRST_STEP .
*  It uses positive logic to activate the steps (1 on the port = ON)
*  This manager has been tested on the following NXP MCUs:
*     + MC9S08QG8
**************************************************************************************************/

#ifndef STEPMANAGER_H_
#define STEPMANAGER_H_


/*************************************************************************************************/
/*********************                 Includes                **********************/
/*************************************************************************************************/
#include "types.h"

/*************************************************************************************************/
/*********************                 Defines                    **********************/
/*************************************************************************************************/



/* Driver configuration. The user should modify these values */
#define STEPPER_PORT          B  /* Specify the digital port where the stepper motor is connected */
#define STEPPER_PIN_START     4   /* Specify the starting pin on the digital port where the stepper motor is connected */


/* These should not be modified by the user */
#define STEPPER_PIN_OUTS      4     /*These are used to control the internal coils of the stepper(It is not recommended to modify)*/
#define STEPPER_MASK  (  0x0F  << STEPPER_PIN_START  )
#define STEPPER_INIT_CONDITION  (0x01 << STEPPER_PIN_START)


#if (STEPPER_PIN_START > STEPPER_PIN_OUTS)
#error "StepManager.h. STEPPER_PIN_START  must be less than 5, since digital ports are 8-bits wide and the motor has 4 outputs";
#endif

/*************************************************************************************************/
/*********************                 Typedefs                **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************            Functions Like Macros              **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************              Extern Variables              **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Extern Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************              Function Prototypes              **********************/
/*************************************************************************************************/

/*!*-----------------------------------------------------------------------------------------------
* \name     StepManager_Init
* \brief    Initalizes the GPIO pins used for the stepper motor and it sets it to the initial condition
*           which is declared on STEPPER_FIRST_STEP
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void StepManager_Init(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     StepManager_RotateClockWise
* \brief    It rotates the stepper in clockwise mode. 
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void StepManager_RotateClockWise(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     StepManager_RotateCounterClockWise
* \brief    It rotates the stepper in counter clockwise mode . 
* \param    void.
* \return   void
-------------------------------------------------------------------------------------------------*/
void StepManager_RotateCounterClockWise(void);



/*************************************************************************************************/
#endif /* STEPMANAGER_H_ */


