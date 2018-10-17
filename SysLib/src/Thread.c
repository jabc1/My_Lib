/******************************Copyright(C) Nubo*******************************
File name  : Thread.c
Description: Thread implementation function 
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#include "NuboLib.h"
#include "Thread.h"

//Private type of data define
#pragma pack(1)
struct thread_data
{
    u8 flag;            //运行标识
    u8 con;             //运行条件
    u16 cnt;            //运行次数
    u32 frep;           //运行周期
    u32 count_time ;    //线程执行的等待时间 yanhuan adding 2015/10/27
    void *fun;          //运行函数指针
};

struct thread_manage
{
    u16 runCnt;         //当前线程运行数
    u16 hangCnt;        //线程挂起数    
    struct thread_data thread[THREAD_NUM_MAX];
};
#pragma pack()

//Private Macro define
#define THREAD_TOTAL    (thread.runCnt + thread.hangCnt)    //线程总数

//Private Variable define
static struct thread_manage   thread;

//Private function declaration
static u8 Thread_Check(u32 start, u32 end, void *fun);

/*******************************************************************************
函 数 名:  Thread_Init
功能说明:  线程数据初始化
参    数:  无
返回  值:  无
*******************************************************************************/
void Thread_Init(void)
{
    *(u32*)&thread.runCnt = 0;   //线程总数置空
}

/*******************************************************************************
函 数 名:  Thread_Login
功能说明:  线程注册 
参    数:  fun: 线程名
           执行描述
返回  值:  注册结果, 
*******************************************************************************/
u32 Thread_Login(ThreadCon_t con, u16 cnt, u32 frep, void * fun)
{
    u32 i;
    
    ERRR(THREAD_TOTAL >= THREAD_NUM_MAX, return 0);     //线程空间
    if (Thread_Check(0, THREAD_TOTAL, fun) == 0)        //线程没有出现在线程表中
    {
        memmove(&thread.thread[thread.runCnt+1], &thread.thread[thread.runCnt],     //空闲一个空间，给新建线程
                    sizeof(struct thread_data)*(thread.hangCnt));   
        i = thread.runCnt;
        thread.runCnt++;
        thread.thread[i].flag = 0;
    }   
    else 
    {
        Thread_Wake(fun);   //线程换醒
        i = Thread_Check(0, THREAD_TOTAL, fun) - 1;
    }   
   
    thread.thread[i].con = con;
    thread.thread[i].fun = fun;
    if (con == ONCEDELAY)   //单次延时线程
    {
        if (0 == frep)
        {
            frep++;
        }
        cnt = 1;
        thread.thread[i].flag = 0;
    }
    thread.thread[i].cnt = cnt;
    thread.thread[i].frep = frep;
    thread.thread[i].count_time = 0; //yanhuan adding 2015/10/28
    
    return 1;
}

/*******************************************************************************
函 数 名:  Thread_Logout
功能说明:  线程注销 
参    数:  fun: 线程名
返 回 值:  无
*******************************************************************************/
void Thread_Logout(void * fun)
{
    u32 i = Thread_Check(0, THREAD_TOTAL, fun);

    if (i)    //找到线程位置
    {
        memmove(&thread.thread[i-1], &thread.thread[i], 
                    sizeof(struct thread_data)*(THREAD_TOTAL - i));
        
        if (i > thread.runCnt)  //线程位于运行空间
        {
            thread.hangCnt--;
        }
        else
        {
            thread.runCnt--; 
        }
    }
}

/*******************************************************************************
函 数 名:  Thread_Hang
功能说明:  线程挂起 
参    数:  fun:线程名
返回  值:  无
*******************************************************************************/
void Thread_Hang(void * fun)
{
    u32 i = Thread_Check(0, thread.runCnt, fun);

    if (i)    //线程位于运行线程空间
    {
        struct thread_data th;
        
        memcpy(&th, &thread.thread[i-1], sizeof(struct thread_data)); 
        memmove(&thread.thread[i-1], &thread.thread[i], 
                    sizeof(struct thread_data)*(thread.runCnt - i));
        memcpy(&thread.thread[--thread.runCnt], &th, sizeof(struct thread_data));
        thread.hangCnt++;
    }
}

/*******************************************************************************
函 数 名:  Thread_Wake
功能说明:  线程换醒
参    数:  fun:线程名
返回  值:  无
注    意:  本功能只能对已有线程的操作 
*******************************************************************************/
void Thread_Wake(void * fun)
{
    u32 i = Thread_Check(thread.runCnt, THREAD_TOTAL, fun);

    if (i)    //找到线程位置
    {
        if ((i - thread.runCnt) > 1)    //i不是紧靠运行线程
        {
            struct thread_data th;
            memcpy(&th, &thread.thread[i-1], sizeof(struct thread_data)); 
            memmove(&thread.thread[thread.runCnt + 1], &thread.thread[thread.runCnt], //腾出存储空间
                        sizeof(struct thread_data)*(i - thread.runCnt));
            memcpy(&thread.thread[thread.runCnt], &th,  sizeof(struct thread_data));
        }
        thread.runCnt++;
        thread.hangCnt--;
    }
}

/*******************************************************************************
函 数 名:  Thread_Process
功能说明:  线程处理
参    数:  无
返回  值:  无
*******************************************************************************/
void Thread_Process(void)
{
    struct thread_data *pThread = NULL;
    
    for (pThread = &thread.thread[0]; pThread < &thread.thread[thread.runCnt]; pThread++)
    {
        if (pThread->flag)
        {
            void *fun = pThread->fun;;
            
            pThread->flag = 0;
            switch (pThread->con)
            {
                case ONCEDELAY: pThread->flag = 1;
                case MANY:      if (!pThread->cnt--)
                                {   
                                    Thread_Logout(fun);
                                    pThread --;
                                    break;
                                }
                     
                case FOREVER:   ((fun1)(fun))();
                     break;             
                case RESULT:    if (((fun2)(fun))() == 0)  //线程运行返回失败
                                {
                                    Thread_Logout(fun);
                                    pThread --;
                                }
                    break;
                default : break;
            }
        }
    }
}
    
/*******************************************************************************
函 数 名:  Thread_RunCheck
功能说明:  线程运行条件核对
参    数:  无
返回  值:  无
*******************************************************************************/
void Thread_RunCheck(void)
{
    struct thread_data *pThread;

    for (pThread = &thread.thread[0]; pThread < &thread.thread[thread.runCnt]; pThread++)
    {
        if ((++pThread->count_time)>=(pThread->frep))//yanhuan modify 2015/10/28
        {
            pThread->count_time = 0;  
            pThread->flag = 1;
        }
    }
}

/*******************************************************************************
函 数 名:   Thread_Check
功能说明:   线程核对
参    数:   fun:     线程名
            start:  起始线程位置
            end:    终止线程位置
返回  值:   0(没有)/(1~THREAD_UNM)线程所处位置
*******************************************************************************/
u8 Thread_Check(u32 start, u32 end, void *fun)
{
    u32 i; 
    
    for (i = start; i < end;)
    {
        if (thread.thread[i++].fun == fun)
        {
            return i;
        }
    }
    
    return 0;
}

/*******************************************************************************
函 数 名:  ThreadState_t Thread_Query(void *fun)
功能说明:  线程查询函数
参    数:  fun：线程函数指针
返 回 值:  NO_EXIST_STATE:不在任务链表中;RUNNING_STATE：在运行链表中;PENDING_STATE：在挂起链表中
*******************************************************************************/
ThreadState_t Thread_Query(void *fun)    //Jay Add 2015.11.17
{
    u8 Taskpos = Thread_Check(0, THREAD_TOTAL, fun);
    if(0 == Taskpos)
    {
        return NO_EXIST_STATE;
    }
    else if(Taskpos < thread.runCnt + 2)
    {
        return RUNNING_STATE;
    }
    else
    {
        return PENDING_STATE;
    }
}

/**************************Copyright Nubo 2018-01-03*************************/

