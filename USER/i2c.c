
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
	SDAout();					//�������ģʽ
	SetSDA();       	//����������
	sleep(5);
	SetSCL();         //����ʱ����
	sleep(10);         //��ʱ
	ResetSDA();       //�����½���
	sleep(5);         //��ʱ
	ResetSCL();       //����ʱ����
	sleep(5);
}
VOID IIC_Stop(VOID)
{						
	SDAout();					//�������ģʽ
	ResetSDA();       //����������
	sleep(5);
	SetSCL();         //����ʱ����
	sleep(10);         //��ʱ
	SetSDA();       	//����������
	sleep(5);         //��ʱ
}
VOID IIC_SendACK(BYTE ack)
{						
	SDAout();					//�������ģʽ
	ResetSCL();       //����ʱ����
	if(ack) SetSDA(); 
	else ResetSDA();  //дӦ���ź�
	sleep(2);         //��ʱ
	SetSCL();         //����ʱ����
	sleep(5);  	      //��ʱ
	ResetSCL();       //����ʱ����
}
BYTE IIC_RecvACK(VOID)
{
	BYTE cnt=0;
	SDAin();//����ģʽ
	SetSDA(); //////////////////////////////?Ϊʲô����ģʽ������ֵ������
	sleep(1);
	SetSCL();
	sleep(1);
	while(isSDA())//�ȴ�Ӧ��
	{
		cnt++;
		sleep(1);
		if(cnt>=250)//�ȴ�ʱ�����������ֹͣ�źţ�����1����ʾ����Ӧ��ʧ��
		{
			IIC_Stop();
			return NO_ACK_FLAG;
		}
	}
	ResetSCL();//Ӧ��ɹ�����SCL���
	return ACK_FLAG;
}
VOID IIC_SendByte(BYTE data)
{
	BYTE i;
	SCLout();							
	SDAout();					//�������ģʽ
	ResetSCL();       //����ʱ����, ����׼������
	sleep(2);					//��ʱ
	for (i=0;i<8;i++) //�Ӹ�λ��ʼһλһλ�ش���
	{
		if(data & 0x80) 
			SetSDA();			//�����ݿ�
		else 
			ResetSDA();
		data <<= 1;			//�Ƴ����ݵ����λ
		SetSCL(); 			//����ʱ����,��������
		sleep(2);				//��ʱ
		ResetSCL();			//����ʱ���ߣ����ݷ������
		sleep(2);				//��ʱ
	}
}
BYTE IIC_RecvByte()
{
	BYTE i;
	BYTE data = 0;
	SDAin();					//ʹ���ڲ�����,׼����ȡ����,
	for (i=0;i<8;i++)	//8λ������
	{
		ResetSCL();//��ʱ����Ϊ�ͣ�׼����������λ
		sleep(2);//ʱ�ӵ͵�ƽ���ڴ���4.7��s
		SetSCL();//��ʱ����Ϊ��ʹ��������������Ч��������ʼ�����ݣ��ӻ������ٸı������ˣ����ı�SDA�ĵ�ƽ
		data <<= 1;
		SetSCL();//����ʱ����
		if(isSDA()) data |= 0x01;//������               
		sleep(1);//��ʱ
	}
	ResetSCL();
	return data;
}

VOID Single_Write_IIC(BYTE REG_Address)
{
	IIC_Start();//��ʼ�ź�
	IIC_SendByte(BH1750_SLAVE_ADDR);//�����豸��ַ+д�ź�
	IIC_RecvACK();
	IIC_SendByte(REG_Address);//�ڲ��Ĵ�����ַ����ο�����pdf22ҳ 
	IIC_RecvACK();
	IIC_Stop();//����ֹͣ�ź�
}

///////////////////////////////////////////////////////////////////////////
VOID Multiple_Read_BH1750(BYTE *BUF)
{
	IIC_Start();//��ʼ�ź�
  IIC_SendByte(BH1750_SLAVE_ADDR+1);//�����豸��ַ+���ź�
	IIC_RecvACK();
	BUF[0] = IIC_RecvByte();//BUF[0]�洢0x32��ַ�е�����
	IIC_SendACK(ACK_FLAG);
	BUF[1] = IIC_RecvByte();//BUF[1]�洢0x32��ַ�е�����
	IIC_SendACK(NO_ACK_FLAG);
	IIC_Stop();//ֹͣ�ź�
	sleep(5000);
}
