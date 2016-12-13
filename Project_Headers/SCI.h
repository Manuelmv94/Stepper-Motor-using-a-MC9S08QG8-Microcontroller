/*! **********************************************************************************************
 * 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores
 *
 * @file:      SCI.h
 * @author(s):    Manuel Madrigal Valenzuela; Efraín Duarte López    
 *
 * @brief (User's Manual):
 *   This is a SCI driver for the 9S08QG8 MCU. It also provides macro-like functions to
 *   reduce code footprint.
 *
 **************************************************************************************************/

#ifndef SCI_H_
#define SCI_H_


/*************************************************************************************************/
/*********************                 Includes                **********************/
/*************************************************************************************************/
#include "derivative.h" /* include peripheral declarations */
#include "types.h"

/*************************************************************************************************/
/*********************                 Defines                    **********************/
/*************************************************************************************************/

/* Driver configuration. The user should modify these values */
#define SCI_BAUD_RATE   9600 /*Amount of bit transfers per second*/
#define SCI_MAX_MSG_SIZE    30  /*The maximum number of characters allowed to be sent and received*/

/* These should not be modified by the user */

#if ((SCI_BAUD_RATE < 9600) || (SCI_BAUD_RATE > 115200))
#error "SCI.h. SCI_BAUD_RATE  must be between 9,600 and 115,200 BPS";
#endif

/*************************************************************************************************/
/*********************                 Typedefs                **********************/
/*************************************************************************************************/
typedef void (*FnPtr)(char); /*function pointer data type that receives a char and returns nothing*/

/*************************************************************************************************/
/*********************            Functions Like Macros              **********************/
/*************************************************************************************************/

/*The next Macros are used to control various optional features of the SCI system.*/
#define SCI_EnableLoopModeSelect()        SCIC1_LOOPS=ENABLE      /*Loop mode or single-wire mode where transmitter outputs are internally connected to receiver input. RxD pin is not used by SCI.*/
#define SCI_DisableLoopModeSelect()       SCIC1_LOOPS=DISABLE     /*Normal operation — RxD and TxD use separate pins.*/
#define SCI_EnableStopsInWaitMode()       SCIC1_SCISWAI=ENABLE    /*SCI clocks freeze while CPU is in wait mode.*/
#define SCI_DisableStopsInWaitMode()      SCIC1_SCISWAI=DISABLE   /*SCI clocks continue to run in wait mode so the SCI can be the source of an interrupt that wakes up the CPU*/
#define SCI_Enable_9BIT_Mode()            SCIC1_M=ENABLE          /*Receiver and transmitter use 9-bit data characters. Start + 8 data bits (LSB first) + 9th data bit + stop.*/
#define SCI_Disable_9BIT_Mode()           SCIC1_M=DISABLE         /*Normal — start + 8 data bits (LSB first) + stop.*/
#define SCI_ParityEnable()                SCIC1_PE=ENABLE         /*Parity enabled*/
#define SCI_DisableParity()               SCIC1_PE=DISABLE        /*No hardware parity generation or checking.*/
#define SCI_SelectOddParityType()         SCIC1_PT=ENABLE         /*Odd parity means the total number of 1s in the data character, including the parity bit, is odd.*/
#define SCI_SelectEvenPaityType()         SCIC1_PT=DISABLE        /*Even parity means the total number of 1s in the data character, including the parity bit, is even.*/
#define SCI_EnableTransmitDataInversion()    SCIC3_TXINV=ENABLE      /*Setting TXINV inverts the TxD output for all cases: data bits, start and stop bits, break, and idle.*/
#define SCI_DisableTransmitDataInversion()   SCIC3_TXINV=DISABLE     /*Transmit data is not inverted*/

/*These Macros control the prescale divisor for SCI baud rate generation*/
#define SCI_ConfigureBaudRateRegister(BR)          SCIBD=BR            /*It sets the modulo divide rate (BR) for the SCI Baud Rate generator*/

/*These Macros control interruptions and enables*/
#define SCI_TransmitInterruptEnable()              SCIC2_TIE=ENABLE    /*Hardware interrupt requested when TDRE flag is activated.*/
#define SCI_TransmitInterruptDisable()             SCIC2_TIE=DISABLE   /*Hardware interrupts from TDRE disabled (use polling).*/
#define SCI_TransmissionCompleteInterruptEnable()  SCIC2_TCIE=ENABLE   /*Hardware interrupt requested when TC flag is activated.*/
#define SCI_TransmissionCompleteInterruptDisable() SCIC2_TCIE=DISABLE  /*Hardware interrupts from TC disabled (use polling).*/
#define SCI_ReceiverInterruptEnable()              SCIC2_RIE=ENABLE    /*Hardware interrupt requested when RDRF flag is activated.*/
#define SCI_ReceiverInterruptDisable()             SCIC2_RIE=DISABLE   /*Hardware interrupts from RDRF disabled (use polling).*/
#define SCI_IdleLineInterruptEnable()              SCIC2_ILIE=ENABLE   /*Hardware interrupt requested when IDLE flag is activated.*/
#define SCI_IdleLineInterruptDisable()             SCIC2_ILIE=DISABLE  /*Hardware interrupts from IDLE disabled (use polling).*/
#define SCI_TransmitterEnable()                    SCIC2_TE=ENABLE     /*Transmitter ON. When TE = 1, the SCI forces the TxD pin to act as an output for the SCI system.*/
#define SCI_TransmitterDisable()                   SCIC2_TE=DISABLE    /*Transmitter OFF. When TE is written to 0, the transmitter keeps control of the port TxD pin until any data, queued idle, or queued break character finishes transmitting before allowing the pin to revert to a general-purpose I/O pin.*/
#define SCI_ReceiverEnable()                       SCIC2_RE=ENABLE     /*Receiver ON*/
#define SCI_ReceiverDisable()                      SCIC2_RE=DISABLE    /*Receiver OFF. When the SCI receiver is off, the RxD pin reverts to being a general-purpose port I/O pin.*/
#define SCI_ReceiverWakeUpEnable()                 SCIC2_RWU=ENABLE    /*SCI receiver in standby waiting for wakeup condition.*/
#define SCI_ReceiverWakeUpDisable()                SCIC2_RWU=DISABLE   /*Normal SCI receiver operation.*/
#define SCI_SendBreakEnable()                      SCIC2_SBK=ENABLE    /*Queue break character(s) to be sent.*/
#define SCI_SendBreakDisable()                     SCIC2_SBK=DISABLE   /*Normal transmitter operation.*/
#define SCI_OverrunInterruptEnable()               SCIC3_ORIE=ENABLE   /*This bit enables the overrun flag (OR) to generate hardware interrupt requests.*/
#define SCI_OverrunInterruptDisable()              SCIC3_ORIE=DISABLE   /*OR interrupts disabled (use polling).*/
#define SCI_NoiseErrorInterruptEnable()            SCIC3_NEIE=ENABLE    /*This bit enables the noise flag (NF) to generate hardware interrupt requests.*/
#define SCI_NoiseErrorInterruptDisable()           SCIC3_NEIE=DISABLE   /*NF interrupts disabled (use polling).*/
#define SCI_FramingErrorInterruptEnable()          SCIC3_FEIE=ENABLE    /*This bit enables the framing error flag (FE) to generate hardware interrupt requests.*/
#define SCI_FramingErrorInterruptDisable()         SCIC3_FEIE=DISABLE   /*FE interrupts disabled (use polling).*/
#define SCI_ParityErrorInterruptEnable()           SCIC3_PEIE=ENABLE    /*This bit enables the parity error flag (PF) to generate hardware interrupt requests.*/
#define SCI_ParityErrorInterruptDisable()          SCIC3_PEIE=DISABLE   /*PF interrupts disabled (use polling).*/

/*These Macros allow to check the flags*/
#define SCI_TDRE_isSet()                (0u != (SCIS1_TDRE))            /* Test if Transmit Data Register Empty Flag is set */
#define SCI_TC_isSet()                  (0u != (SCIS1_TC))              /* Test if Transmission Complete Flag is set */
#define SCI_RDRF_isSet()                (0u != (SCIS1_RDRF))            /* Test if Receive Data Register Full Flag is set */
#define SCI_IDLE_isSet()                (0u != (SCIS1_IDLE))            /* Test if Idle Line Flag is set */
#define SCI_OR_isSet()                  (0u != (SCIS1_OR))              /* Test if Receiver Overrun Flag is set */
#define SCI_NF_isSet()                  (0u != (SCIS1_NF))              /* Test if Noise Flag is set */
#define SCI_FE_isSet()                  (0u != (SCIS1_FE))              /* Test if Framing Error Flag is set */
#define SCI_PF_isSet()                  (0u != (SCIS1_PF))              /* Test if Parity Error Flag is set */
#define SCI_RAF_isSet()                 (0u != (SCIS2_RAF))             /* Test if Receiver Active Flag is set */

#define SCI_ClearFlag()                   (void) SCIS1                  /*this is the first step to clear the flag, you need to write in SCID to complete the clearing process*/
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
* \name     SCI_InitTx
* \brief    Configures the Baud Rate and enables the transmission
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void SCI_InitTx(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     SCI_SendMessage
* \brief    It buffers the message to be sent, enables interruptions and transmit the first character
*           of the message. The rest is done by interruptions. A flag indicating that the tansmission
*           is busy is set.
* \param    char[],u8
* \return   void
-------------------------------------------------------------------------------------------------*/
void SCI_SendMessage(const unsigned char msg[], u8 size);

/*!*-----------------------------------------------------------------------------------------------
* \name     SCI_TxIsBusy
* \brief    Returns TRUE if the transmission is busy sending a previous message, and FALSE if the
*           transmission is free to send a new message
* \param    void
* \return   bool
-------------------------------------------------------------------------------------------------*/
bool SCI_TxIsBusy(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     SCI_InitRx
* \brief    Enables the reception of messages. It also enables the interruptions upon reception
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void SCI_InitRx(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     SCI_RxSetCallback
* \brief    Registers a function to be called whenever the Rx Interruption is rised. In the SCI_Rx ISR, 
*           this function will be called.
* \param    FnPtr (Function pointer to the callback function)
* \return   void
-------------------------------------------------------------------------------------------------*/
void SCI_RxSetCallback(FnPtr);
/*************************************************************************************************/





#endif /* SCI_H_ */
