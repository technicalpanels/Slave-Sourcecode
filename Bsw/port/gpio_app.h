#ifndef __GPIO_HAL__
#define __GPIO_HAL__

#define 	GPIO_PORT_STULED    		GPIO_PORTM_BASE
#define 	GPIO_PIN_STULED    			GPIO_PIN_7

#define 	GPIO_PORT_ADDR_1    		GPIO_PORTA_BASE
#define 	GPIO_PIN_ADDR_1    			GPIO_PIN_4
#define 	GPIO_PORT_ADDR_2    		GPIO_PORTA_BASE
#define 	GPIO_PIN_ADDR_2    			GPIO_PIN_3
#define 	GPIO_PORT_ADDR_3    		GPIO_PORTH_BASE
#define 	GPIO_PIN_ADDR_3    			GPIO_PIN_1

typedef struct {
	
	uint32_t base;
	uint32_t pin;
	
}THAL_GPIO_Typedef;

  

void port_Init(void);
void port_StatusLed_Write(uint8_t status);
uint8_t port_Read_Input_Pin(uint8_t pin);
uint8_t port_Read_pin(uint32_t port,uint32_t pin);

void port_Write_pin(uint32_t port,uint32_t pin,uint8_t status);

void portA_Write_pin(uint32_t pin,uint8_t status);
void portB_Write_pin(uint32_t pin,uint8_t status);
void portC_Write_pin(uint32_t pin,uint8_t status);
			
#endif
