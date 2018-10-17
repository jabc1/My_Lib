/******************************Copyright(C) Nubo*******************************
File name  : MsgPackage.c
Description: message package
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-4
Modify     : 
Modify Time: 
******************************************************************************/

#include "MsgPackage.h"
#include "uartfifo.h"
#include "NbLibConfig.h"
#include "NbType.h"

/******************************************************************************
Function   : void Msg_Feedback(struct comdata *p_msg)
Description: receive message processed feed back message
Input      : p_msg - received message
Output     : void
Author     : Joey
Time       : 2018-1-4
******************************************************************************/
void Msg_Feedback(struct comdata *p_msg)
{
	p_msg->addrsrc  = ADDRESS;
	p_msg->addrdest = p_msg->addrsrc;
	
	cmd_put(&senduart1fifo, (u8 *)p_msg, p_msg->length);
}


