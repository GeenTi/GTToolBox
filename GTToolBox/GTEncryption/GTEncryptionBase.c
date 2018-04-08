//
//  GTEncryptionBase.c
//  GTToolBox
//
//  Created by WMYeah on 15/8/27.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

// 从双字中取单字节
#define B0(a) (a & 0xFF)
#define B1(a) (a >> 8 & 0xFF)
#define B2(a) (a >> 16 & 0xFF)
#define B3(a) (a >> 24 & 0xFF)

#define BASE64_MAXLINE  76
#define EOL "\r\n"

char GetB64Char(int index)
{
    const char szBase64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    if (index >= 0 && index < 64)
        return szBase64Table[index];
    return '=';
}
int getBase64BufferSize(int nInputSize)
{
    int nOutSize = (nInputSize+2)/3*4;                    // 3:4 conversion ratio
    nOutSize += strlen(EOL)*nOutSize/BASE64_MAXLINE + 3;  // Space for newlines and NUL
    return nOutSize;
}


// 编码后的长度一般比原文多占1/3的存储空间，请保证base64code有足够的空间
int encode(char * base64code, const char * src, int src_len)
{
    int len = 0;
    unsigned char* psrc = (unsigned char*)src;
    char * p64 = base64code;
    int i;
    unsigned long ulTmp;
    register int b0;
    register int b1;
    register int b2;
    register int b3;
    int rest;
    int j;
    
    if (src_len == 0)
        src_len = (int)strlen(src);
    
    for (i = 0; i < src_len - 3; i += 3)
    {
        ulTmp = *(unsigned long*)psrc;
        b0 = GetB64Char((B0(ulTmp) >> 2) & 0x3F);
        b1 = GetB64Char((B0(ulTmp) << 6 >> 2 | B1(ulTmp) >> 4) & 0x3F);
        b2 = GetB64Char((B1(ulTmp) << 4 >> 2 | B2(ulTmp) >> 6) & 0x3F);
        b3 = GetB64Char((B2(ulTmp) << 2 >> 2) & 0x3F);
        *((unsigned long*)p64) = b0 | b1 << 8 | b2 << 16 | b3 << 24;
        len += 4;
        p64  += 4;
        psrc += 3;
    }
    
    // 处理最后余下的不足3字节的饿数据
    if (i < src_len)
    {
        rest = src_len - i;
        ulTmp = 0;
        for ( j = 0; j < rest; ++j)
        {
            *(((unsigned char*)&ulTmp) + j) = *psrc++;
        }
        
        p64[0] = GetB64Char((B0(ulTmp) >> 2) & 0x3F);
        p64[1] = GetB64Char((B0(ulTmp) << 6 >> 2 | B1(ulTmp) >> 4) & 0x3F);
        p64[2] = rest > 1 ? GetB64Char((B1(ulTmp) << 4 >> 2 | B2(ulTmp) >> 6) & 0x3F) : '=';
        p64[3] = rest > 2 ? GetB64Char((B2(ulTmp) << 2 >> 2) & 0x3F) : '=';
        p64 += 4;
        len += 4;
    }
    
    *p64 = '\0';
    
    return len;
}


int GetB64Index(char ch)
{
    int index = -1;
    if (ch >= 'A' && ch <= 'Z')
    {
        index = ch - 'A';
    }
    else if (ch >= 'a' && ch <= 'z')
    {
        index = ch - 'a' + 26;
    }
    else if (ch >= '0' && ch <= '9')
    {
        index = ch - '0' + 52;
    }
    else if (ch == '+')
    {
        index = 62;
    }
    else if (ch == '/')
    {
        index = 63;
    }
    
    return index;
}

// 解码后的长度一般比原文少用占1/4的存储空间
int decode(char * buf, const char * base64code, int src_len)
{
    int len = 0;
    unsigned char* psrc = (unsigned char*)base64code;
    char * pbuf = buf;
    int i;
    unsigned long ulTmp;
    register int b0;
    register int b1;
    register int b2;
//    register int b3;
    int rest;
    int j;
    
    if (src_len == 0)
        src_len = (int)strlen(base64code);
    
    for (i = 0; i < src_len - 4; i += 4)
    {
        ulTmp = *(unsigned long*)psrc;
        
        b0 = (GetB64Index((char)B0(ulTmp)) << 2 | GetB64Index((char)B1(ulTmp)) << 2 >> 6) & 0xFF;
        b1 = (GetB64Index((char)B1(ulTmp)) << 4 | GetB64Index((char)B2(ulTmp)) << 2 >> 4) & 0xFF;
        b2 = (GetB64Index((char)B2(ulTmp)) << 6 | GetB64Index((char)B3(ulTmp)) << 2 >> 2) & 0xFF;
        
        *((unsigned long*)pbuf) = b0 | b1 << 8 | b2 << 16;
        psrc  += 4;
        pbuf += 3;
        len += 3;
    }
    
    // 处理最后余下的不足4字节的饿数据
    if (i < src_len)
    {
        rest = src_len - i;
        ulTmp = 0;
        for (j = 0; j < rest; ++j)
        {
            *(((unsigned char*)&ulTmp) + j) = *psrc++;
        }
        
        b0 = (GetB64Index((char)B0(ulTmp)) << 2 | GetB64Index((char)B1(ulTmp)) << 2 >> 6) & 0xFF;
        *pbuf++ = b0;
        len  ++;
        
        if ('=' != B1(ulTmp) && '=' != B2(ulTmp))
        {
            b1 = (GetB64Index((char)B1(ulTmp)) << 4 | GetB64Index((char)B2(ulTmp)) << 2 >> 4) & 0xFF;
            *pbuf++ = b1;
            len  ++;
        }
        
        if ('=' != B2(ulTmp) && '=' != B3(ulTmp))
        {
            b2 = (GetB64Index((char)B2(ulTmp)) << 6 | GetB64Index((char)B3(ulTmp)) << 2 >> 2) & 0xFF;
            *pbuf++ = b2;
            len  ++;
        }
        
    }
    
    *pbuf = '\0'; 
    
    return len;
} 



