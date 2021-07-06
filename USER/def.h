#ifndef __DEF_H__
#define __DEF_H__

/*****定义数据类型*****/
#define TEMP float
#define LIGHT float
#define PH float
#define FLOW char
#define STATUS char

/*******定义常量*******/
#define TEMP_SENSOR_NUMS 5
#define SLEEP_TIME 5000
#define TRUE 1
#define FALSE 0 

#define STATUS_CODE enum ENUM_STATUS_CODE 
#define DATA struct STRUCT_DATA

/********状态码********/
enum ENUM_STATUS_CODE{
  NONE_ERROR = 0,
  NETWORK_ERROR = 1,
  SENSOR_TEMP_ERROR = 2,
  SENSOR_LIGHT_ERROR = 3,
  SENSOR_PH_ERROR = 4,
  SENSOR_FLOW_ERROR = 5,
  OTHER = 6,
};

/******结构体变量******/
struct STRUCT_DATA{
	long timeStamp;			//时间戳
	TEMP temp[TEMP_SENSOR_NUMS];	//温度
	LIGHT light; 			//光照度
	PH ph;				//pH值
	FLOW flow;			//水流状态
	STATUS status;			//状态
};

/*****函数声明*****/
//不包括中断处理函数
/****传感器部分****/
//初始化传感器
void sensorInit(void);
//获取温度 参数：温度计序号 返回值：温度值 单位：℃
TEMP getTemp(int index);
//获取光强 返回值：光强值 单位：V
LIGHT getLight(void);
//获取PH值 返回值：PH值 量纲：1
PH getPH(void);
//获取流量有无 返回值：status
FLOW getFlow(void);
//获取所有数据 返回值：DATA结构体变量
void getData(DATA *data);

/*****网络部分*****/
//上传数据 返回值：成功与否 bool类型 True/False
STATUS upLoad(void);
//初始化网络
void netInit(void);

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
void sleep(int MilliSec);

#endif /* __DEF_H__ */
