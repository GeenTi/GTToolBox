//
//  UIColor+GTEXPand.h
//  GTToolBox
//
//  Created by WMYeah on 2017/11/13.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIColor (GTEXPand)
/**
 通过 16进制RGB获取UIColor对象
 
 @param colorHexString 16进制RGB字符串
 @return 返回Color对象
 */
+ (UIColor *)GT_ColorWithHexString:(NSString *)colorHexString;

@end
