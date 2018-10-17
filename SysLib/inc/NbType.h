/******************************Copyright(C) Nubo*******************************
File name  : nbtype.h
Description: define data format name
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-2
Modify     : 
Modify Time: 
******************************************************************************/
#ifndef _NB_TYPE_H_
#define _NB_TYPE_H_


#define TRUE                      		(1)
#define FALSE                     		(0)

#ifndef NULL
#define NULL                      		((void*)(0))
#endif

#define CLEAR                       	(0xFF)

#define offsetof(TYPE, MEMBER) 			((u32) &((TYPE *)0)->MEMBER)                
#define NB_DIM(array_) 					(sizeof(array_) / sizeof((array_)[0]))		
#define NUM_ROUND(a,b)					(((a)/(b))+ ((0==((a)%(b)))?(0):(1)))		

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
//typedef signed long    s32;
typedef signed short   s16;
typedef signed char    s8;

typedef volatile unsigned int   vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned int  const vuc32;  /* Read Only */
typedef volatile unsigned short const vuc16;  /* Read Only */
typedef volatile unsigned char  const vuc8;   /* Read Only */

#endif

