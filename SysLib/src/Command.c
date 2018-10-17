/******************************Copyright(C) Nubo*******************************
File name  : command.c
Description: get cmd frame from uart fifo
Platform   : MDK V5.23.0.0
Version    : V1.0
Author	   : Joey
Create Time: 2018-1-3
Modify	   : 
Modify Time: 
******************************************************************************/

#include "crc.h"
#include "command.h"

//Private variable define
static const u8 HeadCMD = 0x7E;

/******************************************************************************
Function   : u8 ChkSum(u8 *buf, u8 len)
Description: calulate data sum is or not equal
Input      : buf - to be treated data
             len - data length
Output     : 0 - equal
             1 - not equal
Author     : Joey
Time       : 2018-1-4
******************************************************************************/
u8 ChkSum(u8 *buf, u16 len)
{
	u16 i;
	u8 stmp=0;
	for(i=0;i<len-1;i++)
	{
		stmp += buf[i];
	}
	if(stmp == buf[len-1])
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

u8 ChkSumEx(u8 *buf, u8 data, u16 len)
{
	u16 i;
	u8 stmp=data;
	for(i=0;i<len-1;i++)
	{
		stmp += buf[i];
	}
	if(stmp == buf[len-1])
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/******************************************************************************
Function   : u8 CalulateSum(u8 *buf, u8 len)
Description: calulate data sum 
Input      : buf - to be treated data
             len - data length
Output     : calulated data sum
Author     : Joey
Time       : 2018-1-4
******************************************************************************/
u8 CalulateSum(u8 *buf, u16 len)
{
	u16 i;
	u8 stmp=0;
	for(i=0;i<len;i++)
	{
		stmp += buf[i];
	}
	return stmp;
}



/******************************************************************************
Function   : u32 cmd_get(u8 *cmdBuf, struct fifo_data *fifo)
Description: get command frame from fifo
Input      : cmdBuf - getted command frame storage state
             fifo - fifo handle 
Output     : u32 - the fifo position
Author     : Joey
Time       : 2018-1-4
******************************************************************************/
u32 cmd_get(u8 *cmdBuf, struct fifo_data *fifo)
{
    u32 i;
    u8 tmp=0;
    ERRR(fifo == NULL, goto ERR1);
    
    ERRR(fifo_empty(fifo) == TRUE, goto ERR1);        //FIFO为空
    i = fifo_find(fifo, &HeadCMD, sizeof(HeadCMD));
    fifo->front = i;
//    ERRR(fifo_empty(fifo) == TRUE, goto ERR1);        //FIFO为空
	ERRR(fifo_validSize(fifo) < 3, goto ERR1);        //FIFO为空
	
//    i = *(u16 *)&fifo->data[(fifo->front + sizeof(HeadCMD))%fifo->size];//在循环队列的交界位置取两字节数据有BUG，需要修正
	if((fifo->size - 1) == ((fifo->front + sizeof(HeadCMD))%fifo->size))
	{
		i  = fifo->data[fifo->size - 1];
		i += (u32)(fifo->data[0] << 8);
	}
	else
	{
		i = *(u16 *)&fifo->data[(fifo->front + sizeof(HeadCMD))%fifo->size];
	}
	
    ERRR(i == 0, goto ERR1);  //数据指令长度错误
    ERRR(i > CMD_SIZE, goto ERR2);  //数据指令长度错误
    ERRR(i > fifo_validSize(fifo), goto ERR1); //数据空间不够
                   
//    ERRR(ChkSum(&fifo->data[(fifo->front)%fifo->size], i), goto ERR2);    //检验错误
	//修正当缓冲区不够下一节的时候，自动check到下一节。
	if(fifo->front < fifo->rear)
	{
		ERRR(ChkSum(&fifo->data[(fifo->front)%fifo->size], i), goto ERR2);    //检验错误
	}
	else
	{
		tmp = CalulateSum(&fifo->data[(fifo->front)%fifo->size], fifo->size-fifo->front);
		ERRR(ChkSumEx(&fifo->data[0], tmp, i-(fifo->size-fifo->front)), goto ERR2);
	}

    ERRR(fifo_gets(fifo, cmdBuf, i) == FALSE, goto ERR1);   //数据内容出队
    return i;

ERR2:   fifo->front = (fifo->front+sizeof(HeadCMD))%fifo->size; //数据错误将头移出
ERR1:   return 0;
}

/******************************************************************************
Function   : u32 cmd_put(struct fifo_data *fifo, u8 *cmdBuf, u32 cmdLen)
Description: put a command frame to send fifo
Input      : fifo - handle fifo
             cmdBuf - to be treated data
             cmdLen - data length
Output     : 0 - FALSE, 1 - TURE
Author     : Joey
Time       : 2018-1-4
******************************************************************************/
u32 cmd_put(struct fifo_data *fifo, u8 *cmdBuf, u32 cmdLen)
{
	u8 sum = 0;
    ERRR(fifo == NULL, goto ERR1);
	ERRR(cmdLen > CMD_SIZE, goto ERR1);

	sum = CalulateSum(cmdBuf, cmdLen-1);
//	cmdBuf[cmdLen-1] = sum;
	*(cmdBuf+cmdLen-1) = sum;
	
    ERRR(fifo_puts(fifo, cmdBuf, cmdLen) == FALSE, goto ERR1); 
    return TRUE;
ERR1:   return FALSE;
}

/**************************Copyright Nubo 2018-01-03*************************/
