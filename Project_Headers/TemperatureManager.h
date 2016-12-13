/*! **********************************************************************************************
 * 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores
 *
 * @file:      TemperatureManager.h
 * @author(s):    Manuel Madrigal Valenzuela; Efraín Duarte López    
 *
 * @brief (User's Manual):
 *    This manager is used to consult the temperature given by the sensor,
 *    This manager also can control the temperature limit.
 *    
 *    This manager has been tested on the following NXP MCUs:
 *     + MC9S08QG8
 **************************************************************************************************/

#ifndef TEMPERATUREMANAGER_H_
#define TEMPERATUREMANAGER_H_



/*************************************************************************************************/
/*********************                 Includes                **********************/
/*************************************************************************************************/
#include "derivative.h" /* include peripheral declarations */
#include "types.h"
#include "ADC.h"

/*************************************************************************************************/
/*********************                 Defines                    **********************/
/*************************************************************************************************/

/* Driver configuration. The user should modify these values */
#define INITIAL_TEMPERATURE_LIMIT   1000   //The limit should be in Celsius and scaled by 10. For example:
                                           //124.5 C would be 1245


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
* \name     TemperatureManager_Init
* \brief    Starts the ADC and sets an INITIAL_TEMPERATURE_LIMIT
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void TemperatureManager_Init(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     TemperatureManager_getTemperature
* \brief    It takes the result from the ADC, translates it to temperature, sets a flag
*           in case that the measurement is over the temperature limit and returns the temperature
* \param    void
* \return   u16
-------------------------------------------------------------------------------------------------*/
u16 TemperatureManager_getTemperature(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     TemperatureManager_IsOverTemperatureDetected
* \brief    Returns TRUE in case that the temperatures is over the limit, returns false otherwise
* \param    void
* \return   bool
-------------------------------------------------------------------------------------------------*/
bool TemperatureManager_IsOverTemperatureDetected(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     TemperatureManager_setTemperatureLimit
* \brief    Receives and set the new temperatures scaled by 10. This is done for a better resolution.
*           For example:
*           To set a temperature limit of 102.5 C, the parameter should be 1025
* \param    u16
* \return   void
-------------------------------------------------------------------------------------------------*/
void TemperatureManager_setTemperatureLimit(u16);

/*************************************************************************************************/


#endif /* TEMPERATUREMANAGER_H_ */
