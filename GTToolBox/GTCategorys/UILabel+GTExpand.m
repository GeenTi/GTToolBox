//
//  UILabel+GTExpand.m
//  PocketShop
//
//  Created by WMYeah on 13-10-17.
//  Copyright (c) 2013年 GeenTi. All rights reserved.
//

#import "UILabel+GTExpand.h"

@implementation UILabel (GTExpand)

- (UILabel *)initLabelWithFrame:(CGRect)frame backgroundColor:(UIColor *)backgroundColor text:(NSString *)text textColor:(UIColor *)textColor font:(UIFont *)font textAlignment:( NSTextAlignment)textAlignment adjustsFontSizeToFitWidth:(BOOL)isAdjusts
{
    self = [super init];
    if (self) {
        [self setFrame:frame];
        if (backgroundColor) {
            [self setBackgroundColor:backgroundColor];
        }
        
        if (text) {
            [self setText:text];
        }
        
        if (textColor) {
            [self setTextColor:textColor];
        }
        
        if (font) {
            [self setFont:font];
        }
        
        if (textAlignment) {
            [self setTextAlignment:textAlignment];
        }
        
        if (isAdjusts == YES) {
            [self setAdjustsFontSizeToFitWidth:isAdjusts];
        }
    }
    return self;
}


@end
