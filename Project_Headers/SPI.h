/*! **********************************************************************************************
 * 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores
 *
 * @file:      SPI.h
 * @author(s):    Manuel Madrigal Valenzuela; Efraín Duarte López    
 *
 * @brief (User's Manual):
 *   This is a SPI driver for the 9S08QG8 MCU. It also provides macro-like functions to
 *   reduce code footprint.
 *
 **************************************************************************************************/

#ifndef SPI_H_
#define SPI_H_


/*************************************************************************************************/
/*********************                 Includes                **********************/
/*************************************************************************************************/
#include "derivative.h" /* include peripheral declarations */
#include "types.h"

/*************************************************************************************************/
/*********************                 Defines                    **********************/
/*************************************************************************************************/
//Divisors for the SPI baud rate Prescaler (DO NOT MODIFY)
#define SPI_BR_PS_1     0  //divides by 1
#define SPI_BR_PS_2     1  //divides by 2
#define SPI_BR_PS_3     2  //divides by 3
#define SPI_BR_PS_4     3  //divides by 4
#define SPI_BR_PS_5     4  //divides by 5
#define SPI_BR_PS_6     5  //divides by 6
#define SPI_BR_PS_7     6  //divides by 7
#define SPI_BR_PS_8     7  //divides by 8

//divisors for the SPI baud rate divider (DO NOT MODIFY)
#define SPI_BR_DIV_2    0  //divides by 2
#define SPI_BR_DIV_4    1  //divides by 4
#define SPI_BR_DIV_8    2  //divides by 8
#define SPI_BR_DIV_16   3  //divides by 16
#define SPI_BR_DIV_32   4  //divides by 32
#define SPI_BR_DIV_64   5  //divides by 64
#define SPI_BR_DIV_128  6  //divides by 128
#define SPI_BR_DIV_256  7  //divides by 256

/* Driver configuration. The user should modify these values */
#define SPI_CLOCK_POL   0              //Choose Clock polarity as Active-High(0) or Active-Low(1)
#define SPI_CLOCK_PHA   0              //Choose the first edge on the clock to occur at the middle(0) or at the start(1) of the transfer         
#define SPI_SHIFT_DIR   0              //Choose to start data transfers with MSB(0)  or LSB(1)
#define SPI_BR_PS       SPI_BR_PS_1    //divisor for the SPI baud rate prescaler(used in conjunction with the divider to set the BAUDRATE)
#define SPI_BR_DIV      SPI_BR_DIV_256 //divisor for the SPI baud rate divider(used in conjunction with the prescaler to set the BAUDRATE)

/*************************************************************************************************/
/*********************                 Typedefs                **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************            Functions Like Macros              **********************/
/*************************************************************************************************/

#define SPI_SystemEnable()             SPIC1_SPE=1   //SPI System active
#define SPI_SystemDisable()            SPIC1_SPE=0   //SPI System inactive
#define SPI_SetMasterMode()            SPIC1_MSTR=1  //SPI module configured as a master SPI device
#define SPI_SetSlaveMode()             SPIC1_MSTR=0  //SPI module configured as a slave SPI device
#define SPI_SetClockPolarity(CPO)      SPIC1_CPOL=(CPO)  //0   Active-high SPI clock   (idles low)
                                                         //1   Active-low SPI clock    (idles high)

#define SPI_SetClockPhase(CPH)         SPIC1_CPHA=(CPH)  //0   First edge on the clock occurs at the middle of the first cycle of an 8-cycle data transfer
                                                         //1   First edge on the clock occurs at the start of the first cycle of an 8-cycle data transfer

#define SPI_SetShifterDirection(DIR)   SPIC1_LSBFE=(DIR) //0 SPI serial data transfers start with most significant bit
                                                         //1 SPI serial data transfers start with least significant bit

#define SPI_SetBaudRatePrescaler(PS)   SPIBR_SPPR=(PS)/*This 3-bit field selects one of eight divisors for the SPI baud rate prescaler
                                                      defined above. The input to this prescaler is the bus rate clock (BUSCLK). The output of this prescaler
                                                      drives the input of the SPI baud rate divider.*/

#define SPI_SetBaudRateDivisor(DIV)    SPIBR_SPR=(DIV)/*This 3-bit field selects one of eight divisors for the SPI baud rate divider defined
                                                      above. The input to this divider comes from the SPI baud rate prescaler. The output of this
                                                      divider is the SPI bit rate clock for master mode.*/

#define SPI_DisableMISO()              SPIC2_SPC0=1;SPIC2_BIDIROE=1  //Reverses the dedicated pin for the MISO to GPIO

#define SPI_SPRF_isSet()               (0u != (SPIS_SPRF))     /* Test if SPI Read Buffer Full flag is set */
#define SPI_SPTEF_isSet()              (0u != (SPIS_SPTEF))    /* Test if SPI Transmit Empty Flag is set */

#define SPI_ReadData()                 SPID        //Return the data read from the receive data buffer.          
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
* \name     SPI_Init
* \brief    It enables the module, configures it as the Master device, sets the clock configurations
*           and configures the Baud Rate
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void SPI_Init(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     SPI_TxIsBusy
* \brief    Returns TRUE(1) if the SPI modules is busy transmitting, otherwise returns FALSE(0)
* \param    void
* \return   bool
-------------------------------------------------------------------------------------------------*/
bool SPI_TxIsBusy(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     SPI_Init
* \brief    It places a new data on the empty shift register and starts transmitting it.
* \param    char
* \return   void
-------------------------------------------------------------------------------------------------*/
void SPI_SendData(char);

/*************************************************************************************************/
#endif /* SPI_H_ */
