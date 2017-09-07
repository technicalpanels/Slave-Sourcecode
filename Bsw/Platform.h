#ifndef __PLATFORM__
#define __PLATFORM__

/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/i2c.h"
#include "driverlib/watchdog.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/usb.h"
#include "driverlib/fpu.h"
 
 /////////////////////////////////////////////
 //// Module Software Include ////////////////
 /////////////////////////////////////////////
#include "TM4C1294_Platform/HAL_Dev_Initial.h"
#include "port/gpio_app.h"

#include "can/hcan.h"
#include "monitorcontrol/iohandler.h"


#define TICKS_PER_SECOND 10000

#define MS_PER_SYSTICK (1000 / TICKS_PER_SECOND)

#ifndef NULL
#	define NULL						((void*)0)
#endif
 
#define   ON              1
#define   OFF							0

#define WDT_ON								1

extern uint32_t ui32SysClock;




#endif
