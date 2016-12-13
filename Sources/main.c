/*! **********************************************************************************************
* 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*  
*
* @file:      main.c
* @author(s): Manuel Madrigal Valenzuela; Efraín Duarte López
*
* @brief (Theory of Operation)
*     application that controls a stepper motor to operate in clockwise or counter clockwise mode at 
*     different speeds and configurable with a serial interface.
*     
*      - The number and the location of the motor pins are defined in StepManager.h
*      - The configuration of the timer operation is defined on TimersManager.h
*      - The reception and management of the temperature sensor is done by TemperatureManager.h
*      - The management of receiving and transmitting messages is done by the MessageManager.h
*           - The configuration that determines the operation of the motor is saved in PowerManager.h
*           - The information that determines the motor direction is saved in ModeManager.h
*           - The configuration of the intervals of time between steps is saved in SpeedManager.h
*      
**************************************************************************************************/

/*************************************************************************************************/
/*********************                 Includes                **********************/
/*************************************************************************************************/
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MessageManager.h"
#include "StringUtils.h"
#include "ModeManager.h"
#include "PowerManager.h"
#include "SpeedManager.h"
#include "StepManager.h"
#include "TemperatureManager.h"
#include "TimersManager.h"
#include "LCD_Manager.h"
#include "types.h"
/*************************************************************************************************/
/*********************                 Defines                    **********************/
/*************************************************************************************************/
#define TEMPERATURE_REPORT_DELAY_IN_US 10000000
#define DEGREES_RESOLUTION_BY_100   375
#define SCALE_BY_100 100
/*************************************************************************************************/
/*********************                 Typedefs                **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************              Function Prototypes              **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************              Global Variables              **********************/
/*************************************************************************************************/
u8 u8MessageSize;
unsigned char cMainMessage[MESSAGE_MANAGER_MAX_MSG_SIZE];
unsigned char cTemperatureReport[]={"\r\nTemperature:    .  C\r\n"};


static bool bMessageSucces;    //Set in case that the received message matches one of the options
static bool bMessageFail;      //Set in case that the received message does not match any of the options
static bool  bOverTempMsgSent; //Set if the Over Temperature message has been sent. It does not get clear until the temperatures gets under the limit

static u16 tempspeed;    //This variable holds the speed of the motor in RPS before being passed to the SpeedManager
static u16 templimit;    //This variable holds the temperature limit before being passed to the TemperatureManager

static u8 motorTimerID;
static u8 temperatureTimerID;

static u16 degrees_to_steps;   //Holds how many degrees are said to rotate the stepper
static u32 u32StepsLeft;       //Holds the steps left to accomplish the degrees indicated by degrees_to_steps

static u8 index;

unsigned char *cLCDMessage1={"D:CW "};
unsigned char cLCDMessage2[]={'T',':',' ',' ',' ','.',' ',0xDF,'C'};
unsigned char cLCDMessage3[]={"S:00.2RPS"};
static bool bLCDMessage1Success;    //Set in case that the received message matches one of the options
static bool bLCDMessage2Success;      //Set in case that the received message does not match any of the options
static bool bLCDMessage3Success;    //Set in case that the received message matches one of the options

/*************************************************************************************************/
/*********************                  Static Constants                    **********************/
/*************************************************************************************************/
static const unsigned char kMotorMsg[]={"MOTOR:"};
static const u8 kMotorMsgSize=6;
static const unsigned char kMotorMsgON[]={"ON\r"};
static const u8 kMotorMsgONSize=3;
static const unsigned char kMotorMsgOFF[]={"OFF\r:"};
static const u8 kMotorMsgOFFSize=4;

static const unsigned char kDirMsg[]={"DIR:"};
static const u8 kDirMsgSize=4;
static const unsigned char kDirMsgCW[]={"CW\r"};
static const u8 kDirMsgCWSize=3;
static const unsigned char kDirMsgCCW[]={"CCW\r"};
static const u8 kDirMsgCCWSize=4;

static const unsigned char kRPSMsg[]={"RPS:"};
static const u8 kRPSMsgSize=4;
static const u8 kRPSValueMsgSize=5;
static const u8 kRPSNumOfDecimals=1;
static const u8 kRPSEndOfMsg=9;

static const unsigned char kTempLimitMsg[]={"TEMP-LIMIT:"};
static const u8 kTempLimitMsgSize=11;
static const u8 kTempLimitValueMsgSize=5;
static const u8 kTempLimitNumOfDecimals=1;
static const u8 kTempLimitEndOfMsg=16;
static const u8 kTempReportStart=15;
static const u8 kTempReportMsgSize=24;

static const unsigned char kStepMsg[]={"STEP-CW:"};
static const u8 kStepMsgSize=8;
static const u8 kStepValueMsgSize=3;
static const u8 kStepNumOfDecimals=0;
static const u8 kStepEndOfMsg=11;

static const unsigned char kDONEMsg[]={"\r\nDONE\r\n"};
static const u8 kDONEMsgSize=8;

static const unsigned char kENTERMsg[]={"\r\n"};
static const u8 kENTERMsgSize=2;

static const unsigned char kOvTempMsg[]={"\r\nOver Temperature detected\r\n"};
static const u8 kOvTempMsgSize=29;

static const u8 LCDSpeed_fromIndex=5;
static const u8 LCDSpeed_toIndex=2;
static const u8 LCDSpeed_size=4;

static const u8 LCDTemp_fromIndex=15;
static const u8 LCDTemp_toIndex=2;
static const u8 LCDTemp_size=5;

static const u8 LCDMessage1size=5;
static const u8 LCDMessage1line=1;
static const u8 LCDMessage1col=1;

static const u8 LCDMessage2size=9;
static const u8 LCDMessage2line=1;
static const u8 LCDMessage2col=8;

static const u8 LCDMessage3size=9;
static const u8 LCDMessage3line=2;
static const u8 LCDMessage3col=1;
/*************************************************************************************************/
/*********************                  Global Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  MAIN                   **********************/
/*************************************************************************************************/
void main(void) {
  EnableInterrupts;
  
  //Initialize drivers
  StepManager_Init();
  LCDManager_Init();
  MessageManager_Init();
  PowerManager_Init();
  ModeManager_Init();
  SpeedManager_Init();
  TemperatureManager_Init();
  TimersMngr_Init();
  
  //Initialize variables
  bMessageSucces=FALSE;
  bMessageFail=FALSE;
  bOverTempMsgSent=FALSE;
  bLCDMessage1Success=TRUE;
  bLCDMessage2Success=TRUE;
  bLCDMessage3Success=TRUE;
  degrees_to_steps=INIT_VALUE;
  u32StepsLeft=INIT_VALUE;
  
  //Create and start the timers
  motorTimerID=TimersMngr_CreateTimer(D_NULL);
  temperatureTimerID=TimersMngr_CreateTimer(D_NULL);
  TimersMngr_StartTimer(temperatureTimerID,TEMPERATURE_REPORT_DELAY_IN_US);
  TimersMngr_StartTimer(motorTimerID,SpeedManager_getSpeedDelay());
    
  for(;;) {
     
     if(TimersMngr_TimerHasElapsed(motorTimerID)){
        if(!TemperatureManager_IsOverTemperatureDetected())
        {
           bOverTempMsgSent=FALSE;  //Clear the flag in case it was set to send a message again in case of over temperature
           
           if(PowerManager_IsMotorON() || (u32StepsLeft!=INIT_VALUE))
           {
              TimersMngr_StartTimer(motorTimerID,SpeedManager_getSpeedDelay());
              if(u32StepsLeft>INIT_VALUE)
              {
                 u32StepsLeft--;
              }
              
              if( !ModeManager_IsClockWise())
              {
                 StepManager_RotateCounterClockWise();               //Go to the next step on the Counter clockwise sequence
              }
              else
              {
                 StepManager_RotateClockWise();              //Go to the next step on the Clockwise sequence
              }
           }
        }
     }
     
     if(MessageManager_IsMessageReady())  //Message ready to be read
     {
        //Clean the buffer receiving the messages------------------------------------
       
        for(index=INIT_VALUE;index<MESSAGE_MANAGER_MAX_MSG_SIZE;index++)
        {
           cMainMessage[index]=INIT_VALUE;
        }
        //---------------------------------------------------------------------------
        
        MessageManager_getMessage(cMainMessage,&u8MessageSize);//Buffer the received message into cMainMessage and save the size into u8MessageSize
        
        if(StringUtils_StringCompare(cMainMessage,kMotorMsg,kMotorMsgSize))//Compare the message received against kMotorMsg
        {
           if(StringUtils_StringCompare(&cMainMessage[kMotorMsgSize],kMotorMsgON,kMotorMsgONSize))
           {
              PowerManager_setMotor(POWER_MANAGER_ON);//Turn the stepper motor ON
              bMessageSucces=TRUE;
           }
           else if(StringUtils_StringCompare(&cMainMessage[kMotorMsgSize],kMotorMsgOFF,kMotorMsgOFFSize))
           {
              PowerManager_setMotor(POWER_MANAGER_OFF);//Turn the stepper motor OFF
              u32StepsLeft=INIT_VALUE;
              bMessageSucces=TRUE;
           }
           else
           {
              bMessageFail=TRUE;
           }
        }
        else if(StringUtils_StringCompare(cMainMessage,kDirMsg,kDirMsgSize))//Compare the message received against kMDirMsg
        {
           if(StringUtils_StringCompare(&cMainMessage[kDirMsgSize],kDirMsgCW,kDirMsgCWSize))
           { 
              ModeManager_SetDirection(MODE_MANAGER_CW); //Set the motor into ClockWise Direction
              cLCDMessage1="D:CW ";
              bLCDMessage1Success=TRUE;
              bMessageSucces=TRUE;
           }
           else if(StringUtils_StringCompare(&cMainMessage[kDirMsgSize],kDirMsgCCW,kDirMsgCCWSize))
           {
              ModeManager_SetDirection(MODE_MANAGER_CCW); //Set the motor into Counter-Clockwise direction
              cLCDMessage1="D:CCW";
              bLCDMessage1Success=TRUE;
              bMessageSucces=TRUE;
           }
           else
           {
              bMessageFail=TRUE;
           }
        }
        else if(StringUtils_StringCompare(cMainMessage,kRPSMsg,kRPSMsgSize))//Compare the message received against kRPSMsg
        {
           if(StringUtils_Str2Num(&cMainMessage[kRPSMsgSize],kRPSValueMsgSize,kRPSNumOfDecimals,&tempspeed) && (tempspeed!=INIT_VALUE) && (cMainMessage[kRPSEndOfMsg]==ASCII_ENTER_CODE))
           {
              StringUtils_StringCopy(&cMainMessage[LCDSpeed_fromIndex],&cLCDMessage3[LCDSpeed_toIndex],LCDSpeed_size);
              bLCDMessage3Success=TRUE;
              SpeedManager_setSpeed(tempspeed);
              bMessageSucces=TRUE;
           }
           else
           {
              bMessageFail=TRUE;
           }
        }
        else if(StringUtils_StringCompare(cMainMessage,kTempLimitMsg,kTempLimitMsgSize) && (cMainMessage[kTempLimitEndOfMsg]==ASCII_ENTER_CODE))//Compare the message received against kTempLimitMsg
        {
           if(StringUtils_Str2Num(&cMainMessage[kTempLimitMsgSize],kTempLimitValueMsgSize,kTempLimitNumOfDecimals,&templimit))
           {
              TemperatureManager_setTemperatureLimit(templimit);
              bMessageSucces=TRUE;
           }
           else
           {
              bMessageFail=TRUE;
           }
        }
        else if(StringUtils_StringCompare(cMainMessage,kStepMsg,kStepMsgSize) && (cMainMessage[kStepEndOfMsg]==ASCII_ENTER_CODE))//Compare the message received against kStepMsg
        {
           if(StringUtils_Str2Num(&cMainMessage[kStepMsgSize],kStepValueMsgSize,kStepNumOfDecimals,&degrees_to_steps))
           {
              u32StepsLeft+=((u32)degrees_to_steps*SCALE_BY_100)/DEGREES_RESOLUTION_BY_100;//Set the number of motor steps needed to accomplish the desired degrees rotation
              bMessageSucces=TRUE;
           }
           else
           {
              bMessageFail=TRUE;
           }
        }
        
        else
        {
           bMessageFail=TRUE;
        }
     }
     
     if(!MessageManager_TxIsBusy())
     {
        if(bMessageSucces)
        {
           MessageManager_SendMessage(kDONEMsg,kDONEMsgSize);
           bMessageSucces=FALSE;
        }
        else if(bMessageFail)
        {
           MessageManager_SendMessage(kENTERMsg,kENTERMsgSize);
           bMessageFail=FALSE;
        }
        else if(TemperatureManager_IsOverTemperatureDetected() && !bOverTempMsgSent)
        {
           MessageManager_SendMessage(kOvTempMsg,kOvTempMsgSize);
           bOverTempMsgSent=TRUE;
        }
        else if(TimersMngr_TimerHasElapsed(temperatureTimerID))
        {
           TimersMngr_StartTimer(temperatureTimerID,TEMPERATURE_REPORT_DELAY_IN_US);
           StringUtils_Num2Str(TemperatureManager_getTemperature(),kTempLimitValueMsgSize,kTempLimitNumOfDecimals,&cTemperatureReport[kTempReportStart]);
           MessageManager_SendMessage(cTemperatureReport,kTempReportMsgSize);
           StringUtils_StringCopy(&cTemperatureReport[LCDTemp_fromIndex],&cLCDMessage2[LCDSpeed_toIndex],LCDTemp_size);
           bLCDMessage2Success=TRUE;
        }
     }
     
     if(!LCDManager_IsBusy())
     {
        if(bLCDMessage1Success)
        {
           LCDManager_WriteMessage(cLCDMessage1,LCDMessage1size,LCDMessage1line,LCDMessage1col);
           bLCDMessage1Success=FALSE;
        }
        else if(bLCDMessage2Success)
        {
            LCDManager_WriteMessage(cLCDMessage2,LCDMessage2size,LCDMessage2line,LCDMessage2col);
            bLCDMessage2Success=FALSE;
        }
        else if(bLCDMessage3Success)
        {
            LCDManager_WriteMessage(cLCDMessage3,LCDMessage3size,LCDMessage3line,LCDMessage3col);
            bLCDMessage3Success=FALSE;
        }
       
     }
     
     (void)TemperatureManager_getTemperature();//Gets the temperature and sets a flag in case of over temperature detected
     TimersMngr_PeriodicTask();//Refresh timers
     LCDManager_PeriodicTask();
     
    __RESET_WATCHDOG(); /* feeds the dog */
  } /* loop forever */
  
}
/*************************************************************************************************/
/*********************               Private Functions               **********************/
/*************************************************************************************************/

