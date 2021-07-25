
#include "def.h"
#include "i2c.h"
#include "stm32f10x.h"

VOID IIC_Init(VOID)
{
	//GPIO_Init();
	return;
}
VOID IIC_Start(VOID)
{
	SCLout();							
	SDAout();					//配置输出模式
	SetSDA();       	//拉高数据线
	sleep(5);
	SetSCL();         //拉高时钟线
	sleep(10);         //延时
	ResetSDA();       //产生下降沿
	sleep(5);         //延时
	ResetSCL();       //拉低时钟线
	sleep(5);
}
VOID IIC_Stop(VOID)
{						
	SDAout();					//配置输出模式
	ResetSDA();       //拉低数据线
	sleep(5);
	SetSCL();         //拉高时钟线
	sleep(10);         //延时
	SetSDA();       	//产生上升沿
	sleep(5);         //延时
}
VOID IIC_SendACK(BYTE ack)
{						
	SDAout();					//配置输出模式
	ResetSCL();       //拉低时钟线
	if(ack) SetSDA(); 
	else ResetSDA();  //写应答信号
	sleep(2);         //延时
	SetSCL();         //拉高时钟线
	sleep(5);  	      //延时
	ResetSCL();       //拉低时钟线
}
BYTE IIC_RecvACK(VOID)
{
	BYTE cnt=0;
	SDAin();//输入模式
	SetSDA(); //////////////////////////////?为什么输入模式还设置值？？？
	sleep(1);
	SetSCL();
	sleep(1);
	while(isSDA())//等待应答
	{
		cnt++;
		sleep(1);
		if(cnt>=250)//等待时间过长，产生停止信号，返回1，表示接收应答失败
		{
			IIC_Stop();
			return NO_ACK_FLAG;
		}
	}
	ResetSCL();//应答成功，则SCL变低
	return ACK_FLAG;
}
VOID IIC_SendByte(BYTE data)
{
	BYTE i;
	SCLout();							
	SDAout();					//配置输出模式
	ResetSCL();       //拉低时钟线, 数据准备发送
	sleep(2);					//延时
	for (i=0;i<8;i++) //从高位开始一位一位地传送
	{
		if(data & 0x80) 
			SetSDA();			//送数据口
		else 
			ResetSDA();
		data <<= 1;			//移出数据的最高位
		SetSCL(); 			//拉高时钟线,发送数据
		sleep(2);				//延时
		ResetSCL();			//拉低时钟线，数据发送完毕
		sleep(2);				//延时
	}
}
BYTE IIC_RecvByte()
{
	BYTE i;
	BYTE data = 0;
	SDAin();					//使能内部上拉,准备读取数据,
	for (i=0;i<8;i++)	//8位计数器
	{
		ResetSCL();//置时钟线为低，准备接收数据位
		sleep(2);//时钟低电平周期大于4.7μs
		SetSCL();//置时钟线为高使数据线上数据有效，主机开始读数据，从机不能再改变数据了，即改变SDA的电平
		data <<= 1;
		SetSCL();//拉高时钟线
		if(isSDA()) data |= 0x01;//读数据               
		sleep(1);//延时
	}
	ResetSCL();
	return data;
}

VOID Single_Write_IIC(BYTE REG_Address)
{
	IIC_Start();//起始信号
	IIC_SendByte(BH1750_SLAVE_ADDR);//发送设备地址+写信号
	IIC_RecvACK();
	IIC_SendByte(REG_Address);//内部寄存器地址，请参考中文pdf22页 
	IIC_RecvACK();
	IIC_Stop();//发送停止信号
}

///////////////////////////////////////////////////////////////////////////
VOID Multiple_Read_BH1750(BYTE *BUF)
{
	IIC_Start();//起始信号
  IIC_SendByte(BH1750_SLAVE_ADDR+1);//发送设备地址+读信号
	IIC_RecvACK();
	BUF[0] = IIC_RecvByte();//BUF[0]存储0x32地址中的数据
	IIC_SendACK(ACK_FLAG);
	BUF[1] = IIC_RecvByte();//BUF[1]存储0x32地址中的数据
	IIC_SendACK(NO_ACK_FLAG);
	IIC_Stop();//停止信号
	sleep(5000);
}
