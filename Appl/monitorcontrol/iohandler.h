#ifndef __IOHANDLER__
#define __IOHANDLER__

 
#define 	MAX_INPUT_LOGIC  12
 #define  MAX_OUTPUT_A  	 8
 #define  MAX_OUTPUT_B  	 9
 #define  MAX_OUTPUT_C  	 7
 
 
#define 	TYPE_PORT_A   	0
#define 	TYPE_PORT_B   	1
#define 	TYPE_PORT_C   	2

#define   IO_RELAY_PIN1    4
#define   IO_RELAY_PIN2    5
#define   IO_RELAY_PIN3    6

#define 	INPUT_PIN_LOGIC_1     0
#define 	INPUT_PIN_LOGIC_2     1
#define 	INPUT_PIN_LOGIC_3     2
#define 	INPUT_PIN_LOGIC_4     3
#define 	INPUT_PIN_LOGIC_5     4
#define 	INPUT_PIN_LOGIC_6     5
#define 	INPUT_PIN_LOGIC_7     6
#define 	INPUT_PIN_LOGIC_8     7
#define 	INPUT_PIN_LOGIC_9     8
#define 	INPUT_PIN_LOGIC_10    9
#define 	INPUT_PIN_LOGIC_11    10
#define 	INPUT_PIN_LOGIC_12    11


#define   IOWRITE_OUT_PIN(type,pin,dat)   IOWrite_Output(type,pin,dat)
#define   IOREADINPUT_BITS(n)             (tInputStatus.Input.uiport & n)

typedef struct{
	
	uint16_t uC_CountSet;
	uint16_t uC_CountReSet;
	
}TDCount_Typedef;

typedef struct{
	
	union{
		
		 struct {
			 
			 unsigned Bits1  : 1;
			 unsigned Bits2  : 1;
			 unsigned Bits3  : 1;
			 unsigned Bits4  : 1;
			 unsigned Bits5  : 1;
			 unsigned Bits6  : 1;
			 unsigned Bits7  : 1;
			 unsigned Bits8  : 1;
			 
			 unsigned Bits9  : 1;
			 unsigned Bits10 : 1;
			 unsigned Bits11 : 1;
			 unsigned Bits12 : 1;
			 unsigned Revd   : 4;
			 
		 }BITS;
		 
		 uint8_t  uCport[2];
		 uint16_t uiport;
		 
	}Input;
	
}TInputStatus_Typedef;

typedef struct{
	
	uint8_t               ucInvert;
	uint8_t               uC_Resev;
	uint16_t							uiPIN;
		///// Settting Time /////////////
	uint16_t              uiDebMaxSet;
	uint16_t              uiDebMaxReset;
	TDCount_Typedef 			tDebCount;


	
}TInput_Typedef;

typedef struct{
	
	union{
		
		 struct {
			 
			  /// Port A ///
			 unsigned bits1  : 1;
			 unsigned bits2  : 1;
			 unsigned bits3  : 1;
			 unsigned bits4  : 1;
			 unsigned bits5  : 1;
			 unsigned bits6  : 1;
			 unsigned bits7  : 1;
			 unsigned bits8  : 1;
				/// Port B ///
			 unsigned bits9   : 1;
			 unsigned bits10  : 1;
			 unsigned bits11  : 1;
			 unsigned bits12  : 1;
			 unsigned bits13  : 1;
			 unsigned bits14  : 1;
			 unsigned bits15  : 1;
			 unsigned bits16  : 1;
			 unsigned bits17  : 1;
			  /// Port C ///
			 unsigned bits18  : 1;
			 unsigned bits19  : 1;
			 unsigned bits20  : 1;
			 unsigned bits21  : 1;
			 unsigned bits22  : 1;
			 unsigned bits23  : 1;
			 unsigned bits24  : 1;
			 /// Reved ////
			 unsigned Reved   : 8;
			 
			 
		 }Bits;
		 
		 uint8_t  Bytes[4];
		 uint32_t ui32data;
		 
	 }Output;
	
}TOutputStatus_Typedef;


typedef enum {
	
	OUTPUT_OFF = 0,
	OUTPUT_ON,
	OUTPUT_MEDIUM_BLINK,
	OUTPUT_SINGLE_SHOT
	
}TIOStatus_TypeEnum;

typedef struct{
	
	TIOStatus_TypeEnum   tECtrl_Status; 
	uint32_t 						 uiOutputBitMark;
	uint16_t             CounterClear;
	uint8_t              uC_Short;
	uint8_t              uCNotOveried;
	
	
}TPortControl_Typedef;


typedef struct{
	
	 TOutputStatus_Typedef  tStatusOutput;
	 TDCount_Typedef  			tDeboud[24];
	 TDCount_Typedef  			tDebSetting[24];
	
}TOutputControl_Typedef;


extern TPortControl_Typedef     	TPortControl_A[MAX_OUTPUT_A];
extern TPortControl_Typedef     	TPortControl_B[MAX_OUTPUT_B];
extern TPortControl_Typedef     	TPortControl_C[MAX_OUTPUT_C];
extern  TOutputStatus_Typedef 		tOutputComCtrl;
extern  TInputStatus_Typedef  		tInputStatus; 
extern 	TInput_Typedef  					tInputMod[MAX_INPUT_LOGIC];

void IODefault_Init(void);
void IOInputSetConfig(TInput_Typedef *p ,
	                      uint16_t uipin,uint16_t dedSet,uint16_t dedReset,uint8_t Invert);

uint8_t IORead_SlaveMode(void);
void IOOutputCtrl_Handler(void);
void IOOutputClear_Handler(void);
void IOOutputC_Handler(void);

void IOInput_Handler(void);
uint32_t IOGetOutput_BitsMask(uint8_t type,uint16_t Pin);
void IOWrite_Output(uint8_t type,uint16_t Pin,uint8_t data);




#endif
