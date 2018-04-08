//
//  GTEncryptionBaseFunc.c
//  GTToolBox
//
//  Created by WMYeah on 15/8/27.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#ifndef byte
#define byte unsigned char
#endif



/**********************************************
 * 函数原型: byte abcd_to_asc(byte abyte);
 * 函数功能: 单个字符转换为ASCII
 * 输入参数: abyte  欲转换为ASCII的字符
 * 输出参数: 无
 * 函数返回值: ASCII值
 * 函数调用:
 * 修改时间:
 **********************************************/
byte abcd_to_asc(byte abyte)
{
    if (abyte <= 9)
        abyte += '0';
    else
        abyte += ('A' - 10);
    
    return abyte;
}

/**********************************************
 * 函数原型: byte aasc_to_bcd(byte asc);
 * 函数功能: 单个字符转换为BCD
 * 输入参数: asc  欲转换为BCD的字符
 * 输出参数: 无
 * 函数返回值: BCD值
 * 函数调用:
 * 修改时间:
 **********************************************/
byte aasc_to_bcd(byte asc)
{
    byte bcd;
    
    if ((asc >= '0') && (asc <= '9'))
        bcd = asc - '0';
    else if ((asc >= 'A') && (asc <= 'F'))
        bcd = asc - 'A' + 10;
    else if ((asc >= 'a') && (asc <= 'f'))
        bcd = asc - 'a' + 10;
    else if ((asc > 0x39) && (asc <= 0x3f))
        bcd = asc - '0';
    else if (asc == 0x00)   //防止字符串结束标志转换成0xff
        bcd = 0;
    else
        bcd = 0x0f;
    
    return bcd;
}

/**************************************************************************
 * 函数原型: void BCDToASC(byte *asc_buf, byte *bcd_buf, int asclen);
 * 函数功能: 将BCD字符串转换为ASC字符串
 * 输入参数: bcd_buf  BCD字符串
 *           asclen   ASC字符串长度
 * 输出参数: asc_buf  ASC字符串
 * 函数返回值: 无
 * 函数调用: abcd_to_asc()  单个字符转换为ASCII
 * 修改时间:
 **************************************************************************/
void ZX_BCDToASC(byte *asc_buf,byte *bcd_buf,int asclen)
{
    int i, j;
    
    j = 0;
    for (i = 0; i < asclen / 2; i++)
    {
        asc_buf[j] = (bcd_buf[i] & 0xf0) >> 4;
        asc_buf[j] = abcd_to_asc(asc_buf[j]);      //将单个字符转换为ASCII
        j++;
        asc_buf[j] = bcd_buf[i] & 0x0f;
        asc_buf[j] = abcd_to_asc(asc_buf[j]);
        j++;
    }
    
    if (asclen % 2)
    {
        asc_buf[j] = (bcd_buf[i] & 0xf0) >> 4;
        asc_buf[j] = abcd_to_asc(asc_buf[j]);
    }
    asc_buf[asclen]=0;
}

/**********************************************************************
 * 函数原型: void ASCToBCD(byte *bcd_buf, byte *asc_buf, int asclen);
 * 函数功能: 将ASC字符串转换为BCD字符串
 * 输入参数: asc_buf  ASC字符串
 *           asclen   ASC字符串长度
 * 输出参数: bcd_buf  BDC字符串
 * 函数返回值: 无
 * 函数调用: aasc_to_bcd()  单个字符转换为BCD
 * 修改时间:
 **********************************************************************/
void ZX_ASCToBCD(byte *bcd_buf,byte *asc_buf,int asclen)
{
    int i, j;
    
    j = 0;
    
    for (i = 0; i < (asclen + 1) / 2; i++)
    {
        bcd_buf[i] = aasc_to_bcd(asc_buf[j++]);
        bcd_buf[i] = ((j >= asclen) ? 0x00 : aasc_to_bcd(asc_buf[j++])) + (bcd_buf[i] << 4);
    }
}








int ZX_getDateTime(char *strDate,char *strTime)
{
    time_t	local;
    struct	tm *t;
    
    time(&local);
    t = (struct tm*)localtime(&local);
    
    sprintf(strDate,"%04d%02d%02d",t->tm_year+1900, t->tm_mon+1,t->tm_mday);
    strDate[8] = 0;
    
    sprintf(strTime,"%02d%02d%02d",t->tm_hour, t->tm_min, t->tm_sec);
    strTime[6] = 0;
    
    return 0;
}










/*****************************************************
 * 函数原型: int bcdtoi(byte bcd_value);
 * 函数功能: 单个BCD字符转换为整型
 * 输入参数: bcd_value  单个BCD值
 * 输出参数: 无
 * 函数返回值: 单个BCD转换为整型的值
 * 函数调用:
 * 修改时间:
 *****************************************************/
int bcdtoi(byte bcd_value)
{
    return (((bcd_value >> 4) & 0x0f) * 10 + (bcd_value & 0x0f));
}








/*************************************************************************
 * 函数原型:	void string_fill_right(char *buffer, int max_len, char v);
 * 函数功能:	用指定的字符补齐原字符串(修改原内容)
 * 输入参数:	buffer		需要补齐操作的原字符串
 max_len		需要补齐的最终长度
 *				v			用于补齐的字符
 * 输出参数:	buffer		得到的最终字符串
 * 函数返回值:	无
 * 函数调用:
 * 修改时间:
 *************************************************************************/
char * string_fill_right(char *buffer, int max_len, char v)
{
    int len = -1;
    if((len = (int)strlen(buffer)) >= max_len)
        return buffer;
    
    memset(buffer + len, v, max_len - len);
    return buffer;
}

/*************************************************************************
 功能参考：string_fill_right
 *************************************************************************/
char * string_fill_left(char *buffer, int max_len, char v)
{
    char tmp[1024];
    int len = -1;
    if((len = (int)strlen(buffer)) >= max_len)
        return buffer;
    
    memset(tmp, 0, sizeof(tmp));
    memcpy(tmp, buffer, len);
    memset(buffer, v, max_len - len);
    memcpy(buffer + (max_len - len), tmp, len);
    return buffer;
}




int ZX_readFileBuffer(char *filename,char *buffer,int len)
{
    FILE *fp = NULL;
    int readLen;
    
    fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        return 0;
    }
    readLen=(int)fread(buffer, 1, len, fp);
    
    fclose(fp);
    
    return readLen;
}

int ZX_writeFileBuffer(char *filename,char *buffer,int len)
{
    
    FILE *fp = NULL;
    int writeLen;
    
    fp = fopen(filename, "wb");
    if(fp == NULL)
    {
        return -1;
    }
    writeLen=(int)fwrite(buffer, 1, len, fp);
    
    fclose(fp);
    
    return writeLen;
    
}


