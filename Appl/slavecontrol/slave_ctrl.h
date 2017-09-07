#ifndef __SLAVE_CTRL_APP__
#define __SLAVE_CTRL_APP__


#define  SL_NDO_TURCK_MOD      
//#define  SL_G4S_THAI_MOD       
//#define  SL_HPT_HK_MOD   
//#define    SL_KUWAIT_MOD
//#define  SL_QATAR_MOD
//#define  SL_INDO_MOD
//#define  SL_S2S_KUWIAL_MOD

#define  INPUT_DATA_BITS_MASK_1     0x1
#define  INPUT_DATA_BITS_MASK_2     0x2
#define  INPUT_DATA_BITS_MASK_3     0x4
#define  INPUT_DATA_BITS_MASK_4     0x8
#define  INPUT_DATA_BITS_MASK_5     0x10
#define  INPUT_DATA_BITS_MASK_6     0x20
#define  INPUT_DATA_BITS_MASK_7     0x30
#define  INPUT_DATA_BITS_MASK_8     0x80
#define  INPUT_DATA_BITS_MASK_9     0x100
#define  INPUT_DATA_BITS_MASK_10    0x200
#define  INPUT_DATA_BITS_MASK_11    0x400
#define  INPUT_DATA_BITS_MASK_12    0x800


#define  OUTPUT_CTRL_BITS_1         0x0
#define  OUTPUT_CTRL_BITS_2     		0x1
#define  OUTPUT_CTRL_BITS_3     		0x2
#define  OUTPUT_CTRL_BITS_4     		0x3
#define  OUTPUT_CTRL_BITS_5     		0x4
#define  OUTPUT_CTRL_BITS_6     		0x5
#define  OUTPUT_CTRL_BITS_7     		0x6
#define  OUTPUT_CTRL_BITS_8     		0x7
#define  OUTPUT_CTRL_BITS_9     		0x8


typedef struct {
	
	uint8_t           uC_State;
	uint8_t     			OutputPort;
	uint16_t    			OutputPin;
	uint32_t 					*p_data;
	uint16_t 					InputBitsMask;
  uint16_t          MaxSetDelay;
	uint16_t          uC_Count;
	uint32_t          uiControlMask;
	
	
}TButtonLED_Typedef;

typedef struct {
	
	uint8_t           uC_TxOn_Ok;
	uint8_t     			TxOutputPort;
	uint8_t           logicON;
	uint16_t    			TxOutputPin;
	uint16_t 					RxBitsMask;
	uint16_t          uiControlMask;
	
  uint16_t          TxDelay;
	uint16_t          RxDelay;
	uint16_t          TxCountFail;
	uint8_t           TxLDeb;
	
	uint16_t          Tx_uC_Count;
	uint16_t          Rx_uC_Count;
	
	uint32_t 					*p_data;
	
}TIRx_Typedef;


typedef struct _MOD_InitTypeDef
{
    uint16_t id;
    uint16_t rev;
    uint8_t  *name;
    void     (*startup)(TButtonLED_Typedef **BtLed , TIRx_Typedef **IRx);
    void     (*background)(void);
    void     (*cleanup)(uint8_t );
	
}TMOD_InitTypeDef;
	

typedef struct {
    union {
			
        struct {
            uint8_t pin1 : 2;
            uint8_t pin2 : 2;
            uint8_t pin3 : 2;
            uint8_t pin4 : 2;
            uint8_t pin5 : 2;
            uint8_t pin6 : 2;
            uint8_t pin7 : 2;
            uint8_t pin8 : 2;
        }pin;
        uint8_t port[2];
    }output_a;                                      // 2 Bytes

    union {
        struct {
            uint8_t pin1 : 2;
            uint8_t pin2 : 2;
            uint8_t pin3 : 2;
            uint8_t pin4 : 2;
            uint8_t pin5 : 2;
            uint8_t pin6 : 2;
            uint8_t pin7 : 2;
            uint8_t pin8 : 2;
            uint8_t pin9 : 2;
        }pin;
        uint8_t port[3];
    }output_b;                                      // 3 Bytes

    union {
        struct {
            uint8_t pin1 : 2;
            uint8_t pin2 : 2;
            uint8_t pin3 : 2;
            uint8_t pin4 : 2;
            uint8_t pin5 : 2;
            uint8_t pin6 : 2;
            uint8_t pin7 : 2;
        }pin;
        uint8_t port[2];
    }output_c;                                      // 2 Bytes

    uint8_t odm_status;                             // 1 Bytes
		
}TOSlave_OutputCtrl_Typedef;

extern TOSlave_OutputCtrl_Typedef  	tOSlave_OutputData_Ctrl ;

extern TInputStatus_Typedef  				tIOStatus_Input;

uint8_t App_Slave_Init(void);
void App_Slave_Ctrl(void);
void SL_BTSwitchSensor_Ctrl(void);
void sIR_Ctrl_Add(TIRx_Typedef *p ,uint16_t RxBitsMask ,uint16_t TxOutputPort , uint16_t TxOutputPin ,uint16_t MaxSetDelay);
void sLed_Ctrl_Add(TButtonLED_Typedef *p ,uint16_t BitsMask,uint16_t OutputPort , uint16_t OutputPin ,uint16_t MaxSetDelay , uint16_t MaxResetDelay);

#endif
