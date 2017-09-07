/**
  ******************************************************************************
  * @file    CAB_mod.c
  * @author  Kittanadon Keawratchakit
  * @version V2.0.1
  * @date    17-OCT-2016
  * @brief   This file is main applications side module control
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
#include "rte/rte.h" 
#include "slavecontrol/slave_ctrl.h"

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

#define BTCOUNT  1
#define IRCOUNT  1

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
 TButtonLED_Typedef		tRear_ButtonLED[BTCOUNT];
 TIRx_Typedef         tRear_IRDoordet[IRCOUNT];

/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/

static void RearMode_Initial(TButtonLED_Typedef **BtLed, TIRx_Typedef **IRx);
static void RearModeBackground(void);


TMOD_InitTypeDef tModRearMode_Ctrl = 
{
	4,
	1,
	(uint8_t*)"Rear",  
	RearMode_Initial,
	RearModeBackground, 
	NULL
	
};

/**************************
** @brief 
** @param
** @retval
****************************/
static void RearMode_Initial(TButtonLED_Typedef **BtLed, TIRx_Typedef **IRx)
{
	uint8_t uC_Input = 0;
	
#if defined(SL_G4S_THAI_MOD)

	
#elif defined(SL_HPT_HK_MOD)	
		///////// Input 1 /////////////////
	uC_Input = 0;
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);   //RearOutsideButton_SW
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,100,1);  		//SIDEModeCMD
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_4,100,100,1);  		//DepoModeCMD
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_5,100,100,1);  		//ParkModCMD
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_7,100,100,1);  		//RearSureLock_SW
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_8,100,100,1);  		//SOSCMD
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_9,100,100,1);  		//RTBModeCMD
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1);  	//SecureModeCMD
	
	///////// Button led ///////////
	uC_Input = 0;
	sLed_Ctrl_Add(&tRear_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_5,10,10);
	
	///////// IR Control ///////////
	uC_Input = 0;
	sIR_Ctrl_Add(&tRear_IRDoordet[uC_Input],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
	
#endif

	*BtLed = (TButtonLED_Typedef*)&tRear_ButtonLED;  
	*IRx   = (TIRx_Typedef*)tRear_IRDoordet;
}

/**************************
** @brief 
** @param
** @retval
****************************/
static void RearModeBackground(void)
{
	
	
}



















//End of file
