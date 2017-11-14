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
    NSBundle *bundle = [NSBundle bundleForClass:[GTToolBox class]];
    NSString *versionString = [[bundle infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    
    return versionString;
}


@end
