//
//  GTEncryptionSec.c
//  GTToolBox
//
//  Created by WMYeah on 15/8/27.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef byte
#define byte unsigned char
#endif

//gcc -shared  -fPIC -o ../libzxsec.so zx_sec.c zx_des.c zx_md5.c zx_base64.c zx_basefunc.c
//gcc -c zx_sec.c zx_des.c zx_md5.c zx_base64.c zx_basefunc.c
//ar -cr ../libzzdsec.a zx_sec.o zx_des.o zx_md5.o zx_base64.o zx_basefunc.o
//arm-linux-gcc -shared  -fPIC -o libzxsec.so zx_sec.c zx_des.c zx_md5.c zx_base64.c zx_basefunc.c


extern void ZX_ASCToBCD(byte *bcd_buf,byte *asc_buf,int asclen);
extern int ZX_3desEncryptionText(unsigned char *inputStr, unsigned char *output, unsigned char *doubleKey);
extern int ZX_3desDecryptionText(unsigned char *inputBuff,int inputLen, unsigned char *output, unsigned char *doubleKey);
extern int encode(char * base64code, const char * src, int src_len) ;
extern int decode(char * buf, const char * base64code, int src_len) ;
extern void ZX_MD5HexString32(char *inString,char *md5String);


int GT_encryptionStr(char *inputStr, char *outputStr, char *keyString)
{
    char md5String[33];
    char md5String2[33];
    char key[33];
    char *output;
    int len=(int)strlen(inputStr);
    
    output=(char *)malloc(len+8+1);
    memset(output,0,len+8+1);
    ZX_MD5HexString32(keyString,md5String);
    ZX_MD5HexString32(md5String,md5String2);
    ZX_ASCToBCD((unsigned char*)key,(unsigned char*)md5String2,32);
    ZX_3desEncryptionText((unsigned char*)inputStr,(unsigned char*)output,(unsigned char*)key);
    
    encode(outputStr,output, ((len+7)/8)*8);
    
    free(output);
    
    return (int)(strlen(outputStr));
}

int GT_decryptionStr(char *inputStr, char *outputStr, char *keyString)
{
    char md5String[33];
    char md5String2[33];
    char key[33];
    char *input;
    int len=(int)strlen(inputStr);
    int len2;
    
    input=(char *)malloc(len);
    memset(input,0,len);
    len2 = decode(input,inputStr,len);
    
    memset(outputStr+len2,0,8);
    ZX_MD5HexString32(keyString,md5String);
    ZX_MD5HexString32(md5String,md5String2);
    ZX_ASCToBCD((unsigned char*)key,(unsigned char*)md5String2,32);
    
//    printf("\nkeyString = %s\nBCDComplate = %s\nmd5String2 = %s\n",keyString,key,md5String2);

    ZX_3desDecryptionText((unsigned char*)input,len2,(unsigned char*)outputStr,(unsigned char*)key);
//    printf("\n3DESCo input = %s\n3DESCo outPut = %s\n",input,outputStr);

    free(input);

    return (int)(strlen(outputStr));
}

