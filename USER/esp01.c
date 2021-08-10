#include "def.h"
#include "esp01.h"
#include "watchdog.h"
#include "stdio.h"
#include "string.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"



volatile CHAR RX_FLAG_END_LINE = 0;
volatile BYTE RXi; //index
volatile CHAR RXc; //char
CHAR RX_BUF[RX_BUF_SIZE] = {'\0'};//接收buffer
CHAR TIME_CMD[48] =  {0xE3, 0x0, 0x6, 0xEC, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x31, 0x4E, 0x31, 0x34, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};


VOID clear_RXBuffer(VOID) {
	for (RXi=0; RXi<RX_BUF_SIZE; RXi++)
		RX_BUF[RXi] = '\0';
	RXi = 0;
}

VOID USART_Configuration(VOID){
	/* Configure the USART1 */
	USART_InitTypeDef USART_InitStructure;
	/* USART1 configuration ------------------------------------------------------*/
	/* USART1 configured as follow:
		- BaudRate = 115200 baud
		- Word Length = 8 Bits
		- One Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
		- USART Clock disabled
		- USART CPOL: Clock is active low
		- USART CPHA: Data is captured on the middle
		- USART LastBit: The clock pulse of the last data bit is not output to
			the SCLK pin
	 */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);

	/* Enable USART1 */
	USART_Cmd(USART1, ENABLE);

	/* Enable the USART1 Receive interrupt: this interrupt is generated when the
		USART1 receive data register is not empty */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
VOID USART1_IRQHandler(VOID)
{
    if ((USART1->SR & USART_FLAG_RXNE) != (u16)RESET)
	{
				
				//GPIO_ResetBits(GPIOC, GPIO_Pin_13);		
				RXc = USART_ReceiveData(USART1);
				//GPIO_SetBits(GPIOC, GPIO_Pin_13);	
    		RX_BUF[RXi] = RXc;
    		RXi++;

    		if (RXc != 13) {
    			if (RXi > RX_BUF_SIZE-1) {
    				clear_RXBuffer();
    			}
    		}
    		else {
    			RX_FLAG_END_LINE = 1;
    		}

	}
}

VOID USARTSend(CHAR *pucBuffer)
{
    while (*pucBuffer)
    {
        USART_SendData(USART1, *pucBuffer++);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }
}
VOID USARTSendLen(CHAR pucBuffer [] ,INT len){
	INT i = 0;
	for (i =0 ;i < len;i++)
	{
		USART_SendData(USART1, pucBuffer[i]);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	}
}
VOID USARTRead(VOID){
	while(TRUE){
		if (RX_FLAG_END_LINE == 1) {
					// Reset END_LINE Flag
					RX_FLAG_END_LINE = 0;
					break;
		}
	}
}

VOID SEND_CMD(STATUS* status,CHAR * cmd,CHAR * reply,DELAY_TIME delay_time){
	clear_RXBuffer();
	USARTSend(cmd);
	USARTSend("\r\n");
	sleep(delay_time);
	USARTRead();
	if(strstr(RX_BUF,reply)){
		return;
	}
	else if(strstr(RX_BUF,"ALREADY CONNECTED")){
		return;
	}
	else if(strstr(RX_BUF,"WIFI CONNECTED")){
		return;
	}
	else *status = NETWORK_CONNECT_ERROR;
}

VOID SEND_DATA(STATUS* status,DATA *data,CHAR * reply,DELAY_TIME delay_time){
	CHAR tmp[50]={0};
	INT i = 0;
	clear_RXBuffer();
	/*************************
	DATA{
		TIME timeStamp;			//时间戳
		TEMP temp[TEMP_SENSOR_NUMS];	//温度
		LIGHT light; 			//光照度
		PH ph;				//pH值
		FLOW flow;			//水流状态
		STATUS *status; //状态
	};
	 *************************/
	I_WD_Feed(status);
	sprintf(tmp,"TIMESTAMP:\t%ld",data->timeStamp);
	SEND_MESSAGE(status,tmp,strlen(tmp),"OK",delay_time);
	
	for(i=0;i<TEMP_SENSOR_NUMS;i++){
		I_WD_Feed(status);
		sprintf(tmp,"TEMP[%d]:\t%.2f degree(C)",i,data->temp[i]);
		SEND_MESSAGE(status,tmp,strlen(tmp),"OK",delay_time);
	}
	
	I_WD_Feed(status);
	sprintf(tmp,"LIGHT:\t%.2f lx",data->light);
	SEND_MESSAGE(status,tmp,strlen(tmp),"OK",delay_time);
	
	I_WD_Feed(status);
	sprintf(tmp,"PH:\t%.1f",data->ph);
	SEND_MESSAGE(status,tmp,strlen(tmp),"OK",delay_time);
	
	I_WD_Feed(status);
	sprintf(tmp,"FLOW:\t%d",data->flow);
	SEND_MESSAGE(status,tmp,strlen(tmp),"OK",delay_time);
	
	I_WD_Feed(status);
	sprintf(tmp,"STAT:\t%d",(INT) *status);
	SEND_MESSAGE(status,tmp,strlen(tmp),"OK",delay_time);
	
	I_WD_Feed(status);

}
VOID SEND_MESSAGE(STATUS* status,CHAR * msg,INT len, CHAR *reply,DELAY_TIME delay_time)
{
	CHAR cmd[20] = {0};
	sprintf(cmd," AT+CIPSEND=%d",len);
	clear_RXBuffer();
	USARTSend(cmd);
	USARTSend("\r\n");
	sleep(delay_time);
	USARTRead();
	I_WD_Feed(status);
	clear_RXBuffer();
	USARTSendLen(msg,len);
	//USARTSend("\r\n");
	sleep(delay_time);
	USARTRead();
	if(strstr(RX_BUF,reply)){
		return;
	}
	else if(strstr(RX_BUF,"busy")){
		*status = SERVER_BUSY_ERROR;
	}
	else if(strstr(RX_BUF,"FAIL")){
		*status = SERVER_CONNECT_ERROR;
	}
	else *status = NETWORK_CONNECT_ERROR;
}
TIME getTimestamp(STATUS* status){
	CHAR cmd[RX_BUF_SIZE] = {0};
	TIME time = 0ll ;
	//检查是否正常
	SEND_CMD(status," AT","OK",5000);
	//设置模式
	SEND_CMD(status," AT+CWMODE=1","OK",5000);
	if(checkWIFIconnected(status) == FALSE){
		//连接WIFI
		strcpy(cmd," AT+CWJAP=");
		strcat(cmd,LOCAL_SSID);
		strcat(cmd,",");
		strcat(cmd,LOCAL_PWD);
		I_WD_Feed(status);
		SEND_CMD(status,cmd,"OK",5000000);
		I_WD_Feed(status);
	}
	//查看IP与mac地址
	SEND_CMD(status," AT+CIFSR","OK",10000);
	//设置UDP服务器参数
	strcpy(cmd," AT+CIPSTART=\"UDP\",");
	strcat(cmd,TIME_SERVER_URL);
	strcat(cmd,",");
	strcat(cmd,TIME_SERVER_PORT);
	I_WD_Feed(status);
	SEND_CMD(status, cmd,"OK",2000000);
	I_WD_Feed(status);
	SEND_MESSAGE(status, TIME_CMD ,48 ,"OK" ,5000000);
	I_WD_Feed(status);
	time = (TIME) RX_BUF[78]<<24|(TIME) RX_BUF[79]<<16|(TIME)RX_BUF[80]<<8|RX_BUF[81];
	if(time == 0){ *status = SERVER_TIME_ERROR; return 0;}
	time = time - 2208988800u;
	SEND_CMD(status," AT+CIPCLOSE","OK",5000);
	return time;
}

BYTE checkWIFIconnected(STATUS* status)
{
	I_WD_Feed(status);
	SEND_CMD(status," AT+CWJAP?","OK",8000);
	I_WD_Feed(status);
	if(strstr(RX_BUF,LOCAL_SSID))
		return TRUE;
	return FALSE;
}
