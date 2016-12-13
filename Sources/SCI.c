/*! **********************************************************************************************
* 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*  
*
* @file:      SCI.c
* @author(s): Manuel Madrigal Valenzuela; Efraín Duarte López
*
* @brief (Theory of Operation)
*     Pretty straight forward. It configures the SCI hardware and implements the interruptions, on which
*     it calls the registered callback (if any)
*
**************************************************************************************************/


/*************************************************************************************************/
/*********************                 Includes                **********************/
/*************************************************************************************************/
#include "SCI.h" 

/*************************************************************************************************/
/*********************                 Defines                    **********************/
/*************************************************************************************************/
#define INIT_VALUE 0
#define BUS_CLK_scaledby100 40000  
#define ENABLE    1
#define DISABLE   0

/*************************************************************************************************/
/*********************                 Typedefs                **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************              Function Prototypes              **********************/
/*************************************************************************************************/
u16 SCI_BaudRateModuloDivisor(void);

/*************************************************************************************************/
/*********************                  Static Variables                    **********************/
/*************************************************************************************************/
static char    cTxMsg[SCI_MAX_MSG_SIZE];
static u8      u8TxSize;
static u8      u8TxIndex;
static bool    bTxIsBusy;
static FnPtr   fnRxCallback;
static char    cRxData;
/*************************************************************************************************/
/*********************              Global Variables              **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Static Constants                    **********************/
/*************************************************************************************************/


/*************************************************************************************************/
/*********************                  Global Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************              Exported Functions               **********************/
/*************************************************************************************************/

void SCI_InitTx(void)
{
   SCI_ConfigureBaudRateRegister(SCI_BaudRateModuloDivisor());
   SCI_TransmitterEnable();
}

void SCI_SendMessage(const unsigned char msg[], u8 size)
{
   u8 i;//used to traverse the transmission buffer
   
   if(size>SCI_MAX_MSG_SIZE)  //if the size of the message is bigger than the buffer, the message is reduced to the buffer size
   {
      size=SCI_MAX_MSG_SIZE;
   }

   for(i=0;i<size;i++)  //saves the message into a buffer
   {
       cTxMsg[i]=msg[i];
   }
   u8TxSize=size;

   u8TxIndex=INIT_VALUE;
   SCID=cTxMsg[u8TxIndex++];   //send first character of the message
   SCI_TransmitInterruptEnable();
   bTxIsBusy=TRUE;
   
}

bool SCI_TxIsBusy(void)
{
   return bTxIsBusy;
}


void SCI_InitRx(void)
{
   SCI_ReceiverEnable();
   SCI_ReceiverInterruptEnable();
}

void SCI_RxSetCallback(FnPtr f)
{
   if(f)
   {
      fnRxCallback=f;
   }
}


//-------------------------------------------------------------------------------------------------


/*************************************************************************************************/
/*********************               Private Functions               **********************/
/*************************************************************************************************/

/*!*-----------------------------------------------------------------------------------------------
* \name     SCI_BaudRateModuloDivisor
* \brief    It calculates the Modulo divide rate (BR) needed for the Baud Rate defined
* \param    void
* \return   u16
-------------------------------------------------------------------------------------------------*/
u16 SCI_BaudRateModuloDivisor(void)
{
   u16 BaudRate_scaled_by100=SCI_BAUD_RATE/100;     //scales the BAUD RATE
   return BUS_CLK_scaledby100/(16*BaudRate_scaled_by100);//This formula is included on the S08QG8 Manual
}

/*!*-----------------------------------------------------------------------------------------------
* \name     Tx Interruption
* \brief    It sends a new character if there are some left to be sent. Otherwise, it disables
*           the interruption and clears the busy flag
-------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vscitx void SCI_Tx_IRS()
{
   SCI_ClearFlag();
   if(u8TxIndex>=u8TxSize)
   {
      SCI_TransmitInterruptDisable();
      bTxIsBusy=FALSE;
   }
   else
   {
      SCID=cTxMsg[u8TxIndex++];//send new character
   }
}

/*!*-----------------------------------------------------------------------------------------------
* \name     Interruption
* \brief    It calls a pre-set function(if any) to do something with the received character
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vscirx void SCI_Rx_IRS()
{
   SCI_ClearFlag();
   cRxData=SCID;
   if(fnRxCallback)
   {
      (*fnRxCallback)(cRxData);
   }
}
