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
#include "temp.h"

//��������

VOID test(){
	printf("hello!");
}

int main(void)
{
		//��ʼ��DATA����
		DATA tmp = {0,{0},0,7,'\0'};
		STATUS st_tmp = '\0';
		DATA *data = &tmp;
		STATUS *status = &st_tmp;
		//��ʼ��
		sensorInit(status);
		netInit(status);
		watchDogInit();
		//while�е����ݲ����ظ�
		while(TRUE){
//			getData(status,data);//��ȡ����
//			upLoad(status);//�ϴ�����
//			sleep(SLEEP_TIME);//�ȴ�SLEEP_TIMEʱ���ѭ������
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






