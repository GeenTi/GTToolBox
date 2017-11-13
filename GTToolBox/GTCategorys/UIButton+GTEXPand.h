//
//  UIButton+GTEXPand.h
//  GTToolBox
//
//  Created by WMYeah on 2017/9/21.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIButton (GTEXPand)


typedef enum : NSUInteger {
    // 图片在左，文字在右
    GTBtnImagePositionStyleDefault,
    // 图片在右，文字在左
    GTBtnImagePositionStyleRight,
    // 图片在上，文字在下
    GTBtnImagePositionStyleTop,
    // 图片在下，文字在上
    GTBtnImagePositionStyleBottom,
} GTBtnImagePositionStyle;

/**
 设置  文本 样式

 @param imagePositionStyle 图片位置样式
 @param spacing 图片与文字之间的间距
 */
- (void)GT_imagePositionStyle:(GTBtnImagePositionStyle)imagePositionStyle spacing:(CGFloat)spacing;


/**
 按钮点击时间间隔
 */
@property (nonatomic, assign) NSTimeInterval GT_timeInterval;


@end
