//
//  UIView+GTEXPand.m
//  GTToolBox
//
//  Created by WMYeah on 2017/11/14.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#import "UIView+GTEXPand.h"

@implementation UIView (GTEXPand)

/**
 获取渐变色 Layer
 
 @param startColor 起始颜色
 @param endColor 结束颜色
 */
- (CALayer * )GT_Get_GradientColor_With_StartColor:(UIColor *)startColor EndColor:(UIColor *)endColor
{
    //    CAGradientLayer类对其绘制渐变背景颜色、填充层的形状(包括圆角)
    CAGradientLayer *gradientLayer = [CAGradientLayer layer];
    gradientLayer.frame = self.bounds;
    
    //  创建渐变色数组，需要转换为CGColor颜色
    gradientLayer.colors = @[(__bridge id)startColor.CGColor,(__bridge id)endColor.CGColor];
    gradientLayer.startPoint = CGPointMake(0, 0);
    
    gradientLayer.endPoint = CGPointMake(1, 1);
    //  设置颜色变化点，取值范围 0.0~1.0
    gradientLayer.locations = @[@0,@1];
    
    return gradientLayer;
}
@end
