/******************************Copyright(C) Nubo*******************************
File name  : sysexeattr.c
Description: this source used for system command execute
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2017-12-23
Modify     : 
Modify Time: 
******************************************************************************/

#ifndef _SYSEXEATTR_H
#define _SYSEXEATTR_H

#include "NbType.h"
#include "cmdProcess.h"

//
/****************************Variable Declaration*****************************/
extern const struct attr_exe_data SysAttrTable[];

/****************************Function Declaration*****************************/ 
MsgResult_t Set_TemperatureUnit_Attr(u8* sdata, u16 slen, u8* rlen, u8* rpara);
MsgResult_t Get_TemperatureUnit_Attr(u8* sdata, u16 slen, u8* rlen, u8* rpara);
//MsgResult_t Set_SampleInterval_Att(u8* sdata, u8* rlen, u8* rpara);
//MsgResult_t Get_SampleInterval_Att(u8* sdata, u8* rlen, u8* rpara);
//MsgResult_t Set_StorageStrategy_Attr(u8* sdata, u8* rlen, u8* rpara);
//MsgResult_t Get_StorageStrategy_Attr(u8* sdata, u8* rlen, u8* rpara);
//MsgResult_t Set_AlarmThreshold_Attr(u8* sdata, u8* rlen, u8* rpara);
//MsgResult_t Get_AlarmThreshold_Attr(u8* sdata, u8* rlen, u8* rpara);
//MsgResult_t Get_LockStatus_Attr(u8* sdata, u8* rlen, u8* rpara);
//MsgResult_t Get_HistorySampleValue_Att(u8* sdata, u8* rlen, u8* rpara);
//MsgResult_t Set_ScreenContent_Attr(u8* sdata, u8* rlen, u8* rpara);
//MsgResult_t Set_HandOffAlarm_Attr(u8* sdata, u8* rlen, u8* rpara);

MsgResult_t Set_ProgramUpdate_Attr(u8* sdata, u16 slen, u8* rlen, u8* rpara);
u8 GetAttrNum(void);

#endif
