/******************************Copyright(C) Nubo*******************************
File name  : Thread.h
Description: Thread implementation function 
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#ifndef __THREAD_H
#define __THREAD_H
#include "NbType.h"

#define THREAD_NUM_MAX 20

/*********************************数据类型定义********************************/
typedef enum
{
    ONCEDELAY   = 0,    //单次延时运行
    MANY        = 1,    //多次
    FOREVER     = 2,    //永久
    RESULT      = 3,    //按结果
}ThreadCon_t;           //线程驻存条件
 
typedef enum
{
    NO_EXIST_STATE = 0, //不在任务链表中   
    RUNNING_STATE,      //运行态   
    PENDING_STATE       //挂起态 
}ThreadState_t;

typedef void (*fun1)(void); 
typedef u8 (*fun2)(void);
 
/*********************************函数声明********************************/
void Thread_Init(void);     //线程初始化函数
u32 Thread_Login(ThreadCon_t con, u16 cnt, u32 frep, void * fun);   //线程注册
void Thread_Logout(void *fun);  //线程注销
void Thread_Process(void);      //线程运行
void Thread_RunCheck(void); //线程运行时间核对
void Thread_Hang(void * fun);   //线程挂起
void Thread_Wake(void * fun);   //线程换醒    
ThreadState_t Thread_Query(void *fun);//查询线程当前状态   //Jay Add 2015.11.17

#endif //Thread.h end
