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

#if defined(SL_NDO_TURCK_MOD)
	#define BTCOUNT  5
	#define IRCOUNT  1
#elif defined(SL_G4S_THAI_MOD)
	#define BTCOUNT  5
	#define IRCOUNT  2
#elif defined(SL_HPT_HK_MOD)
	#define BTCOUNT  5
	#define IRCOUNT  1
#elif defined(SL_KUWAIT_MOD)
	#define BTCOUNT  4
	#define IRCOUNT  1
#elif defined(SL_QATAR_MOD)
	#define BTCOUNT  4
	#define IRCOUNT  1
#elif defined(SL_INDO_MOD)
	#define BTCOUNT  5
	#define IRCOUNT  1

#else
	#define BTCOUNT  5
	#define IRCOUNT  1

#endif
/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
 TButtonLED_Typedef		tVault_ButtonLED[BTCOUNT];
 TIRx_Typedef         tVault_IRDoordet[IRCOUNT];

/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/

static void VaulMode_Initial(TButtonLED_Typedef **BtLed, TIRx_Typedef **IRx);
static void VaulModeBackground(void);


TMOD_InitTypeDef tModVaulMode_Ctrl = 
{
	3,
	1,
	(uint8_t*)"Vault",  
	VaulMode_Initial,
	VaulModeBackground, 
	NULL
	
};

/**************************
** @brief 
** @param
** @retval
****************************/
static void VaulMode_Initial(TButtonLED_Typedef **BtLed, TIRx_Typedef **IRx)
{
	uint8_t uC_Input = 0;
	
#ifdef SL_NDO_TURCK_MOD	
	
	///////// Input 1 /////////////////
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);   
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_2,100,10000,1); 	
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);  	
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_7,10000,100,1);  		
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_8,100,100,1);  		
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_9,100,10000,1);  	
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,10000,1);  
	
	///////// Button led ///////////
	uC_Input = 0;
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1, TYPE_PORT_A, OUTPUT_CTRL_BITS_8,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_2, TYPE_PORT_A, OUTPUT_CTRL_BITS_2,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_3, TYPE_PORT_A, OUTPUT_CTRL_BITS_5,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_9, TYPE_PORT_A, OUTPUT_CTRL_BITS_6,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_10,TYPE_PORT_A, OUTPUT_CTRL_BITS_7,10,10);
	
	///////// IR Control ///////////
	sIR_Ctrl_Add(&tVault_IRDoordet[0],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
	 
	vWiegand_Init();
	
#elif defined(SL_G4S_THAI_MOD) // THAI G4S 

	///////// Input 1 /////////////////
	uC_Input = 0;
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_2,100,10000,1); 	
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);  	
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_7,10000,100,1);  		
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_8,100,100,1);  		
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_9,100,10000,1);  	
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,10000,1);  
	
	uC_Input = 0;
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_2, TYPE_PORT_A, OUTPUT_CTRL_BITS_2,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_3, TYPE_PORT_A, OUTPUT_CTRL_BITS_5,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_9, TYPE_PORT_A, OUTPUT_CTRL_BITS_6,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_10, TYPE_PORT_A, OUTPUT_CTRL_BITS_7,10,10);

	///////// IR Control ///////////
	sIR_Ctrl_Add(&tVault_IRDoordet[0],INPUT_PIN_LOGIC_1,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
	sIR_Ctrl_Add(&tVault_IRDoordet[1],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_8,10);
	
	vWiegand_Init();
	
#elif defined(SL_HPT_HK_MOD)

		///////// Input 1 /////////////////
  uC_Input = 0;
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);   //CrewRegister_SW4
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_2,100,10000,1); 	//ValutDoorButtonOutside_SW
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);  	//CrewRegister_SW1
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_7,100,100,1);  		//VaultSureLock_SW
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_8,100,100,1);  		//Alarm_Net
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_9,100,10000,1);  	//CrewRegister_SW2
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,10000,1);  //CrewRegister_SW3
	
	 ///////// Button led ///////////
	uC_Input = 0;
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_2,TYPE_PORT_A,OUTPUT_CTRL_BITS_2,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_3,TYPE_PORT_A,OUTPUT_CTRL_BITS_5,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_9,TYPE_PORT_A,OUTPUT_CTRL_BITS_6,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_10,TYPE_PORT_A,OUTPUT_CTRL_BITS_7,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_8,10,10);
	
	sIR_Ctrl_Add(&tVault_IRDoordet[0],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
	
	vWiegand_Init();
	
#elif defined(SL_KUWAIT_MOD)

  uC_Input = 0;
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);   //
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_2,100,10000,1); 	//
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);  	//
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_7,100,100,1);  		//
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_8,100,100,1);  		//
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_9,100,10000,1);  	//
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,10000,1);  //
	
	 ///////// Button led ///////////
	uC_Input = 0;
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_2,TYPE_PORT_A,OUTPUT_CTRL_BITS_2,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_3,TYPE_PORT_A,OUTPUT_CTRL_BITS_5,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_9,TYPE_PORT_A,OUTPUT_CTRL_BITS_6,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_10,TYPE_PORT_A,OUTPUT_CTRL_BITS_7,10,10);
	//sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_8,10,10);
	
	sIR_Ctrl_Add(&tVault_IRDoordet[0],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);

	vWiegand_Init();
	
#elif defined(SL_QATAR_MOD) //1.2

	uC_Input = 0;
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);   //
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_2,100,10000,1); 	//
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);  	//
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_7,100,100,1);  		//
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_8,100,100,1);  		//
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_9,100,10000,1);  	//
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,10000,1);  //
	
	 ///////// Button led ///////////
	uC_Input = 0;
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_2,TYPE_PORT_A,OUTPUT_CTRL_BITS_2,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_3,TYPE_PORT_A,OUTPUT_CTRL_BITS_5,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_9,TYPE_PORT_A,OUTPUT_CTRL_BITS_6,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_10,TYPE_PORT_A,OUTPUT_CTRL_BITS_7,10,10);
	
	
	sIR_Ctrl_Add(&tVault_IRDoordet[0],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);

	vWiegand_Init();
	
#elif defined(SL_INDO_MOD)

	///////// Input 1 /////////////////
	uC_Input = 0;
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);   
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_2,100,10000,1); 	
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);  	
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_7,10000,100,1);  		
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_8,100,100,1);  		
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_9,100,10000,1);  	
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,10000,1);  
	
	///////// Button led ///////////
	uC_Input = 0;
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1, TYPE_PORT_A, OUTPUT_CTRL_BITS_8,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_2, TYPE_PORT_A, OUTPUT_CTRL_BITS_2,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_3, TYPE_PORT_A, OUTPUT_CTRL_BITS_5,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_9, TYPE_PORT_A, OUTPUT_CTRL_BITS_6,10,10);
	sLed_Ctrl_Add(&tVault_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_10,TYPE_PORT_A, OUTPUT_CTRL_BITS_7,10,10);
	
	///////// IR Control ///////////
	sIR_Ctrl_Add(&tVault_IRDoordet[0],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
	 
	vWiegand_Init();
	
	
#else


#endif

	*BtLed = (TButtonLED_Typedef*)&tVault_ButtonLED; 
	*IRx   = (TIRx_Typedef*)tVault_IRDoordet;
}

/**************************
** @brief 
** @param
** @retval
****************************/
static void VaulModeBackground(void)
{
	
	
}





















//End of file
