#include "def.h"
#include "temp.h"
#include "i2c.h"
#include "adc.h"
#include "esp01.h"
#include "watchdog.h"
#include "string.h"
#include "stm32f10x.h"
VOID GPIO_Configuration(VOID)
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
//初始化输入PA0（作为振动感应器的OUT接口输入）
//=============================================================================	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
//=============================================================================
//初始化PB1（作为温度感应器的IN/OUT接口）
//=============================================================================	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//=============================================================================
//初始化最小系统板上PA1输出（为发光二极管）
//=============================================================================		
//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE); 		
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//=============================================================================
//初始化PA2（作为光照感应器的IN/OUT接口SCL）
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
//=============================================================================
//初始化PA3（作为光照感应器的IN/OUT接口SDA）
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
//=============================================================================
//初始化PA4（作为PH感应器的IN接口）ADC12_IN4
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1 , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_ADCCLKConfig (RCC_PCLK2_Div6);
//=============================================================================
//初始化PA9（作为串口的TX接口）
//=============================================================================		
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
//=============================================================================
//初始化PA10（作为串口的RX接口）
//=============================================================================	
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//=============================================================================
//初始化B9作为VCC，
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//=============================================================================
//初始化B8作为VCC，
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//=============================================================================
//初始化B7作为VCC，
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//=============================================================================
//初始化B10作为GND，
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//=============================================================================
//初始化B11作为GND，
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_9);
	GPIO_SetBits(GPIOB, GPIO_Pin_8);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	GPIO_ResetBits(GPIOB, GPIO_Pin_10);
	GPIO_ResetBits(GPIOB, GPIO_Pin_11);
}
VOID NVIC_Configuration(VOID){
	/* NVIC Configuration */
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the USARTx Interrupt */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 , ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
//初始化传感器
VOID sensorInit(STATUS *status){
	NVIC_Configuration();
	GPIO_Configuration();
	tempInit();
	IIC_Init();
	ph_ADC_init();
}
//获取温度 参数：温度计序号 返回值：温度值 单位：℃
TEMP getTemp(STATUS *status,INT index){
	BYTE TL=0x0F,TH=0xF0;
	TWO_BYTE_SIGNED_DATA temp=0x00FF;
	TEMP temperature = 0;

	
	tempInit();//INITIAL
	tempCheck(status);//UNTIL INITIAL FINISH
	tempWriteByte(0xcc);//SKIP THE ROM, DIRECTLY MEASURE AND CONVERT
	tempWriteByte(0x44);//BEGIN MEASURE AND CONVERT
	
	tempInit();//INITIAL
	tempCheck(status);//UNTIL INITIAL FINISH
	tempWriteByte(0xcc);//SKIP THE ROM, DIRECTLY MEASURE AND CONVERT
	tempWriteByte(0xbe);//BEGIN READ THE RESULT
	
	TL = tempReadByte(); 	// LSB   
  TH = tempReadByte(); 	// MSB  
	temp = (TH << 8) | TL; //形成结果，结果除以16就是温度值。
	temperature = (TEMP)temp / 16;

	if(temperature <= 0 || temperature >= 85) *status = SENSOR_TEMP_ERROR;//如果温度大于等于85报错，或者是温度低于0℃也报错
	return temperature;
}
//获取光强 返回值：光强值 单位：V
LIGHT getLight(STATUS *status){
	BYTE BUF[2]={0x0F,0xF0};
	TWO_BYTE_UNSIGNED_DATA ligh=0x00FF;
	LIGHT light = 1;
	BYTE i=0;
	Single_Write_IIC(CMD_POWER_ON);// power on
	Single_Write_IIC(CMD_1_H_MODE);// H- resolution mode
	sleep(180000);//延时180ms
	Multiple_Read_BH1750(BUF);//连续读出数据，存储在BUF中  
	for(i=0;i<3;i++)
	ligh =(BUF[0]<<8)+BUF[1];//合成数据 
	light=(LIGHT) ligh/1.2;
	return light;
}
//获取PH值 返回值：PH值 量纲：1
PH getPH(STATUS *status){
	TWO_BYTE_UNSIGNED_DATA phdt=0x0ff0;
	PH ph=7;
	ADC_enable();
	ADC_Start_Convert();
	phdt = ADC_Get_Value();
	ph = phdt * PH_LINE_K + PH_LINE_B;
	return ph;
}
//获取流量有无 返回值：status
FLOW getFlow(STATUS *status){
	int i = 0,t = 0;
	for(;i<20;i++){
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) != 0)
			{
				t++;
			}
			sleep(30);
	}
	if(t < 12){
		return 1;//判断没有水流
	}
	if(t > 17){
		return 0;//判断有水流
	}
	return 2;//不确定有没有水流
}
//获取所有数据 返回值：DATA结构体变量
VOID getData(STATUS *status,DATA *data){
	int i = 0;
	data->timeStamp = getTimestamp(status);
	for(;i < TEMP_SENSOR_NUMS ; i++){
		data->temp[i] = getTemp(status,i);
	}
	data->light = getLight(status);
	data->ph = getPH(status);
	data->flow = getFlow(status);
}
//上传数据
VOID upLoad(STATUS *status,DATA* data){
	CHAR cmd[RX_BUF_SIZE] = {0};
	//检查是否正常
	SEND_CMD(status," AT","OK",5000);
	//设置模式
	SEND_CMD(status," AT+CWMODE=1","OK",5000);
	if(checkWIFIconnected(status) == FALSE){
		//连接WIFI
		strcpy(cmd," AT+CWJAP=");
		strcat(cmd,LOCAL_SSID);
		strcat(cmd,",");
		strcat(cmd,LOCAL_PWD);
		I_WD_Feed(status);
		SEND_CMD(status,cmd,"OK",5000000);
		I_WD_Feed(status);
	}
	//查看IP与mac地址
	SEND_CMD(status," AT+CIFSR","OK",10000);
	//设置TCP服务器参数
	strcpy(cmd," AT+CIPSTART=\"TCP\",");
	strcat(cmd,SERVER_IP);
	strcat(cmd,",");
	strcat(cmd,SERVER_PORT);
	I_WD_Feed(status);
	SEND_CMD(status, cmd,"OK",5000000);
	I_WD_Feed(status);
	SEND_DATA(status,data,"OK",500000);
	I_WD_Feed(status);
	SEND_CMD(status," AT+CIPCLOSE","OK",5000);
	I_WD_Feed(status);
}
//初始化网络
VOID netInit(STATUS *status){
	//CHAR cmd[RX_BUF_SIZE] = {0};
  USART_Configuration();
	//关闭回显
	SEND_CMD(status," ATE0","OK",5000);
	//检查是否正常
	SEND_CMD(status," AT","OK",5000);

}

VOID sleep(UINT us){
	int i=0,j;
	for(j = us;j>=0;j--)
		for(i = 0 ; i< 9;i++);
}

VOID watchDogInit(){
	I_WD_Init();
}

