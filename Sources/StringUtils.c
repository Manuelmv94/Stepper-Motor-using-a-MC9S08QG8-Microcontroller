/*! **********************************************************************************************
* 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*  
*
* @file:      StringUtils.c
* @author(s): Manuel Madrigal Valenzuela; Efraín Duarte López
*
* @brief (Theory of Operation)
*     The present file allows the user to treat arrays of chars as if they were strings. It contains
*     comparisons of strings done char by char and translations from Number to String and String
*     to number
*
**************************************************************************************************/


/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include "StringUtils.h"

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define ASCII_OFFSET 0x30
#define LOWEST_DECIMAL_NUMBER 0
#define HIGHES_DECIMAL_NUMBER 9
#define INIT_VALUE   0
#define DECIMAL_SHIFT_LEFT 10
/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/


/*************************************************************************************************/
/*********************                  Static Variables                    **********************/
/*************************************************************************************************/
static  bool StringsEqual;
static u8 tempNum;
static u16 accumulatedValue;
static  bool invalidString;

static u8 index;//used to traverse the strings

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

bool StringUtils_StringCompare(const unsigned char string1[],const unsigned char string2[], u8 stringSize)
{
   StringsEqual=TRUE;
   index=INIT_VALUE;
   
   while(StringsEqual==TRUE && index<stringSize)
   {
      if(string1[index]!=string2[index])
      {
         StringsEqual=FALSE;
      }
      index++;
   }
   
   return StringsEqual;
}

bool StringUtils_Str2Num(char str[], u8 strSize, u8 decimal, u16* num)
{  
   accumulatedValue = INIT_VALUE;
   invalidString = FALSE;
   index=INIT_VALUE;
   
   while (invalidString==FALSE && index<strSize)
   {
      if((index == (strSize-decimal-1)) && (decimal!=D_NULL) )//If the index traversing the string is at the decimal point position
      {
         if(str[index]=='.')
         {
            index++;
         }
         else{
            invalidString = TRUE;
         }
      }

      tempNum = str[index] - ASCII_OFFSET;//translate the ASCII representation of the number to the actual number
      if (tempNum < LOWEST_DECIMAL_NUMBER || tempNum >HIGHES_DECIMAL_NUMBER)   //check for invalid chars
      {
         invalidString = TRUE;//the translated char was not a number
      }
      else
      {
         accumulatedValue *= DECIMAL_SHIFT_LEFT;       //Shift the accumulated value to the left in order to make the units into tens, the tens into hundreds, the hundreds into thousands, and so on
         accumulatedValue += tempNum;  //fit the units
      }

      index++;
   }
   
   if (!invalidString)
   {
      *num = accumulatedValue;
   }
   
   return !invalidString; 
}

void StringUtils_Num2Str(u16 num, u8 strSize, u8 decimal, char string[])
{  
  accumulatedValue=num;

  
  for(index=strSize;index>INIT_VALUE;index--)
  {
     if((strSize-index)==decimal){
        string[index-1]='.';        //place the decimal point at the desired spot
        index--;        
     }
     
    string[index-1]=accumulatedValue%DECIMAL_SHIFT_LEFT +ASCII_OFFSET;//Translate the rightmost number into its character representation
    accumulatedValue/=DECIMAL_SHIFT_LEFT;//Moves from the rightmost number to the consecutive one at the left
  }
}

void StringUtils_StringCopy(unsigned char fromString[],unsigned char toString[], u8 stringSize)
{
   u8 i;
   for(i=0;i<stringSize;i++)
   {
      toString[i]=fromString[i];
   }
   
}

//-------------------------------------------------------------------------------------------------


/*************************************************************************************************/
/*********************				    Private Functions					**********************/
/*************************************************************************************************/

