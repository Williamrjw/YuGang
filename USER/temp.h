#ifndef __TEMP_H__
#define __TEMP_H__

#include "def.h"
#include "stm32f10x.h"
//暂定B1为DATA数据线接口
#define SetDS() GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define ResetDS() GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define isDS() GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) 
#define DSin() {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=0x8<<4;}
#define DSout() {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=0x3<<4;}

VOID tempInit(VOID);
VOID tempCheck(STATUS* status);
VOID tempWriteByte(BYTE dat);
BIT tempReadBit(VOID);
BYTE tempReadByte(VOID);

#endif
