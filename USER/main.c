//=============================================================================
//文件名称：main.c
//功能概要：鱼缸检测与控制
//版权所有：Williamrjw
//调试方式：ST-Link
//=============================================================================

//头文件
#include "def.h"
#include "stm32f10x.h"
#include "stdio.h"

//函数声明
void GPIO_Configuration(void);


int main(void)
{
		//初始化DATA变量
		DATA tmp = {0,{0,0,0,0,0},0,7,'\0','\0'};
		DATA *data = &tmp;
		//初始化
		sensorInit();
		netInit();
		watchDogInit();
		GPIO_Configuration();
		//while中的内容不断重复
		while(TRUE){
			getData(data);//获取数据
			upLoad();//上传数据
			sleep(SLEEP_TIME);//等待SLEEP_TIME时间后循环操作
		}
	  /*
    while (1)
		{
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) != 0){
				GPIO_SetBits(GPIOC, GPIO_Pin_13);
			}else{
				GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			}
    }
		*/
}


void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
//=============================================================================
//初始化最小系统板上PC13LED
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
//=============================================================================
//初始化输入PA0（作为感应器的OUT接口输入）
//=============================================================================	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}



