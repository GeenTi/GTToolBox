//
//  UILabel+GTExpand.h
//  PocketShop
//
//  Created by WMYeah on 13-10-17.
//  Copyright (c) 2013年 GeenTi. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UILabel (GTExpand)


- (UILabel *)initLabelWithFrame:(CGRect)frame backgroundColor:(UIColor *)backgroundColor text:(NSString *)text textColor:(UIColor *)textColor font:(UIFont *)font textAlignment:(NSTextAlignment)textAlignment adjustsFontSizeToFitWidth:(BOOL)isAdjusts;


@end
