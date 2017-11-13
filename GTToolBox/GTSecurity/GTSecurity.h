//
//  GTSecurity.h
//  GTToolBox
//
//  Created by WMYeah on 2017/11/13.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface GTSecurity : NSObject
//32位MD5加密方式
/**
 32位 MD5 加密

 @param srcString 欲加密的字符串
 @return 返回32位加密结果字符串
 */
+ (NSString *)GT_MD5_32Bit_Encription_With_SRCString:(NSString *)srcString;

@end
