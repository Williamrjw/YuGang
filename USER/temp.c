#include "def.h"
#include "temp.h"
#include "stm32f10x.h"


VOID tempInit(VOID){//send reset and initialization command
//发送复位和初始化命令
	DSout();
  ResetDS();
  sleep(700);
  SetDS();
	DSin();	//SET INPUT
  sleep(15);
}

STATUS tempCheck(VOID) 	   
{   
	BYTE retry=0; 
    while (isDS()&&retry<200)
	{
		retry++;
		sleep(1);
	};	 
	if(retry>=200)
		return 1;//两百次了还没拉低就是没接上
	retry = 0;
	while (!isDS()&&retry<240)
	{
		retry++;
		sleep(1);
	}
	if(retry >=240) return 1;
	return 0;//初始化成功
}

VOID tempWriteByte(BYTE dat)   //write a byte to ds18b20
{
  BYTE j;
  BIT test;
	DSout();
  for(j=1;j<=8;j++)
  {
    test=dat&0x01;
    dat=dat>>1;
    if(test)     //write 1
    {
      ResetDS();
      sleep(20);
      SetDS();
      sleep(100);
    }
    else
    {
      ResetDS();       //write 0
      sleep(120);
      SetDS();
    }

  }
}
BIT tempReadBit(VOID){
	BIT data;
	DSout();	//SET  OUTPUT
  ResetDS(); 
	sleep(2);
  SetDS(); 
	DSin();	//SET  INPUT
	sleep(12);
	if(isDS())data=1;
    else data=0;	 
    sleep(50);           
    return data;
}
BYTE tempReadByte(VOID){
	BYTE i,j,data;
    data=0;
	for (i=1;i<=8;i++) 
	{
        j=tempReadBit();
        data=(j<<7)|(data>>1);
    }						    
    return data;
}
