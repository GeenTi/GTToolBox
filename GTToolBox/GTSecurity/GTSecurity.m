//
//  GTSecurity.m
//  GTToolBox
//
//  Created by WMYeah on 2017/11/13.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#import "GTSecurity.h"
#import <CommonCrypto/CommonDigest.h>
#import <objc/runtime.h>

@implementation GTSecurity
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
