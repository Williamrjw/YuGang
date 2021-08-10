#ifndef __ADC_H__
#define __ADC_H__

#include "def.h"
#include "stm32f10x.h"


#define PH_LINE_K -0.0044
#define PH_LINE_B 13.389


VOID ph_ADC_init(VOID);
VOID ADC_enable(VOID);
VOID ADC_Start_Convert(VOID);
TWO_BYTE_UNSIGNED_DATA ADC_Get_Value(VOID);

#endif 


