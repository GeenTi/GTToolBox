//
//  GTToolBox.m
//  GTToolBox
//
//  Created by WMYeah on 2017/11/13.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#import "GTToolBox.h"

#define kGT_GTToolBox_Version   @"1.0.4"


@implementation GTToolBox

+ (NSString *)GT_Get_GTToolsBox_Version
{
    return kGT_GTToolBox_Version;
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



@end
