//
//  NSString+GTEXPand.h
//  GTToolBox
//
//  Created by WMYeah on 2017/9/21.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>

@interface NSString (GTEXPand)

/// 转换为图片
/// @param size 大小
/// @param backgroupColor 背景颜色
/// @param stringColor 文字颜色
- (UIImage *)GT_Convert_To_Image_WithFrame:(CGSize)size BackGroupColor:(UIColor *)backgroupColor StringColor:(UIColor *)stringColor;

@end
