#ifndef __ESP01_H__
#define __ESP01_H__

#include "def.h"
#include "stm32f10x.h"

#define CORE_BRAND "ESP01S"

#define LOCAL_SSID "\"ChinaNet-6PRF2Y\""
#define LOCAL_PWD "\"18007085602\""

#define SERVER_IP "\"192.168.2.16\""
#define SERVER_PORT "5261"

#define TIME_SERVER_URL "\"1.cn.pool.ntp.org\""
#define TIME_SERVER_PORT "123"


#define RX_BUF_SIZE 100


VOID clear_RXBuffer(VOID);//Çå¿Õbuffer

VOID USART_Configuration(VOID);//³õÊ¼»¯USART

VOID USART1_IRQHandler(VOID);
VOID USARTSend(CHAR *pucBuffer);
VOID USARTSendLen(CHAR  pucBuffer[],INT len);
VOID USARTRead(VOID);

VOID SEND_CMD(STATUS* status,CHAR * cmd,CHAR * reply,DELAY_TIME time);
VOID SEND_DATA(STATUS* status,DATA * data,CHAR *reply,DELAY_TIME time);
VOID SEND_MESSAGE(STATUS* status,CHAR * msg,INT len,CHAR *reply,DELAY_TIME time);
TIME getTimestamp(STATUS* status);
BYTE checkWIFIconnected(STATUS* status);


#endif
