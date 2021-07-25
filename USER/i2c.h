#ifndef __I2C_H__
#define __I2C_H__

#include "def.h"
#include "stm32f10x.h"

//暂定A2为SCL数据线接口
#define SetSCL() GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define ResetSCL() GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define isSCL() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2) 
//暂定A3为SDA数据线接口
#define SetSDA() GPIO_SetBits(GPIOA, GPIO_Pin_3)
#define ResetSDA() GPIO_ResetBits(GPIOA, GPIO_Pin_3)
#define isSDA() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) 

#define SCLin() {GPIOA->CRL&=0XFFFFF0FF;GPIOA->CRL|=0x8<<8;}
#define SCLout() {GPIOA->CRL&=0XFFFFF0FF;GPIOA->CRL|=0x3<<8;}
#define SDAin() {GPIOA->CRL&=0XFFFF0FFF;GPIOA->CRL|=0x8<<12;}
#define SDAout() {GPIOA->CRL&=0XFFFF0FFF;GPIOA->CRL|=0x3<<12;}

////////////////////////////////////////////////////////////////////////////

#define ACK_FLAG    0
#define NO_ACK_FLAG 1

#define	  BH1750_ADDR_H   0x5C          //高精度测量
#define	  BH1750_ADDR_L   0x23 					//低精度测量
//你他妈的到底哪个是从地址
#define   BH1750_SLAVE_ADDR  0x46       //从器件地址(实际上不是46，是从地址加上末尾一个0，形成的46）

//命令
#define CMD_POWER_OFF 0x00
#define CMD_RESET 0x07
#define CMD_POWER_ON 0x01								//启动
#define CMD_N_H_MODE 0x10								//连续高精度模式1
#define CMD_1_H_MODE 0x20								//一次高精度测量1
#define CMD_N_H2_MODE 0x11
#define CMD_1_H2_MODE 0x21
#define CMD_N_L_MODE 0x13
#define CMD_1_L_MODE 0x23
/////////////////////////////////////////////////////////////////////////////
/*******函数定义*******/
VOID IIC_Init(VOID);
VOID IIC_Start(VOID);
VOID IIC_Stop(VOID);
VOID IIC_SendACK(BYTE ack);
BYTE IIC_RecvACK(VOID);
VOID IIC_SendByte(BYTE data);
BYTE IIC_RecvByte(VOID);
VOID Single_Write_IIC(BYTE REG_Address);
VOID Multiple_Read_BH1750(BYTE * BUF);


#endif
