/**
  ******************************************************************************
  * @file    can.c
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
#include "can/hcan.h"
#include "string.h"
#include "canbuscontrol/commandctrl.h"
#include "rte/rte.h" 

extern void CMD_Handler_Process(TCommand_Typedef *pcmd);


/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
#define CAN_SPEED									1000000U
#define CAN_MASK									0x7f

#define CAN_STATE_IDLE          	0
#define CAN_STATE_TX            	1
#define CAN_STATE_RR            	2



volatile bool g_bErrFlag 	= 0;
volatile bool g_bRXFlag 	= 0;
volatile bool g_bTXFlag 	= 0;

volatile uint8_t uCanState = 0;

 
TCommand_Typedef 	tCanCommand;
tCANBUSMsg  		 	tCanMsg[32];

int32_t pirCan = 0;
uint32_t ulStatus = 0;

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
uint8_t CanBusSet(tCANBUSMsg *p ,
                  uint8_t     ui32MsgLen,
                  uint8_t 		Object_ID,
                  tMsgObjType tMsgType,
                  uint32_t 		ui32MsgID,
                  uint32_t 		ui32MsgIDMask, 
                  uint32_t 		ui32Flags);
/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/
 
uint32_t uiErrorCounter = 0;
uint8_t  uCAddress;
/**************************
** @brief 
** @param
** @retval
****************************/
void can_Init(uint8_t Address)
{ 

    
	  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
	
	  ROM_CANInit(CAN0_BASE);
	 
	  ROM_CANBitRateSet(CAN0_BASE, ui32SysClock, CAN_SPEED);//CAN_SPEED
	 
	  ROM_CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
	
	  //pirCan = ROM_IntPriorityGet(INT_CAN0);
	
	  MAP_IntPrioritySet(INT_CAN0,0x40); 			// low priority
	  pirCan = MAP_IntPriorityGet(INT_CAN0);  // Get Priority
	  
	  //
    // Enable the CAN interrupt on the processor (NVIC).
    //
    ROM_IntEnable(INT_CAN0); 
	
    //
    // Enable the CAN for operation.
    //
    ROM_CANEnable(CAN0_BASE);
		//
		//
		//
		ROM_CANRetrySet(CAN0_BASE, 0);
		
		
		//
		//
		//
		CanBusSet((tCANBUSMsg*)&tCanMsg, 
		             8 ,
		             RXOBJECT,
								 MSG_OBJ_TYPE_RX,
							   Address,
								 CAN_MASK,
							  (uint32_t)(MSG_OBJ_USE_ID_FILTER|MSG_OBJ_RX_INT_ENABLE)); 
								
	 uCanState = CAN_STATE_IDLE;	 
	 
	 uCAddress= Address;
}
/**************************
** @brief 
** @param
** @retval
****************************/
void can_ResetError(void)
{
  uint32_t ptx , pRx ;
	
	if(g_bErrFlag)
	{
	
		
	}
	
	//CANErrCntrGet(CAN0_BASE,&ptx,&pRx);
	
//	if(CANStatusGet(CAN0_BASE, CAN_STS_CONTROL) != CAN_STATUS_LEC_NONE)
//	{
//		ulStatus = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
//		ulStatus = ulStatus & (~CAN_STATUS_RXOK);
//		ulStatus = ulStatus & (~CAN_STATUS_TXOK);
//		
//		if(ulStatus != CAN_STATUS_LEC_NONE)
//		{
//			port_StatusLed_Write(0);
//		}
//		else
//		{
//			port_StatusLed_Write(1);
//		}
//		
//	}
}
/**************************
** @brief 
** @param
** @retval
****************************/
uint8_t CanBusSet(tCANBUSMsg *p ,
                  uint8_t     ui32MsgLen,
                  uint8_t 		Object_ID,
                  tMsgObjType tMsgType,
                  uint32_t 		ui32MsgID,
                  uint32_t 		ui32MsgIDMask, 
                  uint32_t 		ui32Flags)
{
	
	  tCANMsgObject 	sCanMsg;
	
    sCanMsg.ui32MsgID 			= ui32MsgID;
    sCanMsg.ui32MsgIDMask 	= ui32MsgIDMask;
    sCanMsg.ui32Flags 			= ui32Flags;
    sCanMsg.ui32MsgLen 		  = ui32MsgLen;
    sCanMsg.pui8MsgData 		= p[Object_ID-1].ui8ArrCanData;

    p[Object_ID - 1].eMsgObjType = tMsgType;

    ROM_CANMessageSet(CAN0_BASE, Object_ID, &sCanMsg, tMsgType);

	 return 1;
}
/**************************
** @brief 
** @param
** @retval
****************************/
uint8_t CanBusTxWrite(uint8_t *pBuffer,
	                 uint32_t ui32MsgID, 
                   uint8_t  Object_ID,
                   uint8_t  ui32MsgLen)
{
	if(uCanState != CAN_STATE_IDLE)
		 return 0;
	
	memcpy(&tCanMsg[Object_ID-1].ui8ArrCanData, pBuffer, ui32MsgLen);
	
	tCanMsg[Object_ID-1].ulStatus = CAN_STATE_TX;
	
	CanBusSet((tCANBUSMsg*)&tCanMsg, 
	               ui32MsgLen ,					//Data Length
		             Object_ID,						//TXOBJECT,						//Object_ID
								 MSG_OBJ_TYPE_TX,     //Type Tx
							   ui32MsgID,						//OwnAddr 
								 0,
							  (uint32_t)(MSG_OBJ_TX_INT_ENABLE)); 
	
	uCanState = CAN_STATE_TX;
	
	return 1;
}
/**************************
** @brief 
** @param
** @retval
****************************/
static __inline void CantoComamand(tCANBUSMsg *CanMsg)
{
	if(CanMsg->Cmd <= 255){
		
		tCanCommand.cmd_reg 		= CanMsg->Cmd; 
		tCanCommand.write_count = CanMsg->ucLength;
		
		memset(tCanCommand.DataWrite,0,8);
		
		//Copy to Appl Buffer 
		memcpy(&tCanCommand.DataWrite, &CanMsg->ui8ArrCanData, CanMsg->ucLength);
		
		/////////////////////////////////////////////////
		//////////// Command Process Data Wrte  /////////
		/////////////////////////////////////////////////
		CMD_Handler_Process(&tCanCommand);
		
//		while(HWREG(CAN0_BASE + CAN_O_IF1CRQ) & CAN_IF1CRQ_BUSY);

//		while(HWREG(CAN0_BASE + CAN_O_TXRQ1))
//		{
//			
//		}
		/////////////////////////////////////////////////
		//////////// CAN Tx Data To Master //////////////
		/////////////////////////////////////////////////
		if(tCanCommand.cmd_rw || tCanCommand.cmd_reg == 0x0C || tCanCommand.cmd_reg == 0x02){
			
	    if(!CanBusTxWrite((uint8_t*)&tCanCommand.DataRead,(uint32_t)(SLAVE_ADD_GET() | (tCanCommand.cmd_reg<<7)) ,TXOBJECT, 8))
			{
				 ///Can tx error state Busy
			}
			
		}
	}
	
}

/**************************
** @brief 
** @param
** @retval
****************************/
void CAN0IntHandler(void)
{
	 uint32_t 			ui32Status;
	 tCANMsgObject  sCANMessage;
	 tMsgObjType    eMsgObjType;
	 tCANBUSMsg     *eMessage;
	
	 
    //
    // Read the CAN interrupt status to find the cause of the interrupt
    //
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
		//
    // If the cause is a controller status interrupt, then get the status
    //
    if(ui32Status == CAN_INT_INTID_STATUS)
    {
			//port_StatusLed_Write(0);
			CANIntClear(CAN0_BASE, CAN_INT_INTID_STATUS);
        // Read the controller status.  This will return a field of status
        // error bits that can indicate various errors.  Error processing
        // is not done in this example for simplicity.  Refer to the
        // API documentation for details about the error status bits.
        // The act of reading this status will clear the interrupt.
        //

        ui32Status = ROM_CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
			
			  ulStatus = ui32Status;
			
			  //Remove TXRX Ok 
			  ui32Status = ui32Status & (~CAN_STATUS_RXOK);
			  ui32Status = ui32Status & (~CAN_STATUS_TXOK);
			 
			  if (ui32Status != CAN_STATUS_LEC_NONE)
        {	
					//LED_DEBUG_TOGGLE();
					 //ulStatus = ui32Status;
					//
					// Set a flag to indicate some errors may have occurred.
					//
					g_bErrFlag = 1;
				
					 if(ui32Status & CAN_STATUS_BUS_OFF == CAN_STATUS_BUS_OFF)
					 { 
							//msg_stat |= HAL_CAN_RESULT_BUS_OFF;
							 // Bus-off disables the module. To recover we must re-enable the module
							 CANEnable(CAN0_BASE);
						   //port_StatusLed_Write(0);
						 
						   //ROM_CANRetrySet(CAN0_BASE, 1);

					 }
           else
 					 {
						   //ROM_CANRetrySet(CAN0_BASE, 0);
						    //port_StatusLed_Write(1);
					 }						 
			  }

    }
		else if (ui32Status > 0 && ui32Status <= 32) //1 - 32 Message Box 
		{
			 eMessage 		= &tCanMsg[ui32Status - 1];
			
			 eMsgObjType  = eMessage->eMsgObjType;
			
		  if(eMsgObjType == MSG_OBJ_TYPE_RX)// && g_bRXFlag == 0) //|| MSG_OBJ_TYPE_RX_REMOTE
			{
				//ROM_CANRetrySet(CAN0_BASE, 0);
				 //Data Buffer 
				sCANMessage.pui8MsgData = eMessage->ui8ArrCanData;
				 //For Dirver Tiva 2.1.156 Need to Get Data Before Clear  -(Kittanadon 01.09.2017)
				CANMessageGet(CAN0_BASE,RXOBJECT,(tCANMsgObject*)&sCANMessage ,1);
				 //Get Length
				eMessage->ucLength = sCANMessage.ui32MsgLen;
				 //Custom Command fillter bit 7-10 (ID 11Bits)
				eMessage->Cmd  = (uint8_t)((sCANMessage.ui32MsgID & 0x0780) >> 7);
				
				if((sCANMessage.ui32Flags & MSG_OBJ_NEW_DATA) != 0)
				{
					eMessage->ulStatus =  CAN_STATUS_LEC_NONE;
					
					CantoComamand(eMessage);
				
					
				}
				
#if 0
				if((uint8_t)((sCANMessage.ui32MsgID & 0x0780) >> 7) == 0x0B){
			     LED_DEBUG_TOGGLE();
				}
#endif
				
				//CANIntClear(CAN0_BASE, ui32Status); //-(Kittanadon 01.09.2017)
        //CANMessageClear(CAN0_BASE,ui32Status);
				
				g_bErrFlag 	= 0;
				g_bRXFlag 	= 1;
			}
			else
			{
			   
					CANIntClear(CAN0_BASE,ui32Status);
				
				  CANMessageClear(CAN0_BASE,ui32Status); // Kittnadon (02.01.2017)
				
				  tCanMsg[ui32Status-1].ulStatus = CAN_STATE_IDLE;
					uCanState = CAN_STATE_IDLE;
				
					g_bRXFlag = 0;
					g_bErrFlag = 0;
			}
			
		}
		else
		{
			
		}
	
}
 
//END OF FILE
