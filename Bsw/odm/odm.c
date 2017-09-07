/**
  ******************************************************************************
  * @file    odm.c
  * @author  Kittanadon Keawratchakit
  * @version V2.0.1
  * @date    30-NOV-2016
  * @brief   This file is
	*            
  *          
  * @copy 	  ktw@gpv-asia.co.th	 	
	* @customer   
	*				
	* @target TM4C1294xx ARM Cortex - M4 
	*
  * Copyright (c) 2016 GPV Asia CO,Ltd. (THAILAND R&D Design Center)
	* All rights reserved.
**/

/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "Platform.h"   
#include "odm/odm.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
 
/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/


/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
 uint8_t  uC_Enable = false;
 uint8_t  uC_MEnable = false;
 uint8_t  statusBits_Tacho = 0,statusBits_Tacho_Old = 0;
 uint16_t uiOdminter_PinNumber = 0;
 uint32_t uiSpeedCnt1 = 0,uiSpeedCntprv = 0,uiStorkeCnt = 0;
 uint32_t uiSpeed = 0;
 static uint8_t en = 1;
/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/

 
/**************************
** @brief 
** @param
** @retval
****************************/
void odm_init(uint16_t NumPin)
{ 

//	  MAP_GPIOIntTypeSet(GPIO_PORTQ_BASE, GPIO_INT_PIN_3, GPIO_RISING_EDGE);
//		MAP_GPIOIntEnable(GPIO_PORTQ_BASE, GPIO_PIN_3);
//		MAP_IntEnable(INT_GPIOQ3);
	
	    uiOdminter_PinNumber = NumPin;
	    uiSpeedCnt1 = 0; 
	    uC_MEnable  = true;
			uiStorkeCnt = 0;
}
/**************************
** @brief 
** @param
** @retval 100us
****************************/
void OdMeter_Start(void)
{
	  uC_Enable = 1;  
	  en = uC_Enable;
}
/**************************
** @brief 
** @param
** @retval 100us
****************************/
void Odmeter_Stop(void)
{
		uC_Enable = 0;
}
/**************************
** @brief 
** @param
** @retval 100us
****************************/
void Odmeter_Reset(void)
{
		//uiSpeedCntprv   = 0;
		//uiSpeed   	 = 0;
		uiSpeedCnt1  = 0;
		
		 en = uC_Enable;

}
/**************************
** @brief 
** @param
** @retval 100us
****************************/
void vOdmeter(void)
{
	static uint32_t ucMoniCnt = 0;

	if(uC_MEnable == false){
		uiStorkeCnt 	= 0;
		return;
	}
	
	statusBits_Tacho = port_Read_Input_Pin(uiOdminter_PinNumber);
	
	if((!statusBits_Tacho) && (statusBits_Tacho_Old)) //Falling edge
	{
		if(uC_Enable != 0)
		  uiSpeedCnt1++;
		else
		  uiSpeedCnt1 = 0;
		
		  uiStorkeCnt++;
	}
	
	statusBits_Tacho_Old = statusBits_Tacho;
	
	if(ucMoniCnt < 50000) //5Sec 
      ucMoniCnt++;
   else
   {
	   //tFan.uiSpeed1 = tFan.uiSpeedCnt1 * 30;
		 //1Cnt = 1Hz
		 //uiSpeed 			= uiSpeedCnt1 * 1000;  //100 Gain Hz
		 uiSpeed        = (uiStorkeCnt * 60) /5;
		 uiStorkeCnt 		= 0;
		 //uiSpeed 			= ((uiStorkeCnt - uiSpeedCntprv) * 60)/5;
		 //uiSpeedCntprv 	= uiStorkeCnt;
	  // uiSpeedCnt1 	= 0;
	   ucMoniCnt 		= 0;
	    
   }
	 
}

/**************************
** @brief 
** @param
** @retval
****************************/
uint16_t vOdmGetSpeed(void)
{
	return uiSpeed;
}
/**************************
** @brief 
** @param
** @retval
****************************/
uint16_t vOdmGetCount(void)
{
		return uiSpeedCnt1;
}
