#ifndef __DEF_H__
#define __DEF_H__

/*****定义数据类型*****/
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

/*******定义常量*******/
#define TEMP_SENSOR_NUMS 2
#define TRUE 1
#define FALSE 0 

#define STATUS_CODE enum ENUM_STATUS_CODE 
#define DATA struct STRUCT_DATA

/********状态码********/
STATUS_CODE{
	//无错误
  NONE_ERROR = 0x00,
	//传感器错误
  SENSOR_TEMP_ERROR = 0x01,
  SENSOR_LIGHT_ERROR = 0x02,
  SENSOR_PH_ERROR = 0x03,
  SENSOR_FLOW_ERROR = 0x04,
	//串口（网络)连接错误
	NETWORK_CONNECT_ERROR = 0x10,
	NETWORK_BUSY_ERROR = 0x11,
	//服务器连接错误
	SERVER_CONNECT_ERROR = 0x20,
	SERVER_BUSY_ERROR = 0x21,
	SERVER_TIME_ERROR = 0x22,
	//其他错误
	OTHER_ERROR = 0xFF,
};

/******结构体变量******/
DATA{
	TIME timeStamp;			//时间戳
	TEMP temp[TEMP_SENSOR_NUMS];	//温度
	LIGHT light; 			//光照度
	PH ph;				//pH值
	FLOW flow;			//水流状态
	STATUS *status; //状态
};

/*****函数声明*****/
//初始化GPIO
VOID GPIO_Configuration(VOID);
//初始化中断
VOID NVIC_Configuration(VOID);
/****传感器部分****/
//初始化传感器
VOID sensorInit(STATUS *status);
//获取温度 参数：温度计序号 返回值：温度值 单位：℃
TEMP getTemp(STATUS *status,INT index);
//获取光强 返回值：光强值 单位：V
LIGHT getLight(STATUS *status);
//获取pH值 返回值：pH值 量纲：1
PH getPH(STATUS *status);
//获取流量有无 返回值：status
FLOW getFlow(STATUS *status);
//获取所有数据 返回值：DATA结构体变量
VOID getData(STATUS *status,DATA *data);

/*****网络部分*****/
//上传数据 返回值：成功与否 bool类型 True/False
VOID upLoad(STATUS *status,DATA* data);
//初始化网络
VOID netInit(STATUS *status);

/****通断电部分****/
//通水
void setFlow(void);
//通光
void setLight(void);
//调温
void setTemp(void);
//调pH
void setPH(void);

/*省电管理与看门狗*/
void watchDogInit(void);
void feedDog(void);
void Idle(void);
void Busy(void);
STATUS isBusy(void);

/*******休眠*******/
void sleep(UINT MicroSec);

#endif /* __DEF_H__ */
