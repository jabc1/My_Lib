/******************************Copyright(C) Nubo*******************************
File name  : NuboLib.h
Description: Nubo create lib source
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#ifndef __NuboLIB_H
#define __NuboLIB_H

/*容错宏*/
#define ERRR(conf, ret)      do              \
                            {                \
                                if (conf)    \
                                {            \
                                    ret;     \
                                }            \
                            } while(0) 
                            
#define ABS(i, j)       (((i) > (j)) ? ((i) - (j)) : ((j) - (i)))       //获取绝对值
//
                                
void memcpy(void *dest, const void *src, unsigned int num); //内存考备
char memcmp(void *dest,  const void *src, unsigned int num);    //内存比较
void memmove(void *dest,  const void *src, unsigned int num);   //内存移动
void memset(void *dest, unsigned char const val, unsigned int num); //内存设置 
void* memfind(void *dest, unsigned int dLen, void *src, unsigned int sLen);                         
void memcharget(void *dest, unsigned char *len, void const *src, unsigned int size);

#endif //NuboLib.h end
