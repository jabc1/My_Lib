/***************************Copyright(C) Nobu*********************************
File name  : object.c
Description: check the communication data frame is or not my message
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2017-12-22
Modify     : 
Modify Time: 
*****************************************************************************/
#include "object.h"

/******************************************************************************
Function  : u8 Object_Check(struct comdata* cdata, u32 len)
Describes : check data frame is or not my msg
Input     : cdata, wanted to check data frame
            len,   data frame length
Output    : 0-suc, 1-fail
Author    : Joey
Time      : 2017-12-22
******************************************************************************/
MsgResult_t Object_Check(struct comdata* cdata, u32 len)
{
	//check serial num is or not repeat?

	//check object is or not mine
	if(cdata->addrdest == ADDRESS)
	{
		return COMPLETE;
	}

	return NO_EXE;
}




