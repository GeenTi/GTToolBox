//
//  GTEncryption.mm
//  ZXFramework
//
//  Created by WMYeah on 15/8/25.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//

#import "GTEncryption.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern "C" {
    extern int GT_encryptionStr(char *inputStr, char *outputStr, char *keyString);
    
    extern int GT_decryptionStr(char *inputStr, char *outputStr, char *keyString);
};


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

@end
