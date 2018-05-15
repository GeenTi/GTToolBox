//
//  GTEncryption.h
//  GTToolBox
//
//  Created by WMYeah on 15/8/25.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GTEncryption : NSObject

/**
 加密字符串

 @param waitingEncryptionString 待加密字符串
 @param keyString 加密字符串所用的Key
 @return 返回加密结果
 */
+ (NSString *)GT_encryptionStrWithWaitingEncryptionString:(NSString *)waitingEncryptionString keyString:(NSString *)keyString;

/**
 解密数据

 @param waitingDecryptionString 待解密字符串
 @param keyString 解密字符串所用的Key
 @return 返回解密结果
 */
+ (NSString *)GT_decryptionStrWithWaitingDecryptionString:(NSString *)waitingDecryptionString keyString:(NSString *)keyString;

/**
 32位 MD5 加密
 
 @param srcString 欲加密的字符串
 @return 返回32位加密结果字符串
 */
+ (NSString *)GT_MD5_32Bit_Encription_With_SRCString:(NSString *)srcString;




@end
