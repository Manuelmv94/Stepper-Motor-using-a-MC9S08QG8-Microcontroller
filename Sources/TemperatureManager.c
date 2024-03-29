/*! **********************************************************************************************
* 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*  
*
* @file:      TemperatureManager.c
* @author(s): Manuel Madrigal Valenzuela; Efra�n Duarte L�pez
*
* @brief (Theory of Operation)
*     This driver uses the ADC driver to constantly check the signal given from a temperature sensor
*     and update certain parameters
*
**************************************************************************************************/


/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include "TemperatureManager.h"
/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define MAX_VOLTAGE_IN_mV  3300
/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Static Variables                    **********************/
/*************************************************************************************************/
static bool bOverTemperatureDetected;
static u16 u16TemperatureLimit;

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

void TemperatureManager_Init(void)
{
   ADC_Init();
   bOverTemperatureDetected=FALSE;
   u16TemperatureLimit=INITIAL_TEMPERATURE_LIMIT;
}

u16 TemperatureManager_getTemperature(void)
{
   u16 Temperature=(u16)((u32)ADC_getResultOfConversion()*MAX_VOLTAGE_IN_mV/ADC_MODE_MASK);//Translate the result of the ADC to temperature
   if(Temperature>=u16TemperatureLimit)
   {
      bOverTemperatureDetected=TRUE;
   }
   else{
      bOverTemperatureDetected=FALSE;
   }
   return Temperature;
}

bool TemperatureManager_IsOverTemperatureDetected(void)
{
   return bOverTemperatureDetected;
}

void TemperatureManager_setTemperatureLimit(u16 TempLimit)
{
   u16TemperatureLimit=TempLimit;
}
//-------------------------------------------------------------------------------------------------


/*************************************************************************************************/
/*********************				    Private Functions					**********************/
/*************************************************************************************************/

