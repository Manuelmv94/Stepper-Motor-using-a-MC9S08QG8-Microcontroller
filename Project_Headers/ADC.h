/*! **********************************************************************************************
 * 2016 ITESM Campus Guadalajara. Laboratorio de Microcontroladores
 *
 * @file:      ADC.h
 * @author(s):    Manuel Madrigal Valenzuela; Efraín Duarte López     
 *
 * @brief (User's Manual):
 *    This is a simple ADC driver for the 9S08QG8 MCU. It provides only macro-like functions to
 *    reduce code footprint.
 *
 **************************************************************************************************/

#ifndef ADC_H_
#define ADC_H_


#include "derivative.h" /* include peripheral declarations */

/*************************************************************************************************/
/*********************                 Includes                **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                 Defines                    **********************/
/*************************************************************************************************/

/* Driver configuration. The user should modify these values */
#define ADC_RESOLUTION MODE_10BIT  /*choose resolution between MODE_10BIT, MODE_8BIT*/
#define ADC_CHANNEL  3              //Selects the channel and pin to be used



/* These should not be modified by the user */
#define DISABLE        0   
#define ENABLE         1

#define ADC_HARDWARE_TRIGGER_SELECT        1   /*To be used within the ADC_ConversionTriggerSelect(sel) Macro*/
#define ADC_SOFTWARE_TRIGGER_SELECT        0   /*To be used within the ADC_ConversionTriggerSelect(sel) Macro*/

#define DIVIDED_BY_1    0U /*To be used within the ADC_ClockDivideSelect(clk) Macro*/
#define DIVIDED_BY_2    1U /*To be used within the ADC_ClockDivideSelect(clk) Macro*/
#define DIVIDED_BY_4    2U /*To be used within the ADC_ClockDivideSelect(clk) Macro*/
#define DIVIDED_BY_8    3U /*To be used within the ADC_ClockDivideSelect(clk) Macro*/

#define MODE_8BIT       0U /*To be used within the ADC_ConversionModeSelection(mode) Macro*/
#define MODE_10BIT      2U /*To be used within the ADC_ConversionModeSelection(mode) Macro*/

#define BUSCLK         0U  /*To be used within the ADC_InputClockSelect(clk) Macro*///BUS CLOCK
#define BUSCLK_DIV2    1U  /*To be used within the ADC_InputClockSelect(clk) Macro*///BUS CLOCK divided by 2
#define ALTCLK         2U  /*To be used within the ADC_InputClockSelect(clk) Macro*///ALTERNATE CLOCK
#define ADACK          3U  /*To be used within the ADC_InputClockSelect(clk) Macro*///ASYNCHRONOUS CLOCK

#if (ADC_RESOLUTION==MODE_10BIT)
#define ADC_MODE_MASK    0x03FF
#elif (ADC_RESOLUTION==MODE_8BIT)
#define ADC_MODE_MASK    0x00FF
#else
#error "ADC.h. ADC_RESOLUTION not supported";
#endif

#if (ADC_CHANNEL > 7)
#error "ACD.h. ADC_CHANNEL range from 0 to 7 in this Microcontroller";
#endif

/*************************************************************************************************/
/*********************                 Typedefs                **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************            Functions Like Macros              **********************/
/*************************************************************************************************/

/* DO NOT MODIFY OR USE THESE ********************************************************************/
#define ADCv1(pin)    APCTL1_ADPC##pin       /*Defines the bit name of the register for channels 0 to 7*/
#define ADCv2(pin)    APCTL2_ADPC##pin       /*Defines the bit name of the register for channels 8 to 15*/
#define ADCv3(pin)    APCTL3_ADPC##pin       /*Defines the bit name of the register for channels 16 to 23*/
/*************************************************************************************************/

/* Macros to configure ADC Status and Control Register 1 */
#define ADC_EnableInterrupts()               ADCSC1_AIEN=ENABLE;  /*Used to enable Conversion Complete Interrupts*/
#define ADC_DisableInterrupts()              ADCSC1_AIEN=DISABLE; /*Used to disable Conversion Complete Interrupts*/
#define ADC_EnableContinuousConversion()     ADCSC1_ADCO=ENABLE;  /*Continuous conversions initiated following a write to ADCSC1 when software triggered operation is selected. Continuous conversions are initiated by an ADHWT event when hardware triggered operation is selected.*/
#define ADC_DisableContinuousConversion()    ADCSC1_ADCO=DISABLE; /*One conversion following a write to the ADCSC1 when software triggered operation is selected, or one conversion following assertion of ADHWT when hardware triggered operation is selected.*/
#define ADC_SelectChannel(ch)                ADCSC1_ADCH=ch;      /*The ADCH bits form a 5-bit field which is used to select one of the input channels*/

/* Macros to configure ADC Status and Control Register 2 */
#define ADC_ConversionTriggerSelect(sel)           ADCSC2_ADTRG=sel;     /*Used to select between Hardware trigger (ADC_HARDWARE_TRIGGER_SELECT) and Software Trigger(ADC_SOFTWARE_TRIGGER_SELECT) as the start of the conversion*/
#define ADC_CompareFunctionEnable()                ADCSC2_ACFE=ENABLE;   /*Used to enable the compare function (Compares the read value with a predefined value)*/
#define ADC_CompareFunctionDisable()               ADCSC2_ACFE=DISABLE;  /*Used to disable the compare function*/
#define ADC_CompareFunctionGreaterThanDisable()    ADCSC2_ACFGT=DISABLE; //Compare triggers when input is less than compare level
#define ADC_CompareFunctionGreaterThanEnable()     ADCSC2_ACFGT=ENABLE;  //Compare triggers when input is greater than or equal to compare level

/* Macros to configure ADC Compare Value Register */
#define ADC_SelectValueToCompare(val)              ADCCV=val;        /*This register holds the value selected to compare*/

/* Macros to configure ADC Configuration Register */
#define ADC_LowPowerConfiguration(en)              ADCCFG_ADLPC=en;           /*controls the speed and power configuration of the successive approximation converter.*/
#define ADC_ClockDivideSelect(clk)                 ADCCFG_ADIV=clk;           /*select the divide ratio used by the ADC to generate the internal clock ADCK.Select between: DIVIDED_BY_1 or DIVIDED_BY_2 DIVIDED_BY_4 or DIVIDED_BY_8*/
#define ADC_LongSampleTimeConfiguration()          ADCCFG_ADLSMP=ENABLE;      /*ADLSMP selects a long(U1) sample time.*/
#define ADC_ShortSampleTimeConfiguration()         ADCCFG_ADLSMP=DISABLE;     /*ADLSMP selects a short(U0) sample time.*/
#define ADC_ConversionModeSelection(mode)          ADCCFG_MODE=mode;          /*MODE bits are used to select between 10-bit (MODE_10BIT) or 8-bit (MODE_8BIT) operation*/
#define ADC_InputClockSelect(clk)                  ADCCFG_ADICLK=clk;         /*select the input clock source to generate the internal clock ADCK. Choose between: BUSCLK, BUSCLK_DIV2, ALTCLK, or ADACK*/

/* Macros to configure ADC PIN Control */
#define ADC_EnablePinForADCv1(pin)                   ADCv1(pin)=ENABLE   /*is used to control the pins associated with channels 0–7 of the ADC module.*/
#define ADC_EnablePinForADCv2(pin)                   ADCv2(pin)=ENABLE   /*is used to control the pins associated with channels 8–15 of the ADC module.*/
#define ADC_EnablePinForADCv3(pin)                   ADCv3(pin)=ENABLE   /*is used to control the pins associated with channels 16–23 of the ADC module.*/

/* Macros to get result */
#define ADC_getResultOfConversion()                    ADCR     /*Used to get the register value of the conversion*/


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
* \name     ADC_Init
* \brief    Used to initialize one channel of the ADC driver in Continuous Conversion mode with
*           the parameters defined above
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void ADC_Init(void);


/*************************************************************************************************/



#endif /* ADC_H_ */
