#include "def.h"
#include "temp.h"
#include "stm32f10x.h"
VOID GPIO_Configuration(VOID)
{
  GPIO_InitTypeDef GPIO_InitStructure;
//=============================================================================
//��ʼ����Сϵͳ����PC13LED
//=============================================================================		
//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 		
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//=============================================================================
//��ʼ������PA0����Ϊ��Ӧ����OUT�ӿ����룩
//=============================================================================	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
//=============================================================================
//��ʼ������PB1����Ϊ��Ӧ����OUT�ӿ������
//=============================================================================	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//=============================================================================
//��ʼ����Сϵͳ����PA1���
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//��ʼ��������
VOID sensorInit(STATUS *status){
	GPIO_Configuration();
	tempInit();
}
//��ȡ�¶� �������¶ȼ���� ����ֵ���¶�ֵ ��λ����
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
	temp = (TH << 8) | TL; //�γɽ�����������16�����¶�ֵ��
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
//��ȡ��ǿ ����ֵ����ǿֵ ��λ��V
LIGHT getLight(STATUS *status){
	return 0;
}
//��ȡPHֵ ����ֵ��PHֵ ���٣�1
PH getPH(STATUS *status){
	return 0;
}
//��ȡ�������� ����ֵ��status
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
		return 0;//�ж�û��ˮ��
	}
	if(t > 7){
		return 1;//�ж���ˮ��
	}
	return 2;//��ȷ����û��ˮ��
}
//��ȡ�������� ����ֵ��DATA�ṹ�����
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
//�ϴ�����
VOID upLoad(STATUS *status){
  
}
//��ʼ������
VOID netInit(STATUS *status){
  
}

VOID sleep(UINT us){
	int i=0,j;
	for(j = us;j>=0;j--)
		for(i = 0 ; i< 9;i++);
}

VOID watchDogInit(){
	
}

