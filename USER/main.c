//=============================================================================
//�ļ����ƣ�main.c
//���ܸ�Ҫ����׼�������
//��Ȩ���У�Williamrjw
//���Է�ʽ��ST-Link
//=============================================================================

//ͷ�ļ�
#include "def.h"
#include "stm32f10x.h"
#include "stdio.h"

//��������
void GPIO_Configuration(void);


int main(void)
{
		//��ʼ��DATA����
		DATA tmp = {0,{0,0,0,0,0},0,7,'\0','\0'};
		DATA *data = &tmp;
		//��ʼ��
		sensorInit();
		netInit();
		watchDogInit();
		GPIO_Configuration();
		//while�е����ݲ����ظ�
		while(TRUE){
			getData(data);//��ȡ����
			upLoad();//�ϴ�����
			sleep(SLEEP_TIME);//�ȴ�SLEEP_TIMEʱ���ѭ������
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
//��ʼ����Сϵͳ����PC13LED
//=============================================================================		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
//=============================================================================
//��ʼ������PA0����Ϊ��Ӧ����OUT�ӿ����룩
//=============================================================================	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}



