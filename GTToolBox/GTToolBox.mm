//
//  GTToolBox.m
//  GTToolBox
//
//  Created by WMYeah on 2017/11/13.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#import "GTToolBox.h"

@implementation GTToolBox

+ (NSString *)GT_Get_GTToolsBox_Version
{
    NSString *app_Version = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];

    return app_Version;
}

+ (CGFloat)GT_GetWidthWithContent:(NSString *)content height:(CGFloat)height font:(CGFloat)font
{
    
    CGRect rect = [content boundingRectWithSize:CGSizeMake(999, height)
                                        options:NSStringDrawingUsesLineFragmentOrigin
                                     attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:font]}
                                        context:nil];
    return rect.size.width;
}

+ (BOOL)checkEmpty:(id)object {
    if ([object isKindOfClass:[NSArray class]]) {
        return object != nil && [object count] > 0;
    }
    if ([object isKindOfClass:[NSString class]]) {
        return object != nil && [object length] > 0;
    }
    
    if ([object isKindOfClass:[NSDictionary class]]) {
        return object != nil && [[object allKeys] count] > 0;
    }
    
    
    return false;
}

+ (BOOL)GT_CheckText:(UITextField *)text
{
    if (text == nil) {
        return YES;
    }
    if (text.text == nil || [text.text isEqualToString:@""]) {
        return YES;
    }
    return NO;
}

+ (BOOL)GT_CheckPhoneNumber:(NSString *)phoneNumber
{
    NSString *regex = @"^((13[0-9])|(147)|(15[^4,\\D])|(17[0-9])|(18[0-9]))\\d{8}$";
    
    NSPredicate *pred = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", regex];
    
    return [pred evaluateWithObject:phoneNumber];
}




@end
