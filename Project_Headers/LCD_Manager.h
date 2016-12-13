/*! **********************************************************************************************
 * 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores
 *
 * @file:      LCD_Manager.h
 * @author(s):    Manuel Madrigal Valenzuela; Efraín Duarte López    
 *
 * @brief (User's Manual):
 *    This manager controls the transmission of messages into a 2x16 LCD display.
 *    In order to send a message the user should check first if the manager is not already busy sending 
 *    a previous message. This is done by the LCDManager_TxIsBusy() function; once the user is sure
 *    that the manager isn't busy he can send the new message with the LCDManager_WriteMessage function,
 *    which only prepares the message to be send. The whole process is controlled by the Periodic Task,
 *    which partitions the process in little pieces that are done once every occurrence of the loop,
 *    Characterising the transmission as a non-blocking process.
 **************************************************************************************************/

#ifndef LCD_MANAGER_H_
#define LCD_MANAGER_H_


/*************************************************************************************************/
/*********************                 Includes                **********************/
/*************************************************************************************************/
#include "derivative.h" /* include peripheral declarations */
#include "types.h"
#include "SPI.h"
#include "GPIO.h"
/*************************************************************************************************/
/*********************                 Defines                    **********************/
/*************************************************************************************************/
/* Driver configuration. The user should modify these values */
#define LCDMANAGER_MAX_MSG_SIZE  16
#define ACTION_SELECT_PORT    A  /* Specify the digital port where the action select pin is placed to specify command/data */
#define ACTION_SELECT_PIN     2   /* Specify the pin on the digital port where the action select pin is placed to specify command/data*/

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
* \name     LCD_Manager_Init
* \brief    It initializes the SPI module, configures the action select pin to send commands, sends
*           a series of commands in order to initialize the LCD display and sets the FSM to the idle 
*           state
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void LCDManager_Init(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     LCDManager_IsBusy
* \brief    returns TRUE(1) if there is a message being send, returns FALSE(0) otherwise
* \param    void
* \return   bool
-------------------------------------------------------------------------------------------------*/
bool LCDManager_IsBusy(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     LCDManager_WriteMessage
* \brief    It buffers the message to be send, and changes the state to SET_POSITION to start
*           the transmitting process
* \param    char[],u8,u8,u8
* \return   bool
-------------------------------------------------------------------------------------------------*/
void LCDManager_WriteMessage(char[],u8,u8,u8);

/*!*-----------------------------------------------------------------------------------------------
* \name     LCDManager_PeriodicTask
* \brief    This function is divided in 3 sections (states of the FSM). The first state(IDLE) corresponds to 
*           the initial state, just waiting for a message to be send, it does nothing. The second state
*           is entered after the WriteMessage function is called, in this state is set the starting
*           position of the message to be send and the state is changed to the third and last state (WRITE CHAR)
*           in which the message is send by pieces, one character every time the function is called until
*           the message is finished, returning to the IDLE state.
*           NOTE: In the transition between SET_POSITION and WRITE_CHAR make sure you consume at least 26us in your
*           application before calling LCDManager_PeriodicTask() again, this is to ensure that the command to set
*           the position is completely processed by the LCD.
*           
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void LCDManager_PeriodicTask(void);


/*************************************************************************************************/


#endif /* LCD_MANAGER_H_ */

