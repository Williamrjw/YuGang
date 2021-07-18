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
#include "temp.h"

//函数声明

VOID test(){
	printf("hello!");
}

int main(void)
{
		//初始化DATA变量
		DATA tmp = {0,{0},0,7,'\0'};
		STATUS st_tmp = '\0';
		DATA *data = &tmp;
		STATUS *status = &st_tmp;
		//初始化
		sensorInit(status);
		netInit(status);
		watchDogInit();
		//while中的内容不断重复
		while(TRUE){
//			getData(status,data);//获取数据
//			upLoad(status);//上传数据
//			sleep(SLEEP_TIME);//等待SLEEP_TIME时间后循环操作
//			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)){
//				DSin();
//				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)){
//					GPIO_SetBits(GPIOA, GPIO_Pin_1);
//				}
//				else{
//					GPIO_ResetBits(GPIOA, GPIO_Pin_1);
//				}
//			}
//			else{
//				DSout();
//				if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_1)){
//					GPIO_SetBits(GPIOA, GPIO_Pin_1);
//				}
//				else{
//					GPIO_ResetBits(GPIOA, GPIO_Pin_1);
//				}
//			}
//			
			data->temp[0] = getTemp(status, 0);

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






