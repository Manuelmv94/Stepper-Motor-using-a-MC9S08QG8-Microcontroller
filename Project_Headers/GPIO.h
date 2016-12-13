/*! **********************************************************************************************
 * 2014  ITESM Campus Guadalajara. Laboratorio de Microcontroladores
 *
 * @file:      GPIO.h
 * @author(s): 	Mauricio Capistrán Garza Jirash	   
 *
 * @brief (User's Manual):
 *    This is a simple GPIO driver for the 9S08QG8 MCU. It provides only macro-like functions to
 *    reduce code footprint.
 *
 **************************************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "derivative.h" /* include peripheral declarations */

/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define GPIO_DIR_IN        0   /* Used to configure the direction of the GPIO pins */
#define GPIO_DIR_OUT       1

/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************			 	 Functions Like Macros					**********************/
/*************************************************************************************************/

/* DO NOT MODIFY OR USE THESE ********************************************************************/
#define GPIO_PORT(port)           				PT##port##D                      /* Defines the port register name */
#define GPIO_PIN_DD(port, pin)     				PT##port##DD_PT##port##DD##pin   /* Defines the port-pin direction register name */
#define GPIO_PIN(port, pin)        				PT##port##D_PT##port##D##pin     /* Defines the port-pin register name */
#define GPIO_DIR(port)							   PT##port##DD					      /* Defines the port direction register */
#define PULLUP_PIN(port,pin)                 PT##port##PE_PT##port##PE##pin   /*Defines the pull-up port-pin register name*/
/*************************************************************************************************/

/* Macros to configure pin direction */
#define GPIO_CONFIG_OUT(port, pin)				GPIO_CONFIG_DIR_EXPANDED(port, pin, GPIO_DIR_OUT) /* Sets port-pin as output */
#define GPIO_CONFIG_IN(port, pin)				GPIO_CONFIG_DIR_EXPANDED(port, pin, GPIO_DIR_IN)  /* Sets port-pin as input */
#define GPIO_CONFIG_DIR_EXPANDED(port,pin,dir)  (GPIO_PIN_DD(port, pin) = dir)

#define GPIO_CONFIG_PORT_OUT(port, startPin, size)		( GPIO_DIR(port) = (0xFF >> (8-size) ) << startPin )


/* Macros to output data */
#define GPIO_SET(port, pin)						GPIO_WRITE_PIN(port, pin, 1U)    /* Write a 1 to the port-pin */
#define GPIO_CLR(port, pin)						GPIO_WRITE_PIN(port, pin, 0U)    /* Write a 0 to the port-pin */
#define GPIO_WRITE_PIN(port, pin, val)       (GPIO_PIN(port, pin) = val)      /* Write "val" to the port-pin */  
#define GPIO_WRITE_PORT(port, val)           (GPIO_PORT(port) = val)          /* Write "val" to the port-pin */  

/* Marcos to input data */
#define GPIO_READ_PORT(port)					GPIO_PORT(port)	                  /* Reads port*/
#define GPIO_READ_PIN(port, pin)				GPIO_PIN(port, pin)
#define GPIO_IS_SET(port, pin)			   (0u != GPIO_READ_PIN(port, pin))    /* Test if pin is set */
#define GPIO_IS_CLR(port, pin)				(0u == GPIO_READ_PIN(port, pin))    /* Test if pin is cleared */

/*Macros to enable pull up */
#define  PULLUP_ENABLE(port,pin)          (PULLUP_PIN(port,pin)=1U)     /*Enables the pull up of the port and pin selected*/
#define  PULLUP_DISABLE(port,pin)          (PULLUP_PIN(port,pin)=0U)    /*Disables the pull up of the port and pin selected*/

/*************************************************************************************************/
/*********************					Extern Variables					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Extern Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
#endif /* GPIO_H_ */
