/******************************Copyright(C) Nubo*******************************
File name  : fifo.h
Description: fifo source code
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#ifndef __FIFO_H
#define __FIFO_H
#include "NbType.h"

/***********************************宏定义************************************/
/*容错宏*/
#define ERRR(conf, ret)      do              \
                            {                \
                                if (conf)    \
                                {            \
                                    ret;     \
                                }            \
                            } while(0) 
                            
#define MIN(a, b)           ((a) > (b) ? (b) : (a))

/*******************************定义数据结构**********************************/
struct fifo_data
{
    u8   *data;
    u32   size;
    u32   front;
    u32   rear;
};

/*********************************函数声明*************************************/
u8 fifo_Init(struct fifo_data *head, u8 *buf, u32 len); //队列初始化
void fifo_Rst(struct fifo_data *head);                        //清空队列
u32 fifo_validSize(struct fifo_data *head);     //数据可用空间大小
u8 fifo_empty(struct fifo_data *head);        //队空判断
u8 fifo_puts(struct fifo_data *head, u8 *data, u32 len);
u8 fifo_gets(struct fifo_data *head, u8 *data, u32 len);
u8 fifo_putc(struct fifo_data *head, u8 data);
u8 fifo_getc(struct fifo_data *head, u8 *data);
u32 fifo_find(struct fifo_data *head, const u8 *data, u32 len);
u8 fifo_cmp(const struct fifo_data *fifo, u32 seat, const u8 *cmp, u32 cmpsize);
u8 fifo_get_frame(struct fifo_data *head, u8 *data, u32 *len);
                            
#endif 

