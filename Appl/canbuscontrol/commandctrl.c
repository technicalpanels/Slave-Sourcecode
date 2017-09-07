/**
  ******************************************************************************
  * @file    canbus.c
  * @author  Kittanadon Keawratchakit
  * @version V2.0.1
  * @date    17-OCT-2016
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
#include "rte/rte.h" 
#include "slavecontrol/slave_ctrl.h"
#include "can/hcan.h"
#include "canbuscontrol/commandctrl.h"
#include <string.h>

extern  uint32_t key;

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
static void SDO1_Write(void);
static void SDO1_Read(void);
static void HeartBeat_Read(void);

void UnlockEnterPSMode(void);
void Read_Boot_Status(void);
/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
p_Command_typeDef CanCommand[256];
extern TCommand_Typedef 	tCanCommand;

tPSMode_Typedef tPSMode;

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/
void AddFucCommand(p_Command_typeDef *p , unsigned char Command, unsigned char tran_type,void (*EventHandler)(void));


/**************************
** @brief 
** @param
** @retval
****************************/
void Command_Init(void)
{
	uint16_t i  = 0;
	
	for(i = 0 ;i < 256;i++)
   {
      //Add Null Functions
	   AddFucCommand((p_Command_typeDef*)&CanCommand,i,(TYPE_READ|TYPE_WRITE),Dummy_Fucntions);
		 
   }
	 
	 //////////// Add Command //////////////
	 AddFucCommand((p_Command_typeDef*)&CanCommand,0x0B,TYPE_WRITE,SDO1_Write);
	 AddFucCommand((p_Command_typeDef*)&CanCommand,0x0C,TYPE_READ,SDO1_Read);
	 AddFucCommand((p_Command_typeDef*)&CanCommand,0x0F,TYPE_READ,HeartBeat_Read);
	 
	 AddFucCommand((p_Command_typeDef*)&CanCommand,0x03,TYPE_WRITE,UnlockEnterPSMode); 
	 AddFucCommand((p_Command_typeDef*)&CanCommand,0x02,TYPE_READ,Read_Boot_Status);
	 
}
/* This functions first initial to Add any command use in this project
 * Param : *p  					: Pointer   p_Command_typeDef
 *				  Command			: Number of Command
 *					tran_type 	: Read / Write
 *					EventHander	: void Functions in call by command
 */
void AddFucCommand(p_Command_typeDef *p , unsigned char Command, unsigned char tran_type,void (*EventHandler)(void))

{
	   (p+Command)->Transaction_type 	= tran_type;
	   (p+Command)->CommandCode 			= Command;
	   (p+Command)->EventHandler 			= EventHandler;

}
/**************************
** @brief 
** @param
** @retval
****************************/
void CMD_Handler_Process(TCommand_Typedef *pcmd)
{
	if(pcmd->cmd_reg > 255)
	{
		return ;
	}
	
	//O1 Drirect
	if( (CanCommand[pcmd->cmd_reg].EventHandler != NULL)
 		&&(CanCommand[pcmd->cmd_reg].CommandCode == pcmd->cmd_reg))
	{
		CanCommand[pcmd->cmd_reg].EventHandler();
		
		return;
	}
	else
	{
		 pcmd->cmd_reg 			= 0x00;
		 pcmd->cmd_rw 			= 0x00;
		 pcmd->DataRead[0] 	= 0x00;
		 
		 //USBData_Tranrsactions(pComDowork.DataRead,1);
	}
	
}

/**
  * @brief 
  * @param  
  * @retval 
  */
void Dummy_Fucntions(void)
{
	
	
}
/**************************
** @brief Restpone Status Heart Ok
** @param 0x0F Command 
** @retval
****************************/
static void HeartBeat_Read(void)
{
	
}
/**************************
** @brief OLD Slave Support Master Write Output Data
** @param 0x0B Command 
** @retval
****************************/
static void SDO1_Write(void)
{
	 //LED_DEBUG_TOGGLE();
	 memcpy((TOSlave_OutputCtrl_Typedef*)&tOSlave_OutputData_Ctrl, (uint8_t*)&tCanCommand.DataWrite, 8);
	
	
	if(tOSlave_OutputData_Ctrl.odm_status)
	{
		OdMeter_Start();
	}
	else{
		Odmeter_Stop();
		Odmeter_Reset(); 
	}
}

/**************************
** @brief OLD Slave Support Master Read Output Data
** @param 0x0C Command 
** @retval
****************************/
static void SDO1_Read(void)
{
	uint8_t i = 0;
	uint16_t data = 0;
	uint32_t Odmetercnt = 0;
	
	LED_DEBUG_TOGGLE();
	
//   if(tCanCommand.DataWrite[0]){
//		 
#if 0	
			for(i = 0;i< MAX_INPUT_LOGIC ;i++)
			{ 
				/////// OLD Master Detected ///////
				if(port_Read_Input_Pin(i) != 0)
				{
					data |= (1<<i);
					
				}else
				{  
					data &= ~(1 << i);
				}
				
			}
			
			//GET_WIEG_ID();
		 tCanCommand.DataRead[0] = data &0xFF;
		 tCanCommand.DataRead[1] = (data >> 8) & 0xFF;
		 tCanCommand.DataRead[2] = GET_WIEG_ID();
		// 3-4 ODM Pulse
		// 4-5 ODM Rate
			
#else			
			//tInputStatus.Input
			//tIOStatus_Input
		 data = ~(tInputStatus.Input.uiport);
		 //0 - 1 Input Status 
		 tCanCommand.DataRead[0] =  data &0xFF;
		 tCanCommand.DataRead[1] = (data >> 8) & 0xFF;
		 // 2 - Wieng ID 
		 tCanCommand.DataRead[2] =  GET_WIEG_ID();
			
		 // 3-4 ODM Pulse
		 Odmetercnt = ODM_GET_COUNT(); 
			
			if (Odmetercnt < 65536) {
				data = Odmetercnt;
			} else {
				data = 65535;
			}
			
		 tCanCommand.DataRead[4] =	data &0xFF;
		 tCanCommand.DataRead[5] = (data >> 8) & 0xFF;
			
		// 5-6 ODM Rate
		  Odmetercnt = ODM_GET_SPEED();
		 if (Odmetercnt < 65536) {
				data = Odmetercnt;
			} else {
				data = 65535;
			}
		 tCanCommand.DataRead[6] =	data &0xFF;
		 tCanCommand.DataRead[7] = (data >> 8) & 0xFF;
		 
#endif		


	
}
/*  @brief 
  * @param 0x02
  * @retval 
  */
void Read_Boot_Status(void)
{
	 tCanCommand.DataRead[0] =  tPSMode.Byte;
}
/*  @brief 
  * @param 0x02
  * @retval 
  */
void UnlockEnterPSMode(void)
{
	 if(!strncmp("GPV02",(char*)&tCanCommand.DataWrite[0],5))	
		{	
			  key = 1;
			  SysCtlReset();	//Wait for System Reset
		}
		else if(!strncmp("GPVSL",(char*)&tCanCommand.DataWrite[0],5))	
		{
				
		}
}

//END OF FILE
