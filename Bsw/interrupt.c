

#include "inc/hw_nvic.h"
#include "inc/hw_types.h"

void ResetISR(void);
void NmiSR(void);
void FaultISR(void);
void IntDefaultHandler(void);


/**************************
** @brief 
** @param
** @retval
****************************/
void NmiSR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}
/**************************
** @brief 
** @param
** @retval
****************************/
void FaultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}
/**************************
** @brief 
** @param
** @retval
****************************/
void IntDefaultHandler(void)
{
	
}






