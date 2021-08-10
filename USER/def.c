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
//��ʼ����Сϵͳ����PC13LED
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
//=============================================================================
//��ʼ������PA0����Ϊ�񶯸�Ӧ����OUT�ӿ����룩
//=============================================================================	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
//=============================================================================
//��ʼ��PB1����Ϊ�¶ȸ�Ӧ����IN/OUT�ӿڣ�
//=============================================================================	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//=============================================================================
//��ʼ����Сϵͳ����PA1�����Ϊ��������ܣ�
//=============================================================================		
//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE); 		
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//=============================================================================
//��ʼ��PA2����Ϊ���ո�Ӧ����IN/OUT�ӿ�SCL��
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
//=============================================================================
//��ʼ��PA3����Ϊ���ո�Ӧ����IN/OUT�ӿ�SDA��
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
//=============================================================================
//��ʼ��PA4����ΪPH��Ӧ����IN�ӿڣ�ADC12_IN4
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1 , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_ADCCLKConfig (RCC_PCLK2_Div6);
//=============================================================================
//��ʼ��PA9����Ϊ���ڵ�TX�ӿڣ�
//=============================================================================		
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
//=============================================================================
//��ʼ��PA10����Ϊ���ڵ�RX�ӿڣ�
//=============================================================================	
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//=============================================================================
//��ʼ��B9��ΪVCC��
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//=============================================================================
//��ʼ��B8��ΪVCC��
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//=============================================================================
//��ʼ��B7��ΪVCC��
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//=============================================================================
//��ʼ��B10��ΪGND��
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//=============================================================================
//��ʼ��B11��ΪGND��
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
//��ʼ��������
VOID sensorInit(STATUS *status){
	NVIC_Configuration();
	GPIO_Configuration();
	tempInit();
	IIC_Init();
	ph_ADC_init();
}
//��ȡ�¶� �������¶ȼ���� ����ֵ���¶�ֵ ��λ����
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
	temp = (TH << 8) | TL; //�γɽ�����������16�����¶�ֵ��
	temperature = (TEMP)temp / 16;

	if(temperature <= 0 || temperature >= 85) *status = SENSOR_TEMP_ERROR;//����¶ȴ��ڵ���85�����������¶ȵ���0��Ҳ����
	return temperature;
}
//��ȡ��ǿ ����ֵ����ǿֵ ��λ��V
LIGHT getLight(STATUS *status){
	BYTE BUF[2]={0x0F,0xF0};
	TWO_BYTE_UNSIGNED_DATA ligh=0x00FF;
	LIGHT light = 1;
	BYTE i=0;
	Single_Write_IIC(CMD_POWER_ON);// power on
	Single_Write_IIC(CMD_1_H_MODE);// H- resolution mode
	sleep(180000);//��ʱ180ms
	Multiple_Read_BH1750(BUF);//�����������ݣ��洢��BUF��  
	for(i=0;i<3;i++)
	ligh =(BUF[0]<<8)+BUF[1];//�ϳ����� 
	light=(LIGHT) ligh/1.2;
	return light;
}
//��ȡPHֵ ����ֵ��PHֵ ���٣�1
PH getPH(STATUS *status){
	TWO_BYTE_UNSIGNED_DATA phdt=0x0ff0;
	PH ph=7;
	ADC_enable();
	ADC_Start_Convert();
	phdt = ADC_Get_Value();
	ph = phdt * PH_LINE_K + PH_LINE_B;
	return ph;
}
//��ȡ�������� ����ֵ��status
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
		return 1;//�ж�û��ˮ��
	}
	if(t > 17){
		return 0;//�ж���ˮ��
	}
	return 2;//��ȷ����û��ˮ��
}
//��ȡ�������� ����ֵ��DATA�ṹ�����
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
//�ϴ�����
VOID upLoad(STATUS *status,DATA* data){
	CHAR cmd[RX_BUF_SIZE] = {0};
	//����Ƿ�����
	SEND_CMD(status," AT","OK",5000);
	//����ģʽ
	SEND_CMD(status," AT+CWMODE=1","OK",5000);
	if(checkWIFIconnected(status) == FALSE){
		//����WIFI
		strcpy(cmd," AT+CWJAP=");
		strcat(cmd,LOCAL_SSID);
		strcat(cmd,",");
		strcat(cmd,LOCAL_PWD);
		I_WD_Feed(status);
		SEND_CMD(status,cmd,"OK",5000000);
		I_WD_Feed(status);
	}
	//�鿴IP��mac��ַ
	SEND_CMD(status," AT+CIFSR","OK",10000);
	//����TCP����������
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
//��ʼ������
VOID netInit(STATUS *status){
	//CHAR cmd[RX_BUF_SIZE] = {0};
  USART_Configuration();
	//�رջ���
	SEND_CMD(status," ATE0","OK",5000);
	//����Ƿ�����
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

