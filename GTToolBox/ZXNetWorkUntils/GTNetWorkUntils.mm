//
//  GTNetWorkUntils.mm
//  GTToolBox
//
//  Created by WMYeah on 15/8/25.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//


#import "GTNetWorkUntils.h"
#import <SystemConfiguration/CaptiveNetwork.h>


@implementation GTNetWorkUntils

+ (NSString *)getWifiName
{
    NSString *wifiName = nil;
    CFArrayRef wifiInterfaces = CNCopySupportedInterfaces();
    if (!wifiInterfaces) {
        return nil;
    }
    NSArray *interfaces = (__bridge NSArray *)wifiInterfaces;
    for (NSString *interfaceName in interfaces) {
        CFDictionaryRef dictRef = CNCopyCurrentNetworkInfo((__bridge CFStringRef)(interfaceName));
        if (dictRef) {
            NSDictionary *networkInfo = (__bridge NSDictionary *)dictRef;
            wifiName = [networkInfo objectForKey:(__bridge NSString *)kCNNetworkInfoKeySSID];
            CFRelease(dictRef);
        }
    } 
    CFRelease(wifiInterfaces);
    return wifiName;
}

@end
