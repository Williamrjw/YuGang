#ifndef __DEF_H__
#define __DEF_H__

/*****������������*****/
#define TEMP float
#define LIGHT float
#define PH float
#define FLOW char
#define STATUS unsigned char
#define VOID void
#define TIME long
#define INT int
#define UINT unsigned int
#define CHAR char
#define BYTE unsigned char
#define BIT unsigned char
#define TEMP_DATA short

/*******���峣��*******/
#define TEMP_SENSOR_NUMS 2
#define SLEEP_TIME 5000
#define TRUE 1
#define FALSE 0 

#define STATUS_CODE enum ENUM_STATUS_CODE 
#define DATA struct STRUCT_DATA

/********״̬��********/
STATUS_CODE{
  NONE_ERROR = 0,
  NETWORK_ERROR = 1,
  SENSOR_TEMP_ERROR = 2,
  SENSOR_LIGHT_ERROR = 3,
  SENSOR_PH_ERROR = 4,
  SENSOR_FLOW_ERROR = 5,
  OTHER = 6,
};

/******�ṹ�����******/
DATA{
	TIME timeStamp;			//ʱ���
	TEMP temp[TEMP_SENSOR_NUMS];	//�¶�
	LIGHT light; 			//���ն�
	PH ph;				//pHֵ
	FLOW flow;			//ˮ��״̬
};

/*****��������*****/
//�������жϴ�����
VOID GPIO_Configuration(VOID);
/****����������****/
//��ʼ��������
VOID sensorInit(STATUS *status);
//��ȡ�¶� �������¶ȼ���� ����ֵ���¶�ֵ ��λ����
TEMP getTemp(STATUS *status,INT index);
//��ȡ��ǿ ����ֵ����ǿֵ ��λ��V
LIGHT getLight(STATUS *status);
//��ȡpHֵ ����ֵ��pHֵ ���٣�1
PH getPH(STATUS *status);
//��ȡ�������� ����ֵ��status
FLOW getFlow(STATUS *status);
//��ȡ�������� ����ֵ��DATA�ṹ�����
VOID getData(STATUS *status,DATA *data);

/*****���粿��*****/
//�ϴ����� ����ֵ���ɹ���� bool���� True/False
VOID upLoad(STATUS *status);
//��ʼ������
VOID netInit(STATUS *status);

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
void sleep(UINT MicroSec);

#endif /* __DEF_H__ */
