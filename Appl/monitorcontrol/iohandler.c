/**
  ******************************************************************************
  * @file    iohandler.c
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

/*******************************************************************************/
/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "Platform.h"   
#include "rte/rte.h" 
#include "slavecontrol/slave_ctrl.h"
/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/


/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
 TInput_Typedef  tInputMod[MAX_INPUT_LOGIC];
 
 TInputStatus_Typedef  		tInputStatus;       //Internal Status; 
 
 TOutputControl_Typedef   tOutputCtrl;
 
 TOutputStatus_Typedef 		tOutputComCtrl;
 
 TPortControl_Typedef     TPortControl_A[MAX_OUTPUT_A];
 TPortControl_Typedef     TPortControl_B[MAX_OUTPUT_B];
 TPortControl_Typedef     TPortControl_C[MAX_OUTPUT_C];

 uint16_t DDdata = 0;
/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/
void InputProcess(TInput_Typedef *thisInput);
	
static __inline void InputDet_State(void);

static uint8_t uC_InputCount = 0,uC_Blikstate;
static uint16_t uiBilkCount = 0;


/**************************
** @brief 
** @param
** @retval
****************************/
void IODefault_Init(void)
{
	//uint16_t InAddCount = (MAX_INPUT_LOGIC - uC_InputCount);
	
	uint8_t i  = 0;
	
	for(i = 0;i < MAX_INPUT_LOGIC;i++)
	{
		if(tInputMod[i].uC_Resev != 1)
		{
			//IOAddControl(i,100,100,1)
		}
	}
	
}
/**************************
** @brief 
** @param
** @retval
****************************/
void IOAddControl(uint16_t uipin,uint16_t dedSet,uint16_t dedReset, uint8_t Invert)
{
	if(uipin > MAX_INPUT_LOGIC)
		 return;
	
	tInputMod[uipin].uiPIN 					= uipin;
	tInputMod[uipin].uC_Resev				= 1;
	tInputMod[uipin].uiDebMaxSet		= dedSet;
	tInputMod[uipin].uiDebMaxReset 	= dedReset;
	tInputMod[uipin].ucInvert 			= Invert;
	
	uC_InputCount++;
}
/**************************
** @brief 
** @param
** @retval
****************************/
void IOInputSetConfig(TInput_Typedef *p ,
	                    uint16_t uipin,uint16_t dedSet,uint16_t dedReset,
                      uint8_t Invert)
{
	p->uiPIN 					= uipin;
	p->uC_Resev       = 1;
	p->uiDebMaxSet   	= dedSet;
	p->uiDebMaxReset 	= dedReset;
	p->ucInvert 			= Invert;
	uC_InputCount++;
}
/**************************
** @brief 
** @param
** @retval
****************************/
uint8_t IORead_SlaveMode(void)
{
	uint8_t Addr = 0;

#if defined(SL_HPT_HK_MOD)	
	
	if(port_Read_pin(GPIO_PORT_ADDR_1, GPIO_PIN_ADDR_1) == 0){
		 Addr  = 0x1;
	}
		
	if(port_Read_pin(GPIO_PORT_ADDR_2, GPIO_PIN_ADDR_2) == 0){
		 Addr |= 0x2;
	}
	
	if(port_Read_pin(GPIO_PORT_ADDR_3, GPIO_PIN_ADDR_3) == 0){
		 Addr |= 0x4;
	}

#else //defined(SL_NDO_TURCK_MOD)
	
	if(port_Read_pin(GPIO_PORT_ADDR_1, GPIO_PIN_ADDR_1) == 0){
		 Addr  = 0x1;
	}

	if(port_Read_pin(GPIO_PORT_ADDR_2, GPIO_PIN_ADDR_2) == 0){
		 Addr = 0x2;
	}
	
	if(port_Read_pin(GPIO_PORT_ADDR_3, GPIO_PIN_ADDR_3) == 0){
		 Addr = 0x3;
	}
	
	
		
#endif
	
	return Addr;
}

/**************************
** @brief 
** @param
** @retval
****************************/
void IOInput_Handler(void)
{
	 InputDet_State();
}
/**************************
** @brief 
** @param
** @retval
****************************/
void CommonIOControl(TPortControl_Typedef *pPortCtrl ,uint16_t Port,uint16_t pin)
{
		switch((uint8_t)pPortCtrl->tECtrl_Status)
		{ 
			case OUTPUT_OFF:
				 IOWRITE_OUT_PIN(Port, pin , 0x0);
			if(pPortCtrl->uC_Short)
				 pPortCtrl->uC_Short   = 0;
				break;
			case OUTPUT_ON:
				 IOWRITE_OUT_PIN(Port, pin , 0x1);
				break;
			case OUTPUT_MEDIUM_BLINK:
				 IOWRITE_OUT_PIN(Port, pin , uC_Blikstate);
				break;
			case OUTPUT_SINGLE_SHOT:
				
				 if(pPortCtrl->uC_Short == 0)
				 {
					 pPortCtrl->uC_Short  		= 1;
					 pPortCtrl->CounterClear 	= 100; //ms
					 IOWRITE_OUT_PIN(Port, pin , 0x1);

				 }
				
			
				break;
		}
}
/**************************
** @brief 
** @param
** @retval
****************************/
void IOOutputCtrl_Handler(void)
{
	uint8_t 	i 	= 0;
	uint16_t 	bit = 0x0;
	uint32_t *p_data ;//= NULL;
	
  if(uiBilkCount < 2000)
		uiBilkCount++;
	else
	{
		uiBilkCount  = 0;
		uC_Blikstate ^= 1;
	}
	
	//////////////// PORT A //////////////////////
	p_data = (uint32_t*)tOSlave_OutputData_Ctrl.output_a.port;
	
	//////// ON/OFF ///////////
	for(i = 0;i < MAX_OUTPUT_A;i++)
	{
		TPortControl_A[i].tECtrl_Status =(TIOStatus_TypeEnum)( (*p_data >> (i*2)) & 0x03);
		
		if(TPortControl_A[i].uCNotOveried == 0x80)
		{
			continue;
		}
		else
		{
			CommonIOControl(&TPortControl_A[i],TYPE_PORT_A,i);
		}
		
	}
	//////////////////////////////////////////////
	//////////////// PORT B //////////////////////
	p_data = (uint32_t*)&tOSlave_OutputData_Ctrl.output_b.port;
	
	for(i = 0;i < MAX_OUTPUT_B;i++)
	{
		TPortControl_B[i].tECtrl_Status = (TIOStatus_TypeEnum)((*p_data >> (i*2)) & 0x03);
		
		if(TPortControl_B[i].uCNotOveried == 0x80)
		{
			continue;
		}
		else
		{
			CommonIOControl(&TPortControl_B[i],TYPE_PORT_B,i);
		}
	}
	//////////////////////////////////////////////
	//////////////// PORT C //////////////////////
	p_data = (uint32_t*)&tOSlave_OutputData_Ctrl.output_c.port;
	
	for(i = 0;i < MAX_OUTPUT_C;i++)
	{
		TPortControl_C[i].tECtrl_Status = (TIOStatus_TypeEnum)((*p_data >> (i*2)) & 0x03);
		
		if(TPortControl_C[i].uCNotOveried == 0x80)
		{
			continue;
		}
		else
		{
			CommonIOControl(&TPortControl_C[i],TYPE_PORT_C,i);
		}
	}
	//////////////////////////////////////////////
}


/**************************
** @brief 
** @param
** @retval
****************************/
void IOOutputClear_Handler(void)
{
	uint8_t i = 0;
	
  for(i = 0;i < MAX_OUTPUT_A;i++)
	{
		if(TPortControl_A[i].uC_Short){
			if(TPortControl_A[i].CounterClear > 0)
				 TPortControl_A[i].CounterClear--;
			else
			{
				IOWRITE_OUT_PIN(TYPE_PORT_A, i , 0x0);
				TPortControl_A[i].CounterClear = 0;
			}
		}
	}
	
	for(i = 0;i < MAX_OUTPUT_B;i++)
	{
		if(TPortControl_B[i].uC_Short){
			if(TPortControl_B[i].CounterClear > 0)
				 TPortControl_B[i].CounterClear--;
			else
			{
				IOWRITE_OUT_PIN(TYPE_PORT_B, i , 0x0);
				TPortControl_B[i].CounterClear = 0;
			}
		}
	}
	
	for(i = 0;i < MAX_OUTPUT_C;i++)
	{
		if(TPortControl_C[i].uC_Short){
			if(TPortControl_C[i].CounterClear > 0)
				 TPortControl_C[i].CounterClear--;
			else
			{
				IOWRITE_OUT_PIN(TYPE_PORT_C, i , 0x0);
				TPortControl_C[i].CounterClear = 0;
			}
		}
	}
}
/**************************
** @brief 
** @param
** @retval
****************************/
void IOOutputC_Handler(void)
{
	uint8_t i = 0;
	uint16_t data = 0;
	uint16_t bit = 0x0;
	
	for(i = 0;i < 7;i++)
	{
		bit = 0;
		data = (uint16_t)(tOutputComCtrl.Output.ui32data >> 16);
		bit =   (1 << i);
		//DDdata = data && bit;
		 
			if(data & bit) 
			{
				if(tOutputCtrl.tDeboud[i+17].uC_CountSet  
					 < tOutputCtrl.tDebSetting[i+17].uC_CountSet){
						 tOutputCtrl.tDeboud[i+17].uC_CountSet++;
					 }else{
						 
						   //IO Set On
						   IOWRITE_OUT_PIN(TYPE_PORT_C, i , 0x1);
								
						   data = 0;
						   data = (1<<(i+16));
							 tOutputCtrl.tStatusOutput.Output.ui32data |= data;
					 }
			
			}	
			else{
				
					if(tOutputCtrl.tDeboud[i+17].uC_CountReSet  
					 < tOutputCtrl.tDebSetting[i+17].uC_CountReSet){
						 tOutputCtrl.tDeboud[i+17].uC_CountReSet++;
					 }else{
						 
							IOWRITE_OUT_PIN(TYPE_PORT_C, i , 0x0);
								
						  data = 0;
						  data = (1<<(i+16));
						  tOutputCtrl.tStatusOutput.Output.ui32data  &= ~(data);
								//IO Clear
							
					 }
			}
			
	}
}
/**************************
** @brief 
** @param
** @retval
****************************/

static __inline void InputDet_State(void)
{
	uint8_t i = 0;
	
	if(uC_InputCount == 0)
		return;
	
	for(i = 0; i< uC_InputCount ;i++)
	{
		InputProcess(&tInputMod[i]);
	}
	
}
/**************************
** @brief 
** @param
** @retval
****************************/
void InputProcess(TInput_Typedef *thisInput)
{
	uint16_t upin = thisInput->uiPIN;
	
	if(thisInput->ucInvert)
	{
		if(port_Read_Input_Pin(upin) == 0)
		{
			 thisInput->tDebCount.uC_CountReSet = 0;
			
			 if(thisInput->tDebCount.uC_CountSet < thisInput->uiDebMaxSet)
					thisInput->tDebCount.uC_CountSet++;
			 else
			 {
				 tInputStatus.Input.uiport |= (1<<upin);
			 }
			 
		}else{
			
			 /////// Low  ///////
			thisInput->tDebCount.uC_CountSet = 0;
			
			if(thisInput->tDebCount.uC_CountReSet < thisInput->uiDebMaxReset)
					thisInput->tDebCount.uC_CountReSet++;
			 else
			 {
				 tInputStatus.Input.uiport &= ~(1 << upin);
			 }
			 
		}
	}
	/////////////////// Not Invert Logic /////////
	else{
		///////// High ////////
		if(port_Read_Input_Pin(upin))
		{
			 thisInput->tDebCount.uC_CountReSet = 0;
			
			 if(thisInput->tDebCount.uC_CountSet < thisInput->uiDebMaxSet)
					thisInput->tDebCount.uC_CountSet++;
			 else
			 {
				 tInputStatus.Input.uiport |= (1<<upin);
			 }
			 
		}else{
			
			 /////// Low  ///////
			thisInput->tDebCount.uC_CountSet = 0;
			
			if(thisInput->tDebCount.uC_CountReSet < thisInput->uiDebMaxReset)
					thisInput->tDebCount.uC_CountReSet++;
			 else
			 {
				 tInputStatus.Input.uiport &= ~(1 << upin);
			 }
			 
		}
  }
}

/**************************
** @brief 
** @param
** @retval
****************************/
void IOWrite_Output(uint8_t type,uint16_t Pin,uint8_t data)
{
	  switch(type)
		{
			case TYPE_PORT_A:	
				RTE_PORT_BIT_OUTA_(Pin,data);
				break;
			case TYPE_PORT_B:
				RTE_PORT_BIT_OUTB_(Pin,data);
				break;
			case TYPE_PORT_C:
				RTE_PORT_BIT_OUTC_(Pin,data);
				break;
			
			 default:
				break;
		}
		
}
/**************************
** @brief 
** @param
** @retval
****************************/
uint32_t  IOGetOutput_BitsMask(uint8_t type,uint16_t Pin)
{ 
	uint32_t numberbits  = 0 ;
	
	 switch(type)
		{
			case TYPE_PORT_A:	
				numberbits = (1 << Pin);
				break;
			
			case TYPE_PORT_B:
			  numberbits = (1 << (Pin+8));
				break; 
			
			case TYPE_PORT_C:
				numberbits = (1 << (Pin+17));
				break;
			
			 default:
				break;
		}
		
		 return numberbits;
}

//END OF FILE
