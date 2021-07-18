#include "def.h"
#include "temp.h"
#include "stm32f10x.h"
VOID GPIO_Configuration(VOID)
{
  GPIO_InitTypeDef GPIO_InitStructure;
//=============================================================================
//初始化最小系统板上PC13LED
//=============================================================================		
//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 		
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//=============================================================================
//初始化输入PA0（作为感应器的OUT接口输入）
//=============================================================================	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
//=============================================================================
//初始化输入PB1（作为感应器的OUT接口输出）
//=============================================================================	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//=============================================================================
//初始化最小系统板上PA1输出
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//初始化传感器
VOID sensorInit(STATUS *status){
	GPIO_Configuration();
	tempInit();
}
//获取温度 参数：温度计序号 返回值：温度值 单位：℃
TEMP getTemp(STATUS *status,INT index){
	BYTE TL=0x0F,TH=0xF0;
	TEMP_DATA temp=0x00FF;
	TEMP temperature = 0;
///////////////////////////////
	UINT i;
///////////////////////////////
	
	tempInit();//INITIAL
	tempCheck();//UNTIL INITIAL FINISH
	tempWriteByte(0xcc);//SKIP THE ROM, DIRECTLY MEASURE AND CONVERT
	tempWriteByte(0x44);//BEGIN MEASURE AND CONVERT
	
	tempInit();//INITIAL
	tempCheck();//UNTIL INITIAL FINISH
	tempWriteByte(0xcc);//SKIP THE ROM, DIRECTLY MEASURE AND CONVERT
	tempWriteByte(0xbe);//BEGIN READ THE RESULT
	
	TL = tempReadByte(); 	// LSB   
  TH = tempReadByte(); 	// MSB  
	temp = (TH << 8) | TL; //形成结果，结果除以16就是温度值。
	temperature = (TEMP)temp / 16;
	
/////////////////////////////////
for (i =0;i<16;i++){
	if((temp >> i) & 0x0001){
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
	else{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
	sleep(1000000);
}
/////////////////////////////////
	return temperature;
}
//获取光强 返回值：光强值 单位：V
LIGHT getLight(STATUS *status){
	return 0;
}
//获取PH值 返回值：PH值 量纲：1
PH getPH(STATUS *status){
	return 0;
}
//获取流量有无 返回值：status
FLOW getFlow(STATUS *status){
	int i = 0,t = 0;
	for(;i<10;i++){
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) != 0)
			{
				t++;
			}
			sleep(30);
	}
	if(t < 4){
		return 0;//判断没有水流
	}
	if(t > 7){
		return 1;//判断有水流
	}
	return 2;//不确定有没有水流
}
//获取所有数据 返回值：DATA结构体变量
VOID getData(STATUS *status,DATA *data){
	int i = 0;
	data->timeStamp = 0;
	for(;i < TEMP_SENSOR_NUMS ; i++){
		data->temp[i] = getTemp(status,i);
	}
	data->light = getLight(status);
	data->ph = getPH(status);
	data->flow = getFlow(status);
}
//上传数据
VOID upLoad(STATUS *status){
  
}
//初始化网络
VOID netInit(STATUS *status){
  
}

VOID sleep(UINT us){
	int i=0,j;
	for(j = us;j>=0;j--)
		for(i = 0 ; i< 9;i++);
}

VOID watchDogInit(){
	
}

