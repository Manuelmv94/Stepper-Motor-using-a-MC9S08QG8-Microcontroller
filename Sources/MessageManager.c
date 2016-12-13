/*! **********************************************************************************************
* 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*  
*
* @file:      MessageManager.c
* @author(s): Manuel Madrigal Valenzuela; Efraín Duarte López
*
* @brief (Theory of Operation)
*     This driver uses the SCI driver to receive and transmit data through the serial port.
*     The receiving part is done by the MessageManager_buildMessage function, which is called
*     from an interruption of the SCI, buffering the message in a bi-dimensional array.
*     When the message is ready, it is hold by the cMessage char array.
*     The transmitting part is done by just passing the parameters to the SCI driver.
*     
**************************************************************************************************/


/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include "MessageManager.h"

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define INIT_VALUE   0
#define FIRST_BUFFER 0

/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/
void MessageManager_reConstructMessage(void);
void MessageManager_cleanBuffers(void);

/*************************************************************************************************/
/*********************                  Static Variables                    **********************/
/*************************************************************************************************/
static char cRxMsg[2][MESSAGE_MANAGER_MAX_MSG_SIZE];//This doubled buffer holds the message while already receiving it
static u8   u8RxIndex;//Contains the index of the next position on the selected buffer to save the received character 
static u8   u8BufferSelect;
static bool bIsMsgReady;


static char cMessage[MESSAGE_MANAGER_MAX_MSG_SIZE];//This array holds the final message, ready to be read
static u8 u8MessageSize;

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

void MessageManager_Init(void)
{
   SCI_InitTx();
   SCI_InitRx();
   SCI_RxSetCallback(&MessageManager_buildMessage);//Sets the function to be called when an interruption of the SCI reception is rised
   u8RxIndex=INIT_VALUE;
   u8BufferSelect=INIT_VALUE;
   u8MessageSize=INIT_VALUE;
   bIsMsgReady=FALSE;
}

void MessageManager_buildMessage(char cReceivedChar)
{
   if(cReceivedChar != ASCII_ENTER_CODE)
   {
      if(u8MessageSize<SCI_MAX_MSG_SIZE-1)//The actual message should be a character less than the SCI_MAX_MSG_SIZE to keep space for the ASCII_ENTER_CODE
      {
         if(u8BufferSelect==FIRST_BUFFER)
         {
            cRxMsg[u8BufferSelect++][u8RxIndex]=cReceivedChar; //Saves the character to the first buffer
            u8MessageSize++;
         }
         else
         {
            cRxMsg[u8BufferSelect--][u8RxIndex++]=cReceivedChar;//Saves the character to the second buffer
            u8MessageSize++;
         }
      }//If the received message overflows the array dedicated to receive messages, the message manager starts ignoring the following characters
   }
   else
   {
      cRxMsg[u8BufferSelect][u8RxIndex]=ASCII_ENTER_CODE;
      u8MessageSize++;
      MessageManager_reConstructMessage();
      bIsMsgReady=TRUE;
   }
}

bool MessageManager_IsMessageReady(void)
{
   return bIsMsgReady;
}

void MessageManager_getMessage(char msg[], u8* size)
{
   u8 i;//used to traverse the message array
   for(i=0;i<u8MessageSize;i++)
   {
      msg[i]=cMessage[i];
   }
   
   *size=u8MessageSize;
   
   bIsMsgReady=FALSE;
   MessageManager_cleanBuffers();
}

void MessageManager_SendMessage(const unsigned char msg[], u8 size)
{
   SCI_SendMessage(msg,size);
}

bool MessageManager_TxIsBusy(void)
{
   return SCI_TxIsBusy();
}





//-------------------------------------------------------------------------------------------------


/*************************************************************************************************/
/*********************				    Private Functions					**********************/
/*************************************************************************************************/
/*!*-----------------------------------------------------------------------------------------------
* \name     MessageManager_reConstructMessage
* \brief    Copies and orders character by character the message holding in the temporary buffers
*           to the final buffer
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void MessageManager_reConstructMessage(void)
{
   u8 i; //used to traverse the Message array
      
   u8RxIndex=INIT_VALUE;
   u8BufferSelect=FIRST_BUFFER;
   
   for(i=0;i<u8MessageSize;i++)
   {
      cMessage[i]=cRxMsg[u8BufferSelect][u8RxIndex];
      if(u8BufferSelect==FIRST_BUFFER){
         u8BufferSelect++;
      }
      else
      {
         u8BufferSelect=FIRST_BUFFER;
         u8RxIndex++;
      }
   }  
}

/*!*-----------------------------------------------------------------------------------------------
* \name     MessageManager_cleanBuffers
* \brief    It cleans the final buffer and set it ready to receive the next message. It also takes
*           the variables used to traverse the buffers to their initial value.
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void MessageManager_cleanBuffers(void)
{
   for(u8RxIndex=0;u8RxIndex<u8MessageSize;u8RxIndex++)
   {
      cMessage[u8RxIndex]=INIT_VALUE;
   }
   u8RxIndex=INIT_VALUE;
   u8BufferSelect=INIT_VALUE;
   u8MessageSize=INIT_VALUE;
}
