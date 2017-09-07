/**
  ******************************************************************************
  * @file    wiegand.c
  * @author  Kittanadon Keawratchakit
  * @version V2.0.1
  * @date    17-OCT-2016
  * @brief   This file is wiegand driver in basic software 
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
#include "wiegand/wiegand.h"
/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
#define WIEG_TIMEOUT									25
#define WIGE_BIT_26BIT_MAX						26
#define WIGE_BIT_34BIT_MAX						34
/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
static volatile uint32_t g_wieg_reading_data;
static volatile uint16_t g_wieg_current_bit;
static volatile uint16_t g_wieg_timeout;

uint16_t g_Wieg_ID = 0;
uint8_t  g_IS_Wieg_Enable = 0;
/*******************************************************************************
 * Local Function(private to module)
 ******************************************************************************/
static void app_io_wieg_handler(uint64_t data);

/**************************
** @brief 
** @param
** @retval
****************************/
void vWiegand_Init(void)
{
		/* Weigand D0. */
		MAP_GPIOIntTypeSet(GPIO_PORTQ_BASE, GPIO_INT_PIN_0, GPIO_FALLING_EDGE);
		MAP_GPIOIntEnable(GPIO_PORTQ_BASE, GPIO_PIN_0);
	
		MAP_IntPrioritySet(INT_GPIOQ0,0x30); 			// low priority
	
		MAP_IntEnable(INT_GPIOQ0);
		
		/* Weigand D1. */
		MAP_GPIOIntTypeSet(GPIO_PORTP_BASE, GPIO_INT_PIN_0, GPIO_FALLING_EDGE);
		MAP_GPIOIntEnable(GPIO_PORTP_BASE, GPIO_PIN_0);
	
	  MAP_IntPrioritySet(INT_GPIOP0,0x30); 			// low priority
		MAP_IntEnable(INT_GPIOP0);
	  
	  g_IS_Wieg_Enable = 1;
	
}
/**************************
** @brief 
** @param
** @retval
****************************/
static uint8_t bit_data(uint64_t data, uint8_t bit)
{
    if (((data >> bit) & 0x0000000000000001) != 0) {
        return 1;
    } else {
        return 0;
    }
}
/**************************
** @brief 
** @param
** @retval
****************************/
static uint8_t even_parity_check(uint64_t data, uint8_t len)
{
    uint8_t count = 0;
    uint8_t i = 0;

    for (i=0; i<len; i++) {
        if ((data & 0x0000000000000001) != 0) {
            count++;
        } else {
        }
        data >>= 1;
    }

    if ((count % 2) != 0) {
        /* Odd */
        return 0;
    } else {
        /* Even */
        return 1;
    }
}
/**************************
** @brief 
** @param
** @retval
****************************/
static uint8_t odd_parity_check(uint64_t data, uint8_t len)
{
    uint8_t count = 0;
    uint8_t i = 0;

    for (i=0; i<len; i++) {
        if ((data & 0x0000000000000001) != 0) {
            count++;
        }
        data >>= 1;
    }

    if ((count % 2) != 0) {
        /* Odd */
        return 1;
    } else {
        /* Even */
        return 0;
    }
}
/**************************
** @brief 
** @param
** @retval 1ms
****************************/
void vWiegand_Task(void)
{
	if(!g_IS_Wieg_Enable)
		 return;
	
	if (g_wieg_timeout > 0) {
		if (g_wieg_timeout > WIEG_TIMEOUT) { //25ms
			g_wieg_timeout = 0;
			/* Handle with g_wieg_reading_data, after handle please clear it. */
			
			/* Bit count must equal 26 or 34 and Parity check. */
			if (g_wieg_current_bit == WIGE_BIT_26BIT_MAX) {
				if ((bit_data(g_wieg_reading_data, 0) == 
						 even_parity_check(g_wieg_reading_data >> 1, 12)) &&
						(bit_data(g_wieg_reading_data, (WIGE_BIT_26BIT_MAX - 1)) == 
						 odd_parity_check(g_wieg_reading_data >> 13, 12))) {
							
					app_io_wieg_handler(g_wieg_reading_data);
				}
			} else if (g_wieg_current_bit == WIGE_BIT_34BIT_MAX) {
				if ((bit_data(g_wieg_reading_data, 0) == 
						 even_parity_check(g_wieg_reading_data >> 1, 16)) &&
						(bit_data(g_wieg_reading_data, (WIGE_BIT_34BIT_MAX - 1)) == 
						 odd_parity_check(g_wieg_reading_data >> 17, 16))) {
							
					app_io_wieg_handler(g_wieg_reading_data);
				}
			}
			
			
			g_wieg_reading_data = 0;
			g_wieg_current_bit = 0;
			
		} else {
			g_wieg_timeout += 1;
		}
	}
}
/**************************
** @brief 
** @param
** @retval
****************************/
static void app_io_wieg_handler(uint64_t data)
{
	uint16_t id = 0;
	
	id = (uint16_t)((data >> 1) & 0x000000000000ffff);
	
	g_Wieg_ID = id;
	
}
/**************************
** @brief 
** @param
** @retval
****************************/
uint16_t  GetWiegID(void)
{
	uint16_t tmp 	= g_Wieg_ID;
	
	g_Wieg_ID 		= 0;
	
	return tmp;
}
/**************************
** @brief Weigand D1
** @param
** @retval
****************************/
void GPIOP0IntHandler(void)
{
	MAP_GPIOIntClear(GPIO_PORTP_BASE,GPIO_INT_PIN_0);
	
	g_wieg_timeout = 1;
	
	g_wieg_reading_data <<= 1;
	g_wieg_reading_data |= 0x0000000000000001;
	
	g_wieg_current_bit++;
	
}
/**************************
** @brief Weigand D0
** @param
** @retval
****************************/
void GPIOQ0IntHandler(void)
{
	MAP_GPIOIntClear(GPIO_PORTQ_BASE,GPIO_INT_PIN_0);
	
	g_wieg_timeout = 1;
	
	g_wieg_reading_data <<= 1;
	g_wieg_reading_data &= 0xfffffffffffffffe;
	
	g_wieg_current_bit++;
}


















