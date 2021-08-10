#include "def.h"
#include "adc.h"
#include "stm32f10x.h"
#include "stm32f10x_adc.h"


VOID ph_ADC_init(VOID){
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	// we work in continuous sampling mode
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 4;

	ADC_RegularChannelConfig(ADC1,ADC_Channel_4, 1,ADC_SampleTime_28Cycles5); // define regular conversion config
	ADC_Init ( ADC1, &ADC_InitStructure);	//set config of ADC1
}

VOID ADC_enable(VOID){
	ADC_Cmd(ADC1,ENABLE);	//enable ADC1
}

VOID ADC_Start_Convert(VOID){
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	// start conversion (will be endless as we are in continuous mode)
}
TWO_BYTE_UNSIGNED_DATA ADC_Get_Value(VOID){
	return (TWO_BYTE_UNSIGNED_DATA) ADC_GetConversionValue(ADC1);
}



