#include "def.h"
#include "watchdog.h"
#include "stm32f10x.h"
#include "stm32f10x_iwdg.h"

#define RELOAD_VALUE 0x0C35


VOID I_WD_Init(VOID){

	
	sleep(5000000);
	/* Enable the LSI OSC */
  RCC_LSICmd(ENABLE);
  /* Wait till LSI is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
	/* Enable Watchdog*/
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  IWDG_SetPrescaler(IWDG_Prescaler_128); // 4, 8, 16 ... 256
  IWDG_SetReload(RELOAD_VALUE);//This parameter must be a number between 0 and 0x0FFF.
  IWDG_ReloadCounter();
  IWDG_Enable();
	//64/40*4095=6552ms=6.552s

  GPIO_ResetBits(GPIOC, GPIO_Pin_13);//¡¡µ∆
}

VOID I_WD_Feed(STATUS* status){
	if( (* status & 0xF0) == 0 )
		IWDG_ReloadCounter();
}


