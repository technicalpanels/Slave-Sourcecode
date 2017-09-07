#ifndef __BSW_RTE__
#define __BSW_RTE__

#include "wiegand/wiegand.h"
#include "odm/odm.h"

//#define RTE_OUTPUTA_SETBITS(Bits)    tOutputStatus.uiStatus_OutputA |= Bits;
extern void LED_Toggle(void);
extern uint8_t App_Slave_GetID(void);

#define RTE_PORT_BIT_OUTA_(pin,dat)  portA_Write_pin(pin,dat)
#define RTE_PORT_BIT_OUTB_(pin,dat)  portB_Write_pin(pin,dat)
#define RTE_PORT_BIT_OUTC_(pin,dat)  portC_Write_pin(pin,dat)
                                     
#define LED_DEBUG_TOGGLE()    LED_Toggle();
#define SLAVE_ADD_GET()       App_Slave_GetID()
////////////////////////////////////////////////////
////////////////////////////////////////////////////
#define GET_WIEG_ID()         GetWiegID()

////////////////////////////////////////////////////
////////////////////////////////////////////////////
#define ODM_GET_SPEED()       vOdmGetSpeed()
#define ODM_GET_COUNT()       vOdmGetCount()




#endif
