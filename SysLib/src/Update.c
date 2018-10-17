/******************************Copyright(C) Nubo*******************************
File name  : Update.c
Description: program update execute function
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2017-12-23
Modify     : 
Modify Time: 
******************************************************************************/

#include "Update.h"

struct UpdateFlash UpdateF;

/******************************************************************************
Function   : void GenerateSystemReset(void)
Description: system software reset
Input      : void
Output     : void
Author     : Joey
Time       : 2017-12-23
******************************************************************************/
void GenerateSystemReset(void) 
{ 
//  __ASM("MOV R0, #1"); 
//  __ASM("MSR FAULTMASK, R0"); 
//  SCB->AIRCR = 0x05FA0004; 
  for(;;); 
}

/******************************************************************************
Function   : void SetProgramStatus(void)
Description: set program update mode flag
Input      : void
Output     : void
Author     : Joey
Time       : 2017-12-23
******************************************************************************/
void SetProgramStatus(void)
{
	UpdateF.flag = PROGRAM_UPGRADE_MODE;//upgrade mode
//	UpdateF.type = 0x03;
//	UpdateF.ver  = 0x11;

//	Erase_FLASH_Parts(UPGRADE_FLAG_FLASH_ADDR);
//	FLASH_Program(UPGRADE_FLAG_FLASH_ADDR, (u8 *)&UpdateF, sizeof(UpdateF));
}



