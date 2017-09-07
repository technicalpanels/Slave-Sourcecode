#ifndef __HAL_CAL__
#define __HAL_CAL__

#include "driverlib/can.h" 

#define 	MAX_OBJ_TYPE  	32

#define TXOBJECT                1
#define TXRROBJECT              2
#define RXOBJECT                3
#define RXRROBJECT              4


typedef struct {
    /*!
        \brief TivaWare driverlib CAN object.
    */
	  tMsgObjType		eMsgObjType;
	  
	  uint32_t 			ulStatus;
	  uint8_t       ucLength;
    uint8_t 			ui8ArrCanData[8];
	  uint8_t       Cmd;
	
	
}tCANBUSMsg;



uint8_t CanBusTxWrite(uint8_t *pBuffer,
	                 uint32_t ui32MsgID, 
                   uint8_t  Object_ID,
                   uint8_t  ui32MsgLen);

void can_Init(uint8_t Address);
 
 void can_ResetError(void);
  
 
#endif
 
 
 

