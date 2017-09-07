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
	#define BTCOUNT  1
	#define IRCOUNT  2
#elif defined(SL_G4S_THAI_MOD)
	#define BTCOUNT  1
	#define IRCOUNT  5
#elif defined(SL_HPT_HK_MOD)
	#define BTCOUNT  1
	#define IRCOUNT  5
#elif defined(SL_KUWAIT_MOD)
	#define BTCOUNT  1
	#define IRCOUNT  5
	
#elif defined(SL_QATAR_MOD)

	#define BTCOUNT  1
	#define IRCOUNT  5

#elif defined(SL_INDO_MOD)

	#define BTCOUNT  1
	#define IRCOUNT  5
	
#elif defined (SL_S2S_KUWIAL_MOD)

	#define BTCOUNT  1
	#define IRCOUNT  3	
	
#else

	#define BTCOUNT  1
	#define IRCOUNT  5

#endif
/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
 TButtonLED_Typedef		tCAB_ButtonLED[BTCOUNT];
 TIRx_Typedef         tCAB_IRDoordet[IRCOUNT];

/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/

static void CABMode_Initial(TButtonLED_Typedef **BtLed, TIRx_Typedef **IRx);
static void CABModeBackground(void);


TMOD_InitTypeDef tModCABMode_Ctrl = 
{
	2,
	1,
	(uint8_t*)"CAB",  
	CABMode_Initial,
	CABModeBackground, 
	NULL
	
};

/**************************
** @brief 
** @param
** @retval
****************************/
static void CABMode_Initial(TButtonLED_Typedef **BtLed, TIRx_Typedef **IRx)
{
	uint8_t uC_Input = 0;
	
#ifdef SL_NDO_TURCK_MOD	
	
	  ///////// Input 1  Add //////////
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1, 100,10000,1);  	//SW_CABDoorButtonIndide	
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,10000,100,1);  	  //Sure Lock 2Sec 
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_11,100,100,1);    	//Hernees
	 
	  ///////// Button led ///////////
	  uC_Input = 0;
	  sLed_Ctrl_Add(&tCAB_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
	  ///////// IR Control ///////////
	  uC_Input = 0;
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_9,TYPE_PORT_C,OUTPUT_CTRL_BITS_1,10);
	
	  *BtLed = (TButtonLED_Typedef*)&tCAB_ButtonLED; 
	  *IRx   = (TIRx_Typedef*)tCAB_IRDoordet;
		
		odm_init(INPUT_PIN_LOGIC_12); 
	
#elif defined(SL_G4S_THAI_MOD) // THAI G4S 

    ///////// Input 3  Add //////////
		uC_Input = 0;
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);  	//SW_CABDoorButtonIndide
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1);    //Cab Solenoid
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_11,100,100,1);    //Hernees
		
	  ///////// Button led ///////////
		uC_Input = 0;
	  sLed_Ctrl_Add(&tCAB_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
	
	  ///////// IR Control ///////////
		uC_Input = 0;
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_7,TYPE_PORT_B,OUTPUT_CTRL_BITS_8,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_8,TYPE_PORT_B,OUTPUT_CTRL_BITS_9,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_9,TYPE_PORT_C,OUTPUT_CTRL_BITS_1,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_4,TYPE_PORT_C,OUTPUT_CTRL_BITS_2,10);
		 
	  *BtLed = (TButtonLED_Typedef*)&tCAB_ButtonLED; 
	  *IRx   = (TIRx_Typedef*)tCAB_IRDoordet;
		
		
#elif defined(SL_HPT_HK_MOD)

	  ///////// Input 1  Add //////////
		uC_Input = 0;
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);  	//SW_CABDoorButtonIndide
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1);    //Sure Lock  
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_11,100,100,1);  	//Park Gear  
		
		
	  ///////// Button led ///////////
		uC_Input = 0;
	  sLed_Ctrl_Add(&tCAB_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
	
	  ///////// IR Control ///////////
		uC_Input = 0;
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_4,TYPE_PORT_C,OUTPUT_CTRL_BITS_2,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_7,TYPE_PORT_B,OUTPUT_CTRL_BITS_8,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_8,TYPE_PORT_B,OUTPUT_CTRL_BITS_9,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_9,TYPE_PORT_C,OUTPUT_CTRL_BITS_1,10);
	  
	  *BtLed = (TButtonLED_Typedef*)&tCAB_ButtonLED; 
	  *IRx   = (TIRx_Typedef*)tCAB_IRDoordet;
		
	  odm_init(INPUT_PIN_LOGIC_12); 

#elif defined(SL_KUWAIT_MOD)

    uC_Input = 0;
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);  	//SW_CABDoorButtonIndide
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1);    //Sure Lock  
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_11,100,100,1);  	//Park Gear  
		///////// Button led ///////////
		uC_Input = 0;
	  sLed_Ctrl_Add(&tCAB_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
		
		 ///////// IR Control ///////////
		uC_Input = 0;
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_4,TYPE_PORT_C,OUTPUT_CTRL_BITS_2,10); //RxPassengerEscap
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_7,TYPE_PORT_B,OUTPUT_CTRL_BITS_8,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_8,TYPE_PORT_B,OUTPUT_CTRL_BITS_9,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_9,TYPE_PORT_C,OUTPUT_CTRL_BITS_1,10);
	  
	  *BtLed = (TButtonLED_Typedef*)&tCAB_ButtonLED; 
	  *IRx   = (TIRx_Typedef*)tCAB_IRDoordet;
		
	  odm_init(INPUT_PIN_LOGIC_12); 
		
#elif defined(SL_QATAR_MOD) //1.2

		uC_Input = 0;
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);  	//SW_CABDoorButtonIndide
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1);    //Sure Lock  
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_11,100,100,1);  	//Park Gear  
		///////// Button led ///////////
		uC_Input = 0;
	  sLed_Ctrl_Add(&tCAB_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
		
		 ///////// IR Control ///////////
		uC_Input = 0;
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_4,TYPE_PORT_C,OUTPUT_CTRL_BITS_2,10); //RxPassengerEscap
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_7,TYPE_PORT_B,OUTPUT_CTRL_BITS_8,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_8,TYPE_PORT_B,OUTPUT_CTRL_BITS_9,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_9,TYPE_PORT_C,OUTPUT_CTRL_BITS_1,10);
	  
	  *BtLed = (TButtonLED_Typedef*)&tCAB_ButtonLED; 
	  *IRx   = (TIRx_Typedef*)tCAB_IRDoordet;
		
	  odm_init(INPUT_PIN_LOGIC_12); 
		
		
#elif defined(SL_INDO_MOD)

		uC_Input = 0;
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);  	//SW_CABDoorButtonIndide
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1);    //Sure Lock  
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_11,100,100,1);  	//Park Gear  
		///////// Button led ///////////
		uC_Input = 0;
	  sLed_Ctrl_Add(&tCAB_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
		
		 ///////// IR Control ///////////
		uC_Input = 0;
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_4,TYPE_PORT_C,OUTPUT_CTRL_BITS_2,10); //RxPassengerEscap
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_7,TYPE_PORT_B,OUTPUT_CTRL_BITS_8,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_8,TYPE_PORT_B,OUTPUT_CTRL_BITS_9,10);
	  sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_9,TYPE_PORT_C,OUTPUT_CTRL_BITS_1,10);
	  
	  *BtLed = (TButtonLED_Typedef*)&tCAB_ButtonLED; 
	  *IRx   = (TIRx_Typedef*)tCAB_IRDoordet;
		
	  odm_init(INPUT_PIN_LOGIC_12); 

#elif defined (SL_S2S_KUWIAL_MOD)

  uC_Input = 0;
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,100,1);   
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);   
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_6,100,100,1);   
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_8,100,100,1);   
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1);   
	IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_11,100,100,1);  
	
	uC_Input = 0;
	sLed_Ctrl_Add(&tCAB_ButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_2,10,10);//INPUT_DATA_BITS_MASK_1
	
	uC_Input = 0;
	sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_9,TYPE_PORT_C,OUTPUT_CTRL_BITS_1,10);//PassengerDoorRx
	sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_2,TYPE_PORT_C,OUTPUT_CTRL_BITS_2,10);//VaultDoor RX
	sIR_Ctrl_Add(&tCAB_IRDoordet[uC_Input++],INPUT_PIN_LOGIC_7,TYPE_PORT_B,OUTPUT_CTRL_BITS_8,10);//DriverDoor Rx
	

	*BtLed = (TButtonLED_Typedef*)&tCAB_ButtonLED; 
	*IRx   = (TIRx_Typedef*)tCAB_IRDoordet;
	
	vWiegand_Init();
	
	odm_init(INPUT_PIN_LOGIC_12); 
	
#else



#endif

		
}

/**************************
** @brief 
** @param
** @retval
****************************/
static void CABModeBackground(void)
{
	
	
}













//End of file
