/**
  ******************************************************************************
  * @file    Main.c
  * @author  Kittanadon Keawratchakit
  * @version V2.0.1
  * @date    17-OCT-2016
  * @brief   This file is main applications slave Control Module 
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
#include "inc/hw_nvic.h"
#include "rte/rte.h" 
#include "slavecontrol/slave_ctrl.h"
#include "canbuscontrol/commandctrl.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
 extern TCommand_Typedef 	tCanCommand;
/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
 uint32_t key __attribute__( ( section("RamKeys"),zero_init) );
 
 
volatile uint32_t g_ulLastTick;
//volatile uint8_t  g_ulSysTickCount = 0;
volatile uint8_t  uC_bTick = 0;


/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
static uint16_t uC_CountTimer1ms = 0,uC_CountTimer10ms = 0,uC_CountTimer100ms = 0;
#ifdef TEST_ACTUTOR
static uint16_t ui_MainLedTick = 0,ui_MainLedTick_2 = 0,uc_delay = 0,uc_delay2 = 0;
#endif
static uint8_t OwnAddress = 0;

/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/
static void Task_1ms(void);
static void Task_10ms(void);
static void Task_100ms(void);

/**
  * @brief  System delay us 
  * @param  None      
  * @retval None
  */
void __delay_us(volatile uint32_t times)
{
	volatile uint32_t i;
	
	while(times--)
	{
		i = 18;
		while(i--);
	}
}
/**
  * @brief  System delay us 
  * @param  None      
  * @retval None
  */
void __delay_ms(volatile uint32_t times)
{
	__delay_us(times*1000); 
}
/**************************
** @brief 
** @param
** @retval
****************************/
void SysTickIntHandler(void)
{
	uC_bTick = 1;
	
}

/**************************
** @brief 
** @param
** @retval
****************************/
static __inline void Bsw_Init(void)
{
	 DEV_Clock_Init(); 
	
	 port_Init();
	
	 /// Check Slave ID Make sure Not 0 ///
	 do{
		 
	  OwnAddress = App_Slave_Init();
		 
	 }while(OwnAddress == 0);
	 
	 tInputStatus.Input.uiport = 0;
	 
	 //Some delay statrup 
	 __delay_ms(50);
	 
   can_Init(OwnAddress); 
}
/**************************
** @brief 
** @param
** @retval
****************************/
int main (void)
{
	uint8_t  btest = 0;
	
	 HWREG(NVIC_VTABLE) = 0x00010000;
	
	/**************************/
	/*  InItial Applications  */
	/**************************/
	__disable_irq(); //Diable All Interrupt
	
	 Command_Init();
	
	  Bsw_Init();
	
	__enable_irq(); //Enable All Interrupt
	
		 
	/**************************/
	
	while(1)
	{
		
#if WDT_ON
		//WDT Reset 1/4 ms 250ms
	  WatchdogReloadSet(WATCHDOG0_BASE, ui32SysClock/4);
#endif	
		 //System tick every 100us
		 if(uC_bTick )
		 {

			 vOdmeter();  
			 
			 IOInput_Handler();
			
			 IOOutputCtrl_Handler();
			 
			 Task_1ms();
			 
			 uC_bTick = 0;
			 
		 }
		 
	}
	
}
/**************************
** @brief 
** @param
** @retval
****************************/
static void Task_1ms(void)
{
	uC_CountTimer1ms++;
	switch(uC_CountTimer1ms)
	{
		case 1:
			
#ifdef TEST_ACTUTOR			
			if(ui_MainLedTick < 200){
				 ui_MainLedTick++;
				
				 IOWRITE_OUT_PIN(TYPE_PORT_C, 4, 1);
				 IOWRITE_OUT_PIN(TYPE_PORT_C, 6, 0);
				 uc_delay = 0;
				 ui_MainLedTick_2 = 0;
			}
			else
			{
				IOWRITE_OUT_PIN(TYPE_PORT_C, 4, 0);
				
				if(uc_delay < 1500)
					 uc_delay++;
				else{

					if(ui_MainLedTick_2 < 200){
						 ui_MainLedTick_2++;
						 uc_delay2 = 0;
						IOWRITE_OUT_PIN(TYPE_PORT_C, 6, 1);
					}
					else
					{
							if(uc_delay2 < 1500)
								 uc_delay2++;
							else
							{
								ui_MainLedTick = 0;
								
							}
							
						IOWRITE_OUT_PIN(TYPE_PORT_C, 6, 0);
					}
			 }

			}
	#endif
			
			break;
		
		case 2:
			IOOutputClear_Handler();
			break;
		
		case 3:
			break;
		
		case 4:
			App_Slave_Ctrl();
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
			
			vWiegand_Task();
		
			uC_CountTimer1ms = 0;
		  Task_10ms();
			break;
	}
	
}
/**************************
** @brief 
** @param
** @retval
****************************/
static void Task_10ms(void)
{
	uC_CountTimer10ms++;
	switch(uC_CountTimer10ms)
	{
		case 1:
			
			break;
		
		case 2:
			
			break;
		
		case 3:
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
			
			uC_CountTimer10ms = 0;
		
		  Task_100ms();
		
			break;
		
		//// Error Case ///
		 default:
			uC_CountTimer10ms  = 0;
			break;		
	}
}
/**************************
** @brief 
** @param
** @retval
****************************/
static void Task_100ms(void)
{
	uC_CountTimer100ms++;
	switch(uC_CountTimer100ms)
	{
		case 1:
			can_ResetError();
			break;
		
		case 2:
			
			break;
		
		case 3:
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
			
			uC_CountTimer100ms = 0;
			break;
		
	}
	
}
/**************************
** @brief 
** @param
** @retval
****************************/
void WatchdogIntHandler(void)
{
	  ROM_WatchdogIntClear(WATCHDOG0_BASE);
}
//END OF FILE
