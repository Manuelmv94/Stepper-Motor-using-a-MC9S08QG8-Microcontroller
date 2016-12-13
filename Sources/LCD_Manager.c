/*! **********************************************************************************************
* 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*  
*
* @file:      LCD_Manager.c
* @author(s): Manuel Madrigal Valenzuela; Efraín Duarte López
*
* @brief (Theory of Operation)
*    This driver uses the SPI driver to transmit data into an LCD Display.
*    The main process is done by the PeriodicTask function, which helps the transmission to be a
*    non-blocking process as a Finite State Machine(FSM). When a message is tried to be send, the FSM
*    changes from IDLE to SET_POSITION and then to WRITE_CHAR, sending a character every time 
*    the periodic task is called until the message is completely send, returning to IDLE.
*     
**************************************************************************************************/


/*************************************************************************************************/
/*********************                 Includes                **********************/
/*************************************************************************************************/
#include "LCD_Manager.h"

/*************************************************************************************************/
/*********************                 Defines                    **********************/
/*************************************************************************************************/
#define IDLE         0
#define SET_POSITION 1
#define WRITE_CHAR   2

#define SECOND_LINE_POS 0x40
#define SLCT_LINE_CMMD  0X80
/*************************************************************************************************/
/*********************                 Typedefs                **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************              Function Prototypes              **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Static Variables                    **********************/
/*************************************************************************************************/
static char cMessage[LCDMANAGER_MAX_MSG_SIZE];
static u8   u8MsgSize;
static u8   u8IndexPos;
static bool bIsBusy;
static u8   u8Column;
static u8   u8Line;
static u8   u8State;
static u8   u8Command;
/*************************************************************************************************/
/*********************              Global Variables              **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Static Constants                    **********************/
/*************************************************************************************************/

static const char initialization[]={0x39,0x39,0x78,0x55,0x6D,0x0F};
static const u8 initSize=6;
/*************************************************************************************************/
/*********************                  Global Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************              Exported Functions               **********************/
/*************************************************************************************************/

void LCDManager_Init(void)
{
   u8 i;//to be used in the loop
   SPI_Init();
   GPIO_CLR(ACTION_SELECT_PORT,ACTION_SELECT_PIN);       //Configures the action select pin to send commands
   GPIO_CONFIG_OUT(ACTION_SELECT_PORT,ACTION_SELECT_PIN);//
   for(i=0;i<initSize;i++)
   {
      do{
         asm("NOP");
      }while(SPI_TxIsBusy());
      SPI_SendData(initialization[i]); //Send the commands from the initialization array to start using the LCD display
      
   }
   bIsBusy=FALSE;
   u8State=IDLE;
}

bool LCDManager_IsBusy()
{
   return bIsBusy;
}

void LCDManager_WriteMessage(char msg[],u8 size,u8 line,u8 col)
{
   u8 i;//to be used in the loop
   if(size<LCDMANAGER_MAX_MSG_SIZE)    
   {
      u8MsgSize=size;
   }
   else//Trims the message if the size is bigger than max size configured
   {
      u8MsgSize=LCDMANAGER_MAX_MSG_SIZE;
   }
   for(i=0;i<u8MsgSize;i++)   // Saves the message to a temporary buffer
   {
      cMessage[i]=msg[i];
   }
   u8IndexPos=INIT_VALUE;  
   u8Line=line;
   u8Column=col;
   bIsBusy=TRUE;
   u8State=SET_POSITION;
}

void LCDManager_PeriodicTask()
{
   switch(u8State)
   {
      case IDLE:
         bIsBusy=FALSE;
         break;
       
      case SET_POSITION:
         if(GPIO_IS_SET(ACTION_SELECT_PORT,ACTION_SELECT_PIN)) 
         {
            GPIO_CLR(ACTION_SELECT_PORT,ACTION_SELECT_PIN);//Configures the action select pin to send a command
         }
         if(!SPI_TxIsBusy())
         {
            u8Command=((u8Line-1)*(SECOND_LINE_POS))+(u8Column-1)+SLCT_LINE_CMMD;//prepares the command indicating the line and column of the lcd display where the message is going to be placed
            SPI_SendData(u8Command);//sends the command to set the position
            u8IndexPos=INIT_VALUE;
            u8State=WRITE_CHAR;
         }
            
         break;
      case  WRITE_CHAR:
         
         if(!SPI_TxIsBusy())
         {
            if(GPIO_IS_CLR(ACTION_SELECT_PORT,ACTION_SELECT_PIN))
            {
               GPIO_SET(ACTION_SELECT_PORT,ACTION_SELECT_PIN);//Configures the action select pin to send data
            }
            SPI_SendData(cMessage[u8IndexPos++]);//sends the following character of the message
            if(u8IndexPos>=u8MsgSize)
            {
               u8State=IDLE;
            }
         }
         break;
      default:
         while(1)
         {
            //The microcontroller is lost
         }         
   }
}


//-------------------------------------------------------------------------------------------------


/*************************************************************************************************/
/*********************               Private Functions               **********************/
/*************************************************************************************************/
