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
#include "rte/rte.h" 
#include "slavecontrol/slave_ctrl.h"
/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
 #define  SIDE_ADDRESS      1
 #define  CAB_ADDRESS       2
 #define  VAULT_ADDRESS			3
 #define  REAR_ADDRESS			4
 
 
 #define  LED_OFF_STATE   	0
 #define  LED_ON_STATE   		1
 #define  LED_BLINK_STATE   2
 
 extern  TMOD_InitTypeDef 		tModSideMode_Ctrl;
 extern  TMOD_InitTypeDef     tModCABMode_Ctrl;
 extern  TMOD_InitTypeDef 		tModVaulMode_Ctrl;
 extern	 TMOD_InitTypeDef 		tModRearMode_Ctrl;
/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
static uint8_t OwnAddress = 0;

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
TInputStatus_Typedef  		tIOStatus_Input,tIStatus_Ctrl_Mask;
TOutputStatus_Typedef 		tOutputOverride;


TOSlave_OutputCtrl_Typedef  tOSlave_OutputData_Ctrl ;


TButtonLED_Typedef 	*pButtonled;
TIRx_Typedef        *pIRDoor;
TMOD_InitTypeDef		*pModule;

static uint8_t  uC_Timer_Tick = 0;
static uint8_t 	uLed_State 		= 0;
static uint16_t uC_Led_Count 	= 0;

static uint8_t  uC_BtLed      = 0;
static uint8_t  uC_BtIR       = 0;

/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/
static __inline void vButton_LED_Ctrl(void);
static __inline void vIR_Ctrl(void);	
static __inline void vStatus_Update(void);

/**************************
** @brief Slave Control Initial 
** @param
** @retval
****************************/
uint8_t App_Slave_Init(void)
{
	 pModule = NULL;
		//////// Initial Read Own Address Of slave ////
	 OwnAddress = IORead_SlaveMode();
   
	 uC_BtLed = 0;
	 uC_BtIR  = 0;
	
	if(OwnAddress == SIDE_ADDRESS){
		
		pModule   	= (TMOD_InitTypeDef*)&tModSideMode_Ctrl;

		//Module Add Control 
	  if(pModule != NULL) {
	    pModule->startup(&pButtonled,&pIRDoor);
		}
		
	}else if(OwnAddress == CAB_ADDRESS){
		
		pModule   	= (TMOD_InitTypeDef*)&tModCABMode_Ctrl;
		//Module Add Control 
	  if(pModule != NULL) {
	    pModule->startup(&pButtonled,&pIRDoor);
		}
	}
	else if(OwnAddress == VAULT_ADDRESS){
		
		pModule   	= (TMOD_InitTypeDef*)&tModVaulMode_Ctrl;
		//Module Add Control 
	  if(pModule != NULL) {
	    pModule->startup(&pButtonled,&pIRDoor);
		}
		
	}
	
#if defined(SL_NDO_TURCK_MOD)  //3 Module 
	
	else
	{
		//Error
	}
	
#else
	
  else if(OwnAddress == REAR_ADDRESS){
		
		pModule   	= (TMOD_InitTypeDef*)&tModRearMode_Ctrl;
		//Module Add Control 
	  if(pModule != NULL) {
	    pModule->startup(&pButtonled,&pIRDoor);
		}
		
	}
	
#endif	
	
	if(pModule == NULL) {
		uC_BtLed = 0;
	  uC_BtIR  = 0;
	}
	 
	return OwnAddress;
	
}
/**************************
** @brief Get Own Address ID 
** @param
** @retval
****************************/
uint8_t App_Slave_GetID(void)
{
	return OwnAddress;
}
/**************************
** @brief 
** @param
** @retval
****************************/
void App_Slave_Ctrl(void)
{
	uC_Timer_Tick++;
	switch(uC_Timer_Tick)
	{
		case 1:
			pModule->background();
			break;
		
		case 2:
			vButton_LED_Ctrl();
			break;
		
		case 3:
			vIR_Ctrl(); 
			break;
		
		case 4:
			
			break;
		
		case 5:
			break;
		
		case 6:
			break;
		
		case 7:
			break;
		
		case 8:
			break;
		
		case 9:
		
			break;
		
		case 10:
			
			vStatus_Update();
		
			uC_Timer_Tick = 0;
		  
			break;
	}
	
	
}
/**************************
** @brief 
** @param
** @retval
****************************/
void sLed_Ctrl_Add(TButtonLED_Typedef *p ,uint16_t BitsMask,uint16_t OutputPort , uint16_t OutputPin ,uint16_t MaxSetDelay , uint16_t MaxResetDelay)
{
	p->InputBitsMask 	= BitsMask;
	p->OutputPort 		= OutputPort;
	p->OutputPin 			= OutputPin;
	
	p->uiControlMask  = IOGetOutput_BitsMask(OutputPort,OutputPin);
	
	p->MaxSetDelay    = MaxSetDelay;
	p->uC_State				= 1;
	p->uC_Count 			= 0;
	
	switch(OutputPort)
	{
		case TYPE_PORT_A:
	    p->p_data         = (uint32_t*)&tOSlave_OutputData_Ctrl.output_a.port;
		  TPortControl_A[OutputPin].uCNotOveried = 0x80;
		break;
		case TYPE_PORT_B:
	    p->p_data         = (uint32_t*)&tOSlave_OutputData_Ctrl.output_b.port;
		  TPortControl_B[OutputPin].uCNotOveried = 0x80;
		break;
		case TYPE_PORT_C:
	    p->p_data         = (uint32_t*)&tOSlave_OutputData_Ctrl.output_c.port;
		  TPortControl_C[OutputPin].uCNotOveried = 0x80;
		break;
	}
	//tOutputOverride.Output.ui32data |= p->uiControlMask;
	
	uC_BtLed++;
}
/**************************
** @brief 
** @param
** @retval
****************************/
void sIR_Ctrl_Add(TIRx_Typedef *p ,uint16_t RxBitsMask ,uint16_t TxOutputPort , uint16_t TxOutputPin ,uint16_t MaxSetDelay)
{
	
	p->RxBitsMask = RxBitsMask;

	p->TxOutputPort = TxOutputPort;
	p->TxOutputPin  = TxOutputPin;
	p->TxDelay  		= MaxSetDelay;
	p->logicON      = 0;
	 
	p->uiControlMask  = IOGetOutput_BitsMask(TxOutputPort,TxOutputPin);
	
	 switch(TxOutputPort)
	{
		case TYPE_PORT_A:
	    p->p_data         = (uint32_t*)&tOSlave_OutputData_Ctrl.output_a.port;
		  TPortControl_A[TxOutputPin].uCNotOveried = 0x80;
		break;
		case TYPE_PORT_B:
	    p->p_data         = (uint32_t*)&tOSlave_OutputData_Ctrl.output_b.port;
		  TPortControl_B[TxOutputPin].uCNotOveried = 0x80;
		break;
		case TYPE_PORT_C:
	    p->p_data         = (uint32_t*)&tOSlave_OutputData_Ctrl.output_c.port;
		  TPortControl_C[TxOutputPin].uCNotOveried = 0x80;
		break;
	}
	
	p->Tx_uC_Count 	= 0;
	p->TxCountFail 	= 0;
	p->uC_TxOn_Ok 	= 0;
	p->Rx_uC_Count	= 0;
	uC_BtIR++;
}
/**************************
** @brief  Button & Led Control Event
** @param  pButtonled
** @retval 10ms
****************************/
static __inline void vButton_LED_Ctrl(void)
{
	uint8_t i = 0;
	
	if(uC_BtLed == 0 || pButtonled == NULL)
		return;
	
	if(uC_Led_Count < 15)
		uC_Led_Count++;
	else
	{
		uC_Led_Count  = 0;
		uLed_State ^= 1;
	}
	
	uint32_t *p_data = NULL;
	
	///////////////////////////////////
	///////////////////////////////////
	for(i = 0 ;i < uC_BtLed ;i++)
	{
		 p_data = pButtonled[i].p_data;
		
		if(IOREADINPUT_BITS(pButtonled[i].InputBitsMask) || ((p_data != NULL) && (((*p_data >> (pButtonled[i].OutputPin*2)) & 0x03) == 0x02)) ) //tInputStatus.Input.uiport & pButtonled[i].BitsMask)
		{
				//////// Toggle State ////////
			IOWRITE_OUT_PIN(pButtonled[i].OutputPort, pButtonled[i].OutputPin , uLed_State);
			 
			//tIStatus_Ctrl.Input.uiport |= pButtonled[i].InputBitsMask;
			
		}
		else if(((p_data != NULL) && ((*p_data >> (pButtonled[i].OutputPin*2)) & 0x03) == 0x01))//tOutputComCtrl.Output.ui32data & pButtonled[i].uiControlMask)   // Master Remote Output Override
		{
			//////// ON State ////////
			IOWRITE_OUT_PIN(pButtonled[i].OutputPort, pButtonled[i].OutputPin , 1);
			//tIStatus_Ctrl.Input.uiport |= pButtonled[i].InputBitsMask;
		}
		else
		{
			//////// OFF State ////////
			pButtonled[i].uC_State = 0;
			
			//tIStatus_Ctrl.Input.uiport &= ~(pButtonled[i].InputBitsMask);
			
			IOWRITE_OUT_PIN(pButtonled[i].OutputPort, pButtonled[i].OutputPin , 0);
		}
		
	}
	
	
}

/**************************
** @brief 	IR Control Tx Read back form rx the door IR Control
** @param  	pIRDoor
** @retval	10ms
****************************/
static __inline void vIR_Ctrl(void)
{
	uint8_t i = 0;

	if(pIRDoor == NULL || uC_BtIR == 0)
		return;
	
	uint32_t *p_data = NULL;
	
	for(i = 0 ;i < uC_BtIR ;i++)
	{
//			p_data = pIRDoor[i].p_data;
//		
//				///if Overide Off Tx ///
//			if((((*p_data >> (pIRDoor[i].TxOutputPin*2)) & 0x03) == 0x00))
//			{
//				// Tx Off
//				IOWRITE_OUT_PIN(pIRDoor[i].TxOutputPort, pIRDoor[i].TxOutputPin,0);
//				// Rx Off
//				tInputStatus.Input.uiport     |= (1 << pIRDoor[i].RxBitsMask);
//				
//				pIRDoor[i].uC_TxOn_Ok  = 0;
//				pIRDoor[i].Tx_uC_Count = 0;
//				pIRDoor[i].Rx_uC_Count = 0;
//				pIRDoor[i].TxCountFail = 0;
//				pIRDoor[i].TxLDeb      = 0;
//				
//				continue;
//			}
		
				/// Control Tx Rx ///
				if(pIRDoor[i].uC_TxOn_Ok == 0)
				{
						pIRDoor[i].Rx_uC_Count = 0;
					
					 if(pIRDoor[i].Tx_uC_Count < pIRDoor[i].TxDelay) //TX off times
					 {
							pIRDoor[i].Tx_uC_Count++;
						 
#if 1			
						  if(!port_Read_Input_Pin(pIRDoor[i].RxBitsMask))
							{
								if(pIRDoor[i].TxCountFail < pIRDoor[i].TxDelay-5)
									 pIRDoor[i].TxCountFail++; 
								else 
								{
									 //port_StatusLed_Write(0);
										pIRDoor[i].TxLDeb = 0;
										
								}
							}

#endif
					 }
					 else
					 {
							IOWRITE_OUT_PIN(pIRDoor[i].TxOutputPort, pIRDoor[i].TxOutputPin,1);
						
							pIRDoor[i].uC_TxOn_Ok  = 1;
					 }
					 
				}
				else
				{
					 pIRDoor[i].Tx_uC_Count = 0;
					
					
					 if(pIRDoor[i].Rx_uC_Count < pIRDoor[i].TxDelay)
							pIRDoor[i].Rx_uC_Count++;
					 else
					 {
							if(!port_Read_Input_Pin(pIRDoor[i].RxBitsMask) &&(pIRDoor[i].TxCountFail == 0))//IOREADINPUT_BITS(pIRDoor[i].RxBitsMask))
							{	
 
									 //port_StatusLed_Write(1);
								  if(pIRDoor[i].Rx_uC_Count > 5 )
								  {
									 //pIRDoor[i].TxCountFail = 0;
								   if(pIRDoor[i].TxLDeb < 2)
										  pIRDoor[i].TxLDeb++;
								    else{
											
											tInputStatus.Input.uiport     |= (1 << pIRDoor[i].RxBitsMask);
										}
									}
									 //Door Close
									 pIRDoor[i].RxDelay = 0;
									
								   //tInputStatus.Input.uiport     |= (1 << pIRDoor[i].RxBitsMask);
								
							}
							else
							{
								pIRDoor[i].TxLDeb = 0;
								 //Door Open
								 //5Times  * 200ms Active signal 1s 
								 if(pIRDoor[i].Rx_uC_Count > 5 )
								 {
									 if(pIRDoor[i].RxDelay < 2) //10
											pIRDoor[i].RxDelay++;
									 else{
										  
											if(pIRDoor[i].TxCountFail > 0)
											   pIRDoor[i].TxCountFail = 0;
											
										   //port_StatusLed_Write(0); //port_StatusLed_Write(0);
											 tInputStatus.Input.uiport 			&= ~(1 << pIRDoor[i].RxBitsMask);
									 }
							   }
							}
	
							IOWRITE_OUT_PIN(pIRDoor[i].TxOutputPort, pIRDoor[i].TxOutputPin, 0);
				
							pIRDoor[i].uC_TxOn_Ok  = 0;
							
						 
					 }
				}
			
	} 
	
	

}
/**************************
** @brief Status Update to Common  
** @param
** @retval
****************************/
static __inline void vStatus_Update(void)
{
//	int i = 0;
//	uint16_t tmp = 0;
//	
//	 ///////Copy Status Comm Status  ///////
//	for(i = 0; i < MAX_INPUT_LOGIC ;i++)
//	{
//		if(tIStatus_Ctrl_Mask.Input.uiport & (1<<i))
//		{
//			 //// Update By Control ///
//		}
//		else //Copy bit
//		{
//			if(tInputStatus.Input.uiport & (1<<i))
//			{
//				tIStatus_Ctrl.Input.uiport |= (1<<i);
//			}
//			else
//			{
//				tIStatus_Ctrl.Input.uiport &= ~(1<<i);
//			}
//			
//		}

//	}	
	 
	 
	
	
	
}


//END OF FILE
