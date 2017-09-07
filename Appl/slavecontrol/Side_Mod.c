/**
  ******************************************************************************
  * @file    side_mod.c
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
	#define BTCOUNT  2
	#define IRCOUNT  1
#elif defined(SL_G4S_THAI_MOD)
	#define BTCOUNT  3
	#define IRCOUNT  1
#elif defined(SL_HPT_HK_MOD)
	#define BTCOUNT  3
	#define IRCOUNT  1
#elif defined(SL_KUWAIT_MOD)
	#define BTCOUNT  3
	#define IRCOUNT  1
#elif defined(SL_QATAR_MOD)
	#define BTCOUNT  3
	#define IRCOUNT  1
#elif defined(SL_INDO_MOD)

	#define BTCOUNT  3
	#define IRCOUNT  1

#else

	#define BTCOUNT  4
	#define IRCOUNT  4

#endif
/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
 TButtonLED_Typedef		tButtonLED[BTCOUNT];
 TIRx_Typedef         tIRDoordet[IRCOUNT];


/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/
static void SideMode_Initial(TButtonLED_Typedef **BtLed, TIRx_Typedef **IRx);
static void SideBackground(void);


TMOD_InitTypeDef tModSideMode_Ctrl = 
{
	1,
	1,
	(uint8_t*)"SIDE",  
	SideMode_Initial,
	SideBackground, 
	NULL
	
};
/**************************
** @brief 
** @param
** @retval
****************************/
static void SideMode_Initial(TButtonLED_Typedef **BtLed, TIRx_Typedef **IRx)
{
	  uint8_t uC_Input = 0;
	
#if defined(SL_NDO_TURCK_MOD)
	
		///////////////////// Input 4  Add ////////////////////////
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);  //SW_SideDoor_Inside 
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);  //SW_CABDoor_OutsideP1
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_7,100,100,1); 	 //SW_HAT
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1); 	 //SOEM
	
		///////////////////// Button 3 led Add ////////////////////
	  uC_Input = 0;
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_3,TYPE_PORT_A,OUTPUT_CTRL_BITS_2,10,10);
	
	  //////////////////// Door IR TxRx ////////////////////////
	  uC_Input = 0;
	  sIR_Ctrl_Add(&tIRDoordet[uC_Input++],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);

#elif defined(SL_G4S_THAI_MOD) // THAI G4S 
	
		uC_Input = 0;
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);  //SW_SideDoor_Inside 
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_2,100,10000,1);  //SW_SideDoor_Outside
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);  //SW_CABSideDoor_Outside
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_7,100,100,1);    //Air Look 
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_8,100,100,1);    //SideDoorButton
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_9,100,100,1);    //TitSensor
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1);   //SW_OEM Switch
	 
		///////////////////// Button 3 led Add ////////////////////
		uC_Input = 0;
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_2,TYPE_PORT_A,OUTPUT_CTRL_BITS_3,10,10);
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_3,TYPE_PORT_A,OUTPUT_CTRL_BITS_2,10,10);
	
	  //////////////////// Door IR TxRx ////////////////////////
	  sIR_Ctrl_Add(&tIRDoordet[0],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
	
#elif defined(SL_HPT_HK_MOD)

	  ///////////////////// Input 4  Add ////////////////////////
		uC_Input = 0;
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);  //SW_SideDoor_Inside 
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_2,100,10000,1);  //SW_SideDoor_Outside
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);  //SW_CABSideDoor_Outside
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_8,100,10000,1);  //SW_SideDoor_Sensor
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1); 	 //SW_OEM Switch
	 
		///////////////////// Button 3 led Add ////////////////////
		uC_Input = 0;
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_2,TYPE_PORT_A,OUTPUT_CTRL_BITS_3,10,10);
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_3,TYPE_PORT_A,OUTPUT_CTRL_BITS_2,10,10);
	
	  //////////////////// Door IR TxRx ////////////////////////
	  sIR_Ctrl_Add(&tIRDoordet[0],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);

#elif defined(SL_KUWAIT_MOD)

    uC_Input = 0;
 	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);  //SW_SideDoor_Inside 
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_2,100,10000,1);  //SW_SideDoor_Outside
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);  //SW_CABSideDoor_Outside
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_8,100,10000,1);  //SW_SideDoor_Sensor
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1); 	 //SW_OEM Switch
	  ///////////////////// Button 3 led Add ////////////////////
		uC_Input = 0;
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_2,TYPE_PORT_A,OUTPUT_CTRL_BITS_3,10,10);
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_3,TYPE_PORT_A,OUTPUT_CTRL_BITS_2,10,10);
			
			
	  //////////////////// Door IR TxRx ////////////////////////
	  sIR_Ctrl_Add(&tIRDoordet[0],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
		
#elif defined(SL_QATAR_MOD) //1.2

		uC_Input = 0;
 	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);  //SW_SideDoor_Inside 
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_2,100,10000,1);  //SW_SideDoor_Outside
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);  //SW_CABSideDoor_Outside
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_8,100,10000,1);  //SW_SideDoor_Sensor
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1); 	 //SW_OEM Switch
	  ///////////////////// Button 3 led Add ////////////////////
		uC_Input = 0;
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_2,TYPE_PORT_A,OUTPUT_CTRL_BITS_3,10,10);
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_3,TYPE_PORT_A,OUTPUT_CTRL_BITS_2,10,10);
			
			
	  //////////////////// Door IR TxRx ////////////////////////
	  sIR_Ctrl_Add(&tIRDoordet[0],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
		
#elif defined(SL_INDO_MOD)

		uC_Input = 0;
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_1,100,10000,1);  //SW_SideDoor_Inside 
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_2,100,10000,1);  //SW_SideDoor_Outside
		IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_3,100,10000,1);  //SW_CABSideDoor_Outside
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_7,100,100,1); 	 //SW_HAT
	  IOInputSetConfig(&tInputMod[uC_Input++],INPUT_PIN_LOGIC_10,100,100,1); 	 //SOEM
	
		///////////////////// Button 3 led Add ////////////////////
	  uC_Input = 0;
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_1,TYPE_PORT_A,OUTPUT_CTRL_BITS_1,10,10);
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_2,TYPE_PORT_A,OUTPUT_CTRL_BITS_3,10,10);
		sLed_Ctrl_Add(&tButtonLED[uC_Input++],INPUT_DATA_BITS_MASK_3,TYPE_PORT_A,OUTPUT_CTRL_BITS_2,10,10);
	
	  //////////////////// Door IR TxRx ////////////////////////
	  uC_Input = 0;
	  sIR_Ctrl_Add(&tIRDoordet[0],INPUT_PIN_LOGIC_6,TYPE_PORT_B,OUTPUT_CTRL_BITS_7,10);
 
#else


#endif


	
	  *BtLed = (TButtonLED_Typedef*)&tButtonLED;
	  *IRx   = (TIRx_Typedef*)tIRDoordet;
	
	 
}

/**************************
** @brief 
** @param
** @retval 10ms
****************************/
static void SideBackground(void)
{

}


















//End of file
