/******************************Copyright(C) Nubo*******************************
File name  : crc.h
Description: check crc method  0x18005 X16+X15+X2+1
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#ifndef _CRC_H
#define _CRC_H
#include "NbType.h"

/**********************************º¯ÊýÉùÃ÷************************************/
u16 ChkCrcValue(u8 *buf, u16 len);
u16 ChkCrcValueEx(u8 *buf, u16 len, u16 FirstData);

#endif
/**************************Copyright Nubo 2018-01-03*************************/
