/******************************Copyright(C) Nubo*******************************
File name  : uartfifo.c
Description: uart fifo process
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#include "fifo.h"
#include "uartfifo.h"

//Public Globe variable define
struct fifo_data rcvuart1fifo;
struct fifo_data senduart1fifo;

//Private variable define
u8 rcvUart1Buf[FIFO_UART1_BUF_SIZE];
u8 sendUart1Buf[FIFO_UART1_BUF_SIZE];

/*****************************************************************************
函数  名:   void FIFO_Uart_Init(void)
功能说明:   uartFIFO队列初始化
参    数:   void
返回  值:   void
说    明:   无
*****************************************************************************/
void FIFO_Uart1_Init(void)
{
    fifo_Init(&rcvuart1fifo, rcvUart1Buf, sizeof(rcvUart1Buf));
    fifo_Init(&senduart1fifo, sendUart1Buf, sizeof(sendUart1Buf));
}

