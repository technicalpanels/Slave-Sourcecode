/**
  ******************************************************************************
  * @file    Main.c
  * @author  Kittanadon
  * @version V2.0.1
  * @date    17-OCT-2016
  * @brief   This file is MCU Initial Hardware layer
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
#include "usblib/usblib.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
 

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
uint32_t ui32SysClock,ui32PLLRate;

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
 
 
/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/
	
	
/**************************
** @brief 
** @param
** @retval
****************************/
void DEV_Clock_Init(void)
{
    //FPUEnable(); 
    //FPULazyStackingEnable();
	
//	MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
//            								  SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
//											  SYSCTL_CFG_VCO_480),
//            								  configCPU_CLOCK_HZ);
	
    ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                           SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                           SYSCTL_CFG_VCO_480),  ( ( unsigned long ) 120000000 ));
	 
	  
	
	   // Enable all the GPIO peripherals.
    //
	  //SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);

	  ROM_SysTickPeriodSet(ui32SysClock / TICKS_PER_SECOND);
		
#if WDT_ON	

		MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
	 
		// Initialize the watchdog timer.
		WatchdogReloadSet(WATCHDOG0_BASE, ui32SysClock/4);
		// Enable the reset.
		WatchdogResetEnable(WATCHDOG0_BASE);
		// Enable the watchdog timer.
		WatchdogEnable(WATCHDOG0_BASE);
		
#endif
		MAP_GPIOPinConfigure(GPIO_PA0_CAN0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_CAN0TX);
	
    MAP_GPIOPinTypeCAN(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
}
/**************************
** @brief All Initial for Device TM4C129x
** @param
** @retval
****************************/
void DEV_IO_Init(void)
{


}







//End of file 
