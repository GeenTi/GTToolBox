//
//  GTToolBox.h
//  GTToolBox
//
//  Created by WMYeah on 2017/11/10.
//  Copyright © 2017年 GeenTi. All rights reserved.
//



#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

#import "GTAppDefines.h"

#import "GTFuncExtension.h"

#import "GTCategorys.h"

#import "GTEncryption.h"

#import "GTNetworkServices.h"

@interface GTToolBox : NSObject

/**
 获取版本号

 @return 返回版本号字符串
 */
+ (NSString *)GT_Get_GTToolsBox_Version;


/*!
 *  计算字符串所在Label 中的宽度
 *
 *  @param content 计算的内容
 *  @param height  计算的高度
 *  @param font    font字体大小
 *
 *  @return 返回宽度
 */
+ (CGFloat)GT_GetWidthWithContent:(NSString *)content height:(CGFloat)height font:(CGFloat)font;


/**
 检查文本框有无内容

 @param text 文本框
 @return 返回认证结果
 */
+ (BOOL)GT_CheckText:(UITextField *)text;


/**
 检查手机号是否合法

 @param phoneNumber 手机号
 @return 返回认证结果
 */
+ (BOOL)GT_CheckPhoneNumber:(NSString *)phoneNumber;



@end
