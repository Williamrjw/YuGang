//=============================================================================
//�ļ����ƣ�main.c
//���ܸ�Ҫ����׼�������
//��Ȩ���У�Williamrjw
//���Է�ʽ��ST-Link
//=============================================================================

//ͷ�ļ�
#include "def.h"
#include "esp01.h"
#include "watchdog.h"
#include "stm32f10x.h"


//����
//��ʼ��DATA����
DATA tmp = {0,{0},0,7,'\0'};
STATUS st_tmp = '\0';
DATA *data = &tmp;
STATUS *status = &st_tmp;
int main(void)
{
		//��ʼ��
		sensorInit(status);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);//���
		//watchDogInit();
		netInit(status);
		//while�е����ݲ����ظ�
		while(TRUE){

			if( NONE_ERROR != *status ){
				GPIO_ResetBits(GPIOC, GPIO_Pin_13);//����
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






