//=============================================================================
//文件名称：main.c
//功能概要：鱼缸检测与控制
//版权所有：Williamrjw
//调试方式：ST-Link
//=============================================================================

//头文件
#include "def.h"
#include "esp01.h"
#include "watchdog.h"
#include "stm32f10x.h"


//声明
//初始化DATA变量
DATA tmp = {0,{0},0,7,'\0'};
STATUS st_tmp = '\0';
DATA *data = &tmp;
STATUS *status = &st_tmp;
int main(void)
{
		//初始化
		sensorInit(status);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);//灭灯
		//watchDogInit();
		netInit(status);
		//while中的内容不断重复
		while(TRUE){

			if( NONE_ERROR != *status ){
				GPIO_ResetBits(GPIOC, GPIO_Pin_13);//亮灯
			}
			getData(status,data);
			upLoad(status,data);
			*status = NONE_ERROR;
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






