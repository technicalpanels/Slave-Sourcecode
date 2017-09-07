/**
  ******************************************************************************
  * @file    gpio_app.c
  * @author  Kittanadon Keawratchakit
  * @version V2.0.1
  * @date    17-OCT-2016
  * @brief   This file is GPIO Control for Slave in port -> bsw Layer
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

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
 #define   INPUT_PIN_MAX  		12
 #define   OUTPUT_A_PIN_MAX  	 8
 #define   OUTPUT_B_PIN_MAX  	 9
 #define   OUTPUT_C_PIN_MAX  	 7
 
#define  BSW_PORTA_PIN_WRITE(Pin,Dat)   port_Write_pin(tOutput_A[Pin].base,tOutput_A[Pin].pin,Dat)
#define  BSW_PORTB_PIN_WRITE(Pin,Dat)   port_Write_pin(tOutput_B[Pin].base,tOutput_B[Pin].pin,Dat)
#define  BSW_PORTC_PIN_WRITE(Pin,Dat)   port_Write_pin(tOutput_C[Pin].base,tOutput_C[Pin].pin,Dat)

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
 
 /////// Input Map pin ////////////
static const THAL_GPIO_Typedef tInput[] = {
	
	{ GPIO_PORTL_BASE, GPIO_PIN_1}, // IOPortA1 PL1
	{ GPIO_PORTL_BASE, GPIO_PIN_2}, // IOPortA2 PL2 
	{ GPIO_PORTL_BASE, GPIO_PIN_3}, // IOPortA3 PL3
	{ GPIO_PORTP_BASE, GPIO_PIN_0}, // IOPortA4 PP0
	{ GPIO_PORTQ_BASE, GPIO_PIN_0}, // IOPortA5 PQ0
	{ GPIO_PORTQ_BASE, GPIO_PIN_1}, // IOPortA6 PQ1
	{ GPIO_PORTP_BASE, GPIO_PIN_5}, // IOPortA7 PP5
	{ GPIO_PORTP_BASE, GPIO_PIN_1}, // IOPortA8 PP1
	{ GPIO_PORTQ_BASE, GPIO_PIN_2}, // IOPortA9 PQ2
	{ GPIO_PORTQ_BASE, GPIO_PIN_4}, // IOPortA10 PQ4
	{ GPIO_PORTP_BASE, GPIO_PIN_2}, // IOPortA11 PP2
	{ GPIO_PORTQ_BASE, GPIO_PIN_3}  // IOPortA12 PQ3
	
};

 /////// OutputA Map pin ////////////
static const THAL_GPIO_Typedef tOutput_A[] = {
	
	{ GPIO_PORTH_BASE, GPIO_PIN_0},	// OutPortA1 PH0
	{ GPIO_PORTA_BASE, GPIO_PIN_5},	// OutPortA2 PA5
	{ GPIO_PORTP_BASE, GPIO_PIN_4},	// OutPortA3 PP4
	{ GPIO_PORTG_BASE, GPIO_PIN_0},	// OutPortA4 PG0
	{ GPIO_PORTF_BASE, GPIO_PIN_1},	// OutPortA5 PF1
	{ GPIO_PORTD_BASE, GPIO_PIN_4},	// OutPortA6 PD4
	{ GPIO_PORTL_BASE, GPIO_PIN_0},	// OutPortA7 PL0
	{ GPIO_PORTF_BASE, GPIO_PIN_2}	// OutPortA8 PF2
	
};

 /////// OutputB Map pin ////////////
static const THAL_GPIO_Typedef tOutput_B[] = {
	{ GPIO_PORTM_BASE, GPIO_PIN_2},	// OutPortB1 PM2
	{ GPIO_PORTH_BASE, GPIO_PIN_3},	// OutPortB2 PH3
	{ GPIO_PORTM_BASE, GPIO_PIN_1},	// OutPortB3 PM1
	{ GPIO_PORTK_BASE, GPIO_PIN_4},	// OutPortB4 PK4
	{ GPIO_PORTN_BASE, GPIO_PIN_1},	// OutPortB5 PN1
	{ GPIO_PORTN_BASE, GPIO_PIN_0},	// OutPortB6 PK5 --- OutPortB9 PN0
	{ GPIO_PORTL_BASE, GPIO_PIN_4},	// OutPortB7 PL4 --- OutPortB7 PE4
	{ GPIO_PORTE_BASE, GPIO_PIN_4},	// OutPortB8 PE4 --- OutPortB8 PL4
	{ GPIO_PORTK_BASE, GPIO_PIN_5}	// OutPortB9 PN0 --- OutPortB6 PK5
};
 /////// OutputC Map pin ////////////
static const THAL_GPIO_Typedef tOutput_C[] = {
	{ GPIO_PORTB_BASE, GPIO_PIN_5},	// OutPortC1 PB5
	{ GPIO_PORTB_BASE, GPIO_PIN_4},	// OutPortC2 PB4
	{ GPIO_PORTE_BASE, GPIO_PIN_3},	// OutPortC3 PE3
	{ GPIO_PORTE_BASE, GPIO_PIN_1},	// OutPortC4 PE1
//	{ GPIO_PORTD_BASE, GPIO_PIN_7},	// OutPortC5 PD7
	{ GPIO_PORTK_BASE, GPIO_PIN_2}, // OutPortC5 PK2
	{ GPIO_PORTE_BASE, GPIO_PIN_0},	// OutPortC6 PE0
	{ GPIO_PORTG_BASE, GPIO_PIN_1}	// OutPortC7 PG1
};


/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
volatile uint8_t  g_ulSysTickCount = 0;

/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/
 
 /**************************
** @brief 
** @param
** @retval
****************************/
void port_Init(void)
{
	uint8_t i = 0;
	
  /* GPIO Initial */
	DEV_IO_Init();
	

	/* Intialize Input Port. */
	for (i=0; i< INPUT_PIN_MAX; i++) {
		
		MAP_GPIOPinTypeGPIOInput(tInput[i].base, tInput[i].pin);
		MAP_GPIOPadConfigSet(tInput[i].base, tInput[i].pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_OD);
		
	}
	
	/* Initialize Output Port A. */
	for (i=0; i < OUTPUT_A_PIN_MAX; i++) {
		MAP_GPIOPinTypeGPIOOutput(tOutput_A[i].base, tOutput_A[i].pin);
		MAP_GPIOPadConfigSet(tOutput_A[i].base, tOutput_A[i].pin, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
	} 
	
	/* Initialize Output Port B. */
	for (i=0; i < OUTPUT_B_PIN_MAX; i++) {
		MAP_GPIOPinTypeGPIOOutput(tOutput_B[i].base, tOutput_B[i].pin);
		MAP_GPIOPadConfigSet(tOutput_B[i].base, tOutput_B[i].pin, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
	}
	
	/* Initialize OUTPUT_C_PIN_MAX Port C. */
	for (i=0; i < OUTPUT_C_PIN_MAX; i++) {
		MAP_GPIOPinTypeGPIOOutput(tOutput_C[i].base, tOutput_C[i].pin);
		MAP_GPIOPadConfigSet(tOutput_C[i].base, tOutput_C[i].pin, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
	}
	
	/* ID-SW. */
	MAP_GPIOPinTypeGPIOInput(GPIO_PORT_ADDR_1, GPIO_PIN_ADDR_1);
	MAP_GPIOPadConfigSet(GPIO_PORT_ADDR_1, GPIO_PIN_ADDR_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
	MAP_GPIOPinTypeGPIOInput(GPIO_PORT_ADDR_2, GPIO_PIN_ADDR_2);
	MAP_GPIOPadConfigSet(GPIO_PORT_ADDR_2, GPIO_PIN_ADDR_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
	MAP_GPIOPinTypeGPIOInput(GPIO_PORT_ADDR_3, GPIO_PIN_ADDR_3);
	MAP_GPIOPadConfigSet(GPIO_PORT_ADDR_3, GPIO_PIN_ADDR_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
	/* STATUS-LED. */
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORT_STULED, GPIO_PIN_STULED);
	MAP_GPIOPadConfigSet(GPIO_PORT_STULED, GPIO_PIN_STULED, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_OD);
	 
	///// Timer tick enable ///
  ROM_SysTickEnable();
  ROM_SysTickIntEnable();
	
}
 /**************************
** @brief 
** @param
** @retval
****************************/
uint8_t port_Read_pin(uint32_t port,uint32_t pin)
{
 	return (MAP_GPIOPinRead(port, pin));
}
 /**************************
** @brief 
** @param
** @retval
****************************/
uint8_t port_Read_Input_Pin(uint8_t pin)
{
	if(pin >= INPUT_PIN_MAX)
		 return 0;
	
	return port_Read_pin(tInput[pin].base ,tInput[pin].pin);
	
}
 /**************************
** @brief 
** @param
** @retval
****************************/
uint16_t port_Read_Input(void)
{
	uint8_t i = 0;
	uint16_t port = 0;
	
	for (i=0; i< INPUT_PIN_MAX; i++) {
		
		port  |= MAP_GPIOPinRead(tInput[i].base ,tInput[i].pin) << i;
		
	}
	
	 return port;
	
}
/**************************
** @brief 
** @param
** @retval
****************************/
void port_Write_pin(uint32_t port,uint32_t pin,uint8_t status)
{
  if(status){
		MAP_GPIOPinWrite(port, pin , pin);
	}
	else{
		MAP_GPIOPinWrite(port, pin , 0);
	}
}
/**************************
** @brief 
** @param
** @retval
****************************/
void portA_Write_pin(uint32_t pin,uint8_t status)
{
	if(pin >= OUTPUT_A_PIN_MAX)
		 return ;
	 
	BSW_PORTA_PIN_WRITE(pin,status);
}
/**************************
** @brief 
** @param
** @retval
****************************/
void portB_Write_pin(uint32_t pin,uint8_t status)
{
	if(pin >= OUTPUT_B_PIN_MAX)
		 return ;
		
	BSW_PORTB_PIN_WRITE(pin,status);
}
/**************************
** @brief 
** @param
** @retval
****************************/
void portC_Write_pin(uint32_t pin,uint8_t status)
{
	if(pin >= OUTPUT_C_PIN_MAX)
		 return ;
	
	BSW_PORTC_PIN_WRITE(pin,status);
	
}
/**************************
** @brief 
** @param
** @retval
****************************/
void port_StatusLed_Write(uint8_t status)
{
	if(status){
		port_Write_pin(GPIO_PORT_STULED, GPIO_PIN_STULED , GPIO_PIN_STULED);
	}
	else{
		port_Write_pin(GPIO_PORT_STULED, GPIO_PIN_STULED , 0);
	}
	
}
/**************************
** @brief 
** @param
** @retval
****************************/
void LED_Toggle(void)
{					
	g_ulSysTickCount ^= 1;		
	port_StatusLed_Write(g_ulSysTickCount);
	
}

//End of file 
