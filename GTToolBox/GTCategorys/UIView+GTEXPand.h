//
//  UIView+GTEXPand.h
//  GTToolBox
//
//  Created by WMYeah on 2017/11/14.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIView (GTEXPand)

/**
 获取渐变色 Layer
 
 @param startColor 起始颜色
 @param endColor 结束颜色
 */
- (CALayer * )GT_Get_GradientColor_With_StartColor:(UIColor *)startColor EndColor:(UIColor *)endColor;


@end
