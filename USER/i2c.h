#ifndef __I2C_H__
#define __I2C_H__

#include "def.h"
#include "stm32f10x.h"

//�ݶ�A2ΪSCL�����߽ӿ�
#define SetSCL() GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define ResetSCL() GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define isSCL() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2) 
//�ݶ�A3ΪSDA�����߽ӿ�
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

#define	  BH1750_ADDR_H   0x5C          //�߾��Ȳ���
#define	  BH1750_ADDR_L   0x23 					//�;��Ȳ���
//������ĵ����ĸ��Ǵӵ�ַ
#define   BH1750_SLAVE_ADDR  0x46       //��������ַ(ʵ���ϲ���46���Ǵӵ�ַ����ĩβһ��0���γɵ�46��

//����
#define CMD_POWER_OFF 0x00
#define CMD_RESET 0x07
#define CMD_POWER_ON 0x01								//����
#define CMD_N_H_MODE 0x10								//�����߾���ģʽ1
#define CMD_1_H_MODE 0x20								//һ�θ߾��Ȳ���1
#define CMD_N_H2_MODE 0x11
#define CMD_1_H2_MODE 0x21
#define CMD_N_L_MODE 0x13
#define CMD_1_L_MODE 0x23
/////////////////////////////////////////////////////////////////////////////
/*******��������*******/
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
