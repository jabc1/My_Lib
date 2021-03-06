/******************************Copyright(C) Nubo*******************************
File name  : fifo.c
Description: fifo source code
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#include "fifo.h"
#include "NuboLib.h"

static u32 fifo_surplusSize(struct fifo_data *head); //队列剩余空间判断
static u8 fifo_full(struct fifo_data *head);         //队满判断

/*******************************************************************************
函 数 名：  fifo_Init
功能说明：  队列初始化
参    数：  *head:  队列头
            *data:  数据存储首地址
            len:    数据存储区域长度
返 回 值：  初始化结果 TRUE/FALSE
*******************************************************************************/
u8 fifo_Init(struct fifo_data *head, u8 *buf, u32 len)
{
    ERRR(head == NULL, return FALSE);
    head->data = buf;
    head->size = len;
    head->front = head->rear = 0;

    return TRUE;
}

/*******************************************************************************
函 数 名：  fifo_Clr
功能说明：  队列清空
参    数：  *head:  队列头
返 回 值：  无
*******************************************************************************/
void fifo_Rst(struct fifo_data *head)
{
    ERRR(head == NULL, return);
    head->front = 0;
    head->rear = 0;
}
/*******************************************************************************
函 数 名：  fifo_empty
功能说明：  判断队列是否为空
参    数：  *head:  队列头
返 回 值：  TRUE(队列为空)/FALSE
*******************************************************************************/
u8 fifo_empty(struct fifo_data *head)
{
    
    return ((head->front == head->rear) ? TRUE : FALSE);
}

/*******************************************************************************
函 数 名：  fifo_full
功能说明：  判断队列是否已满
参    数：  *head:  队列头
返 回 值：  TRUE(队列已满)/FALSE
*******************************************************************************/
static u8 fifo_full(struct fifo_data *head)
{
    
    return ((head->front == ((head->rear+1)%head->size)) ? TRUE : FALSE);
}

/*******************************************************************************
函 数 名：  fifo_surplusSize
功能说明：  判断队列剩余空间大小 
参    数：  *head:  队列头
返 回 值：  剩余空间大小(字符为单位)
*******************************************************************************/
static u32 fifo_surplusSize(struct fifo_data *head)
{

    return ((head->front > head->rear)
            ? (head->front - head->rear - 1)
            : (head->size + head->front - head->rear - 1));

}

/*******************************************************************************
函 数 名：  fifo_validSize
功能说明：  查询队列有效空间大小
参    数：  *head:  队列头
返 回 值：  剩余空间大小(字符为单位)
*******************************************************************************/
u32 fifo_validSize(struct fifo_data *head)
{

    return ((head->rear < head->front)
            ? (head->rear + head->size - head->front)
            : (head->rear - head->front));
}

/*******************************************************************************
函 数 名：  kfifo_puts
功能说明：  入队
参    数：  *head:  队列头
            *data:  入队数据
            len:    数据长度
返 回 值：  入队结果 TRUE/FALSE
*******************************************************************************/
u8 fifo_puts(struct fifo_data *head, u8 *data, u32 len)
{  
    u32 size;

    ERRR(head == NULL, return FALSE);
    ERRR(len > fifo_surplusSize(head), return FALSE); //判断队列中是否还有存储空间
    
    size = MIN(len, head->size - head->rear);
    memcpy(head->data + head->rear, data, size);
    memcpy(head->data, data + size, len - size);

    head->rear = (head->rear + len)%head->size;

    return TRUE;   
}

/*******************************************************************************
函 数 名：  kfifo_gets
功能说明：  出队
参    数：  *head:  队列头
            *data:  出队数据
            len:    出队数据长度
返 回 值：  出队结果 TRUE/FALSE
*******************************************************************************/
u8 fifo_gets(struct fifo_data *head, u8 *data, u32 len)
{
    u32 size;

    ERRR(head == NULL, return FALSE);
    ERRR(fifo_empty(head) == TRUE, return FALSE); //队列为空
    ERRR(len > fifo_validSize(head), return FALSE); //存储总数小于要读取的数

    size = MIN(len, head->size - head->front);
    memcpy(data, head->data + head->front, size);
    memcpy(data+size, head->data, len - size);

    head->front = (head->front + len)%head->size;

    return TRUE;   
}

/*******************************************************************************
函 数 名：  fifo_putc
功能说明：  入队一个字符
参    数：  *head:  队列头
            data:   要入队的数据
返 回 值：  入队结果 TRUE/FALSE
*******************************************************************************/
u8 fifo_putc(struct fifo_data *head, u8 data)
{
    ERRR(head == NULL, return FALSE);
    ERRR(fifo_full(head) == TRUE, return FALSE); //判断队列中是否还有存储空间

    head->data[head->rear] = data;

    head->rear = (++head->rear)%head->size;

    return TRUE;   
}

/*******************************************************************************
函 数 名：  kfifo_getc
功能说明：  出队一个字符
参    数：  *head:  队列头
            data:  出队数据
返 回 值：  出队结果 TRUE/FALSE
*******************************************************************************/
u8 fifo_getc(struct fifo_data *head, u8 *data)
{
    ERRR(head == NULL, return FALSE);
    ERRR(fifo_empty(head) == TRUE, return FALSE); //队列为空

    *data = head->data[head->front];
    head->front = (++head->front)%head->size;

    return TRUE;   
}

/*******************************************************************************
函 数 名：  fifo_get_frame
功能说明：  Get one frame from FIFO
参    数：  *head:  队列头
            *data:  出队数据
            len:    出队数据长度
返 回 值：  出队结果 TRUE/FALSE
author  :   Am.Peng
Date    :   2018-5-29
*******************************************************************************/
u8 fifo_get_frame(struct fifo_data *head, u8 *data, u32 *len)
{
    u32 size;
    u32 Length;
    u8 frame_head;

    ERRR(head == NULL, return FALSE);
    ERRR(fifo_empty(head) == TRUE, return FALSE); //队列为空

    do
    {
        if (!fifo_getc(head, &frame_head))
        {
            return FALSE;
        }
    }
    while (frame_head != 0x7E);//寻找数据头
    *data = 0x7E;
    
    //Get frame Length
    fifo_getc(head, &frame_head);
    Length = frame_head;
    *(data + 1) = frame_head;
    fifo_getc(head, &frame_head);
    Length += frame_head * 256;
    *(data + 2) = frame_head;
    
    if (!fifo_gets(head, data + 3, Length + 3))      //Length contain check region and pack tail
    {
        return FALSE;
    }
    
    *len = Length + 6;

    return TRUE;   
}

/*******************************************************************************
函 数 名：  fifo_Find
功能说明：  队列数据查找
参    数：  *head:  队列头
            *data:  数据匹配内容
            len:    匹配数据长度
返 回 值：  队列匹配指针，查找到的位置 
*******************************************************************************/
u32 fifo_find(struct fifo_data *head, const u8 *data, u32 len)
{
    u32 i, n;
    
    ERRR((NULL == head)||(NULL == data)||(0 == len), return 0);
    
    for (i = head->front, n = 0; i != head->rear; i = (1+i)%head->size)
    {
        if (head->data[i] == data[n])   //数据内容相等
        {
            if (++n == len) //匹配长度相等
            {
                n--;
                break;
            }
        }
        else
        {
            n = 0;
        }
    }
    
    return ((i+head->size - n)%head->size);
}

/*******************************************************************************
函 数 名：  fifo_cmp
功能说明：  队列数据比较
参    数：  fifo: 比较源
            seat:   位于fifo的开始比较位置
            cmp：    被比较数
            cmpsize:比较长度
返 回 值：  TRUE/FALSE
*******************************************************************************/
u8 fifo_cmp(const struct fifo_data *fifo, u32 seat, const u8 *cmp, u32 cmpsize)
{
    u32 i;

    ERRR((fifo->data == NULL)||(cmp == NULL), return FALSE);

    for (i = 0; i < cmpsize; i++)   //整个队列查找
    {
        if (fifo->data[(seat+i)%fifo->size] != *cmp++)
        {
            return FALSE;
        }
    }
    
    return TRUE;
}   


/**************************Copyright Nubo 2018-01-03*************************/

