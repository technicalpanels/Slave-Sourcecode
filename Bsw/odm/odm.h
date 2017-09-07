#ifndef __ODMMETER__
#define __ODMMETER__


void odm_init(uint16_t NumPin);
void OdMeter_Start(void);
void Odmeter_Stop(void);
void Odmeter_Reset(void);
void vOdmeter(void);
uint16_t vOdmGetSpeed(void);
uint16_t vOdmGetCount(void);


#endif
