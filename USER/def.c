#include "def.h"
//��ʼ��������
void sensorInit(void){
  
}
//��ȡ�¶� �������¶ȼ���� ����ֵ���¶�ֵ ��λ����
TEMP getTemp(int index){
  return 0.0;
}
//��ȡ��ǿ ����ֵ����ǿֵ ��λ��V
LIGHT getLight(void){
  return 0.0;
}
//��ȡPHֵ ����ֵ��PHֵ ���٣�1
PH getPH(void){
  return 0.0;
}
//��ȡ�������� ����ֵ��status
FLOW getFlow(void){
  return '1';
}
//��ȡ�������� ����ֵ��DATA�ṹ�����
void getData(DATA *data){
	int i = 0;
	data->timeStamp = 0;
	for(;i < TEMP_SENSOR_NUMS ; i++){
		data->temp[i] = getTemp(i);
	}
	data->light = getLight();
	data->ph = getPH();
	data->flow = getFlow();
	data->status = NONE_ERROR;
}
//�ϴ����� ����ֵ���ɹ���� bool���� True/False
STATUS upLoad(void){
  return NONE_ERROR;
}
//��ʼ������
void netInit(void){
  
}

/****ͨ�ϵ粿��****/
//ͨˮ
void setFlow(void){
  
}
//ͨ��
void setLight(void){
  
}
//����
void setTemp(void){
  
}
//��pH
void setPH(void){
  
}

/*ʡ������뿴�Ź�*/
void watchDogInit(void){
  
}
void feedDog(void){
  
}
void Idle(void){
  
}
void Busy(void){
  
}
STATUS isBusy(void){
  return OTHER;
}

/*******����*******/
void sleep(int MilliSec){
  
}
