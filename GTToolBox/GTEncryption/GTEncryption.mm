//
//  GTEncryption.mm
//  GTToolBox
//
//  Created by WMYeah on 15/8/25.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//

#import "GTEncryption.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#import <CommonCrypto/CommonDigest.h>
#import <objc/runtime.h>
#import "GTEncryptionC.h"




@implementation GTEncryption

+ (NSString *)GT_encryptionStrWithWaitingEncryptionString:(NSString *)waitingEncryptionString keyString:(NSString *)keyString
{
    if (!waitingEncryptionString) {
        return nil;
    }
    
    char * resultChar = new char [1024*10];
    memset(resultChar,0,1024*10);

//    char    *resultChar[1024*10];
    
    int     retCode = 0;
    
    retCode = GT_encryptionStr((char *)[waitingEncryptionString cStringUsingEncoding:NSUTF8StringEncoding], (char *)resultChar, (char *)[keyString cStringUsingEncoding:NSUTF8StringEncoding]);
    
    NSString *enString = [NSString stringWithCString:(const char *)resultChar encoding:NSUTF8StringEncoding];
    delete[] resultChar;
    
    return enString;
}

+ (NSString *)GT_decryptionStrWithWaitingDecryptionString:(NSString *)waitingDecryptionString keyString:(NSString *)keyString
{
    if (!waitingDecryptionString) {
        return nil;
    }
    
    char * resultChar = new char [1024*10];
    memset(resultChar,0,1024*10);
    
//    char    *resultChar[1024*10];

    int     retCode = 0;
    
    retCode = GT_decryptionStr((char *)[waitingDecryptionString cStringUsingEncoding:NSUTF8StringEncoding], (char *)resultChar, (char *)[keyString cStringUsingEncoding:NSUTF8StringEncoding]);
    
    NSString *decString = [NSString stringWithCString:(const char *)resultChar encoding:NSUTF8StringEncoding];
    delete[] resultChar;
    
    return decString;
}


//32位MD5加密方式
+ (NSString *)GT_MD5_32Bit_Encription_With_SRCString:(NSString *)srcString
{
    if (!srcString) {
        return nil;
    }
    const char *cStr = [srcString UTF8String];
    unsigned char digest[CC_MD5_DIGEST_LENGTH];
    CC_MD5( cStr, (int)strlen(cStr), digest );
    NSMutableString *result = [NSMutableString stringWithCapacity:CC_MD5_DIGEST_LENGTH * 2];
    for(int i = 0; i < CC_MD5_DIGEST_LENGTH; i++)
        [result appendFormat:@"%02x", digest[i]];
    
    return result;
}



@end
