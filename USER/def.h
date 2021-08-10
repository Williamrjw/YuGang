#ifndef __DEF_H__
#define __DEF_H__

/*****������������*****/
#define TEMP float
#define LIGHT float
#define PH float
#define FLOW char
#define STATUS unsigned char
#define VOID void
#define TIME unsigned long int
#define DELAY_TIME int
#define INT int
#define UINT unsigned int
#define CHAR char
#define BYTE unsigned char
#define BIT unsigned char
#define TWO_BYTE_SIGNED_DATA short
#define TWO_BYTE_UNSIGNED_DATA unsigned short

/*******���峣��*******/
#define TEMP_SENSOR_NUMS 2
#define TRUE 1
#define FALSE 0 

#define STATUS_CODE enum ENUM_STATUS_CODE 
#define DATA struct STRUCT_DATA

/********״̬��********/
STATUS_CODE{
	//�޴���
  NONE_ERROR = 0x00,
	//����������
  SENSOR_TEMP_ERROR = 0x01,
  SENSOR_LIGHT_ERROR = 0x02,
  SENSOR_PH_ERROR = 0x03,
  SENSOR_FLOW_ERROR = 0x04,
	//���ڣ�����)���Ӵ���
	NETWORK_CONNECT_ERROR = 0x10,
	NETWORK_BUSY_ERROR = 0x11,
	//���������Ӵ���
	SERVER_CONNECT_ERROR = 0x20,
	SERVER_BUSY_ERROR = 0x21,
	SERVER_TIME_ERROR = 0x22,
	//��������
	OTHER_ERROR = 0xFF,
};

/******�ṹ�����******/
DATA{
	TIME timeStamp;			//ʱ���
	TEMP temp[TEMP_SENSOR_NUMS];	//�¶�
	LIGHT light; 			//���ն�
	PH ph;				//pHֵ
	FLOW flow;			//ˮ��״̬
	STATUS *status; //״̬
};

/*****��������*****/
//��ʼ��GPIO
VOID GPIO_Configuration(VOID);
//��ʼ���ж�
VOID NVIC_Configuration(VOID);
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
VOID upLoad(STATUS *status,DATA* data);
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
