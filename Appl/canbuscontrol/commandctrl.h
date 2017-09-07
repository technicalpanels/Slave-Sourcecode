#ifndef __COMMAND_CAN__
#define __COMMAND_CAN__


#define TYPE_READ   					0x01
#define TYPE_WRITE   					0x02

#define INT_COM_MAX            16


typedef union
{
	struct
	{
   unsigned Prim:1;
	 unsigned Sec:1;
	 unsigned Bootmode:1;
	 unsigned Unlock:1;
	 unsigned FlashError:1;
	 unsigned Trans_Error:1;
	 unsigned Appcrc_Error:1;
	 unsigned Fw_IdentError:1;
		
	}Bits;
	
	uint8_t Byte;
	
}tPSMode_Typedef;

extern tPSMode_Typedef tPSMode;


typedef struct
{
	uint8_t cmd_reg;
	uint8_t cmd_rw;
	uint8_t write_count;
	uint8_t read_count;
	uint8_t DataWrite[INT_COM_MAX];
	uint8_t DataRead[INT_COM_MAX];
	
}TCommand_Typedef;

typedef struct
{

	unsigned char CommandCode;				 				/* Command Code */
	unsigned char Transaction_type;          	/* Command Can R/W ? */
	unsigned char NumberOfbytes;             	/* Count Of Data R/W */
	void(*EventHandler)(void);			     			/* Fuctions to Action Command */


}
p_Command_typeDef;





void Dummy_Fucntions(void);
void Command_Init(void);


#endif
