//
//  GTAppDefines.h
//  GTToolBox
//
//  Created by WMYeah on 2017/11/13.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#ifndef GTAppDefines_h
#define GTAppDefines_h

/**
 获取 App显示名
 */
#define kGT_App_Name                [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleDisplayName"]

/**
 获取 App BundleID
 */
#define kGT_App_BundleID                [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleIdentifier"]
/**
 获取 App BundleName
 */
#define kGT_App_BundleName              [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleName"]
/**
 获取 App 当前版本号
 */
#define kGT_App_Current_Version          [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]

/**
 获取 App 当前LBUildVersion
 */
#define kGT_App_CurrentBuildVersion          [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"]


#ifdef DEBUG
#define kGT_Log(format, ...)            NSLog((@"\n\n  文件名  =  %s" "\n  函数名  =  %s" "\n  行号  =  %d\n  MSG  =  \n\n" format), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define kGT_Log(...)          NSLog(__VA_ARGS__)
#endif


/**
 通过RGB 获取 UIColor对象

 @param r r值
 @param g g值
 @param b b值
 @return    UIColor对象
 */
#define RGBCOLOR(r,g,b) [UIColor colorWithRed:(r)/255.0f green:(g)/255.0f blue:(b)/255.0f alpha:1]
/**
 通过RGB 获取 UIColor对象并设置aplpha值
 
 @param r r值
 @param g g值
 @param b b值
 @param a aplpha值
 @return    UIColor对象
 */
#define RGBAlphaCOLOR(r,g,b,a) [UIColor colorWithRed:(r)/255.0f green:(g)/255.0f blue:(b)/255.0f alpha:a]
/**
 通过RGB Hex值获取UIColor对象
 
 @param hexString hex值
 @return    UIColor对象
 */
#define RGBCOLOR_With_HexString(hexString) [UIColor GT_ColorWithHexString:hexString]


#endif /* GTAppDefines_h */
