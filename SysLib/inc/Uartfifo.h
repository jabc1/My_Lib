/******************************Copyright(C) Nubo*******************************
File name  : uartfifo.h
Description: uart fifo process
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#ifndef __UARTFIFO_H
#define __UARTFIFO_H
#include "NbType.h"
#include "fifo.h"

#define FIFO_UART1_BUF_SIZE  1024   //define fifo buf size

/***********************************变量声明************************************/
extern struct fifo_data rcvuart1fifo;
extern struct fifo_data senduart1fifo;

/***********************************函数声明************************************/
void FIFO_Uart1_Init(void);

#endif  //433fifo.h End
