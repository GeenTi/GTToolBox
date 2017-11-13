//
//  UIButton+GTEXPand.m
//  GTToolBox
//
//  Created by WMYeah on 2017/9/21.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#import "UIButton+GTEXPand.h"

#import <objc/runtime.h>

@interface UIButton ()
@property (nonatomic, assign) NSTimeInterval temp_timeInterval;
@end

@implementation UIButton (GTEXPand)


/**
 *  设置图片与文字样式
 *
 *  @param imagePositionStyle     图片的文字
 *  @param spacing           图片与文字之间的间距
 */
- (void)GT_imagePositionStyle:(GTBtnImagePositionStyle)imagePositionStyle spacing:(CGFloat)spacing {
    if (imagePositionStyle == GTBtnImagePositionStyleDefault) {
        self.imageEdgeInsets = UIEdgeInsetsMake(0, - 0.5 * spacing, 0, 0.5 * spacing);
        self.titleEdgeInsets = UIEdgeInsetsMake(0, 0.5 * spacing, 0, - 0.5 * spacing);
    } else if (imagePositionStyle == GTBtnImagePositionStyleRight) {
        CGFloat imageW = self.imageView.image.size.width;
        CGFloat titleW = self.titleLabel.frame.size.width;
        CGFloat imageOffset = titleW + 0.5 * spacing;
        CGFloat titleOffset = imageW + 0.5 * spacing;
        self.imageEdgeInsets = UIEdgeInsetsMake(0, imageOffset, 0, - imageOffset);
        self.titleEdgeInsets = UIEdgeInsetsMake(0, - titleOffset, 0, titleOffset);
    } else if (imagePositionStyle == GTBtnImagePositionStyleTop) {
        CGFloat imageW = self.imageView.frame.size.width;
        CGFloat imageH = self.imageView.frame.size.height;
        CGFloat titleIntrinsicContentSizeW = self.titleLabel.intrinsicContentSize.width;
        CGFloat titleIntrinsicContentSizeH = self.titleLabel.intrinsicContentSize.height;
        self.imageEdgeInsets = UIEdgeInsetsMake(- titleIntrinsicContentSizeH - spacing, 0, 0, - titleIntrinsicContentSizeW);
        self.titleEdgeInsets = UIEdgeInsetsMake(0, - imageW, - imageH - spacing, 0);
    } else if (imagePositionStyle == GTBtnImagePositionStyleBottom) {
        CGFloat imageW = self.imageView.frame.size.width;
        CGFloat imageH = self.imageView.frame.size.height;
        CGFloat titleIntrinsicContentSizeW = self.titleLabel.intrinsicContentSize.width;
        CGFloat titleIntrinsicContentSizeH = self.titleLabel.intrinsicContentSize.height;
        self.imageEdgeInsets = UIEdgeInsetsMake(titleIntrinsicContentSizeH + spacing, 0, 0, - titleIntrinsicContentSizeW);
        self.titleEdgeInsets = UIEdgeInsetsMake(0, - imageW, imageH + spacing, 0);
    }
}



+ (void)load {
    Method systemMethod = class_getInstanceMethod(self, @selector(sendAction:to:forEvent:));
    SEL sysSEL = @selector(sendAction:to:forEvent:);
    
    Method SGMethod = class_getInstanceMethod(self, @selector(GT_sendAction:to:forEvent:));
    SEL SGSEL = @selector(GT_sendAction:to:forEvent:);
    
    BOOL addMethod = class_addMethod(self, SGSEL, method_getImplementation(SGMethod), method_getTypeEncoding(SGMethod));
    if (addMethod) {
        class_replaceMethod(self, sysSEL, method_getImplementation(systemMethod), method_getTypeEncoding(systemMethod));
    } else {
        method_exchangeImplementations(systemMethod, SGMethod);
    }
}

- (void)GT_sendAction:(SEL)action to:(id)target forEvent:(UIEvent *)event {
    BOOL needSendAction = (NSDate.date.timeIntervalSince1970 - self.temp_timeInterval >= self.GT_timeInterval);
    
    if (self.GT_timeInterval > 0) {
        self.temp_timeInterval = NSDate.date.timeIntervalSince1970;
    }
    
    if (needSendAction) {
        [self GT_sendAction:action to:target forEvent:event];
    }
}

#pragma mark - - - set、get
- (void)setGT_timeInterval:(NSTimeInterval)GT_timeInterval {
    objc_setAssociatedObject(self, "UIButton_GT_timeInterval", @(GT_timeInterval), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}
- (NSTimeInterval)GT_timeInterval {
    return [objc_getAssociatedObject(self, "UIButton_GT_timeInterval") doubleValue];
}

- (void)setTemp_timeInterval:(NSTimeInterval)temp_timeInterval {
    objc_setAssociatedObject(self, "UIButton_temp_timeInterval", @(temp_timeInterval), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}
- (NSTimeInterval)temp_timeInterval {
    return [objc_getAssociatedObject(self, "UIButton_temp_timeInterval") doubleValue];
}

@end
