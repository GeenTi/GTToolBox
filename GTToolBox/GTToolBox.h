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

#import "GTSecurity.h"

#import "GTCategorys.h"

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



@end
