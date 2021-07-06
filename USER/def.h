#ifndef __DEF_H__
#define __DEF_H__

/*****������������*****/
#define TEMP float
#define LIGHT float
#define PH float
#define FLOW char
#define STATUS char

/*******���峣��*******/
#define TEMP_SENSOR_NUMS 5
#define SLEEP_TIME 5000
#define TRUE 1
#define FALSE 0 

#define STATUS_CODE enum ENUM_STATUS_CODE 
#define DATA struct STRUCT_DATA

/********״̬��********/
enum ENUM_STATUS_CODE{
  NONE_ERROR = 0,
  NETWORK_ERROR = 1,
  SENSOR_TEMP_ERROR = 2,
  SENSOR_LIGHT_ERROR = 3,
  SENSOR_PH_ERROR = 4,
  SENSOR_FLOW_ERROR = 5,
  OTHER = 6,
};

/******�ṹ�����******/
struct STRUCT_DATA{
	long timeStamp;			//ʱ���
	TEMP temp[TEMP_SENSOR_NUMS];	//�¶�
	LIGHT light; 			//���ն�
	PH ph;				//pHֵ
	FLOW flow;			//ˮ��״̬
	STATUS status;			//״̬
};

/*****��������*****/
//�������жϴ�����
/****����������****/
//��ʼ��������
void sensorInit(void);
//��ȡ�¶� �������¶ȼ���� ����ֵ���¶�ֵ ��λ����
TEMP getTemp(int index);
//��ȡ��ǿ ����ֵ����ǿֵ ��λ��V
LIGHT getLight(void);
//��ȡPHֵ ����ֵ��PHֵ ���٣�1
PH getPH(void);
//��ȡ�������� ����ֵ��status
FLOW getFlow(void);
//��ȡ�������� ����ֵ��DATA�ṹ�����
void getData(DATA *data);

/*****���粿��*****/
//�ϴ����� ����ֵ���ɹ���� bool���� True/False
STATUS upLoad(void);
//��ʼ������
void netInit(void);

/****ͨ�ϵ粿��****/
//ͨˮ
void setFlow(void);
//ͨ��
void setLight(void);
//����
void setTemp(void);
//��pH
void setPH(void);

/*ʡ������뿴�Ź�*/
void watchDogInit(void);
void feedDog(void);
void Idle(void);
void Busy(void);
STATUS isBusy(void);

/*******����*******/
void sleep(int MilliSec);

#endif /* __DEF_H__ */
