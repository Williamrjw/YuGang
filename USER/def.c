#include "def.h"
//初始化传感器
void sensorInit(void){
  
}
//获取温度 参数：温度计序号 返回值：温度值 单位：℃
TEMP getTemp(int index){
  return 0.0;
}
//获取光强 返回值：光强值 单位：V
LIGHT getLight(void){
  return 0.0;
}
//获取PH值 返回值：PH值 量纲：1
PH getPH(void){
  return 0.0;
}
//获取流量有无 返回值：status
FLOW getFlow(void){
  return '1';
}
//获取所有数据 返回值：DATA结构体变量
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
//上传数据 返回值：成功与否 bool类型 True/False
STATUS upLoad(void){
  return NONE_ERROR;
}
//初始化网络
void netInit(void){
  
}

/****通断电部分****/
//通水
void setFlow(void){
  
}
//通光
void setLight(void){
  
}
//调温
void setTemp(void){
  
}
//调pH
void setPH(void){
  
}

/*省电管理与看门狗*/
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

/*******休眠*******/
void sleep(int MilliSec){
  
}
