//
//  GTAppDefines.h
//  GTToolBox
//
//  Created by WMYeah on 2017/11/13.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#ifndef GTAppDefines_h
#define GTAppDefines_h


#define kGT_App_Name                    NSLocalizedStringFromTable(@"CFBundleDisplayName", @"InfoPlist", nil)


#define kGT_App_BundleID                [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleIdentifier"]

#define kGT_App_BundleName              [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleName"]

#define kGT_App_Current_Version          [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]


#define kGT_App_CurrentBuildVersion          [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"]

#ifdef DEBUG
#define kGT_Log(format, ...)            NSLog((@"\n\n  文件名  =  %s" "\n  函数名  =  %s" "\n  行号  =  %d\n  MSG  =  \n\n" format), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define kGT_Log(...)          NSLog(__VA_ARGS__)
#endif


//  RGB 颜色
#define RGBCOLOR(r,g,b) [UIColor colorWithRed:(r)/255.0f green:(g)/255.0f blue:(b)/255.0f alpha:1]
#define RGBAlphaCOLOR(r,g,b,a) [UIColor colorWithRed:(r)/255.0f green:(g)/255.0f blue:(b)/255.0f alpha:a]




#endif /* GTAppDefines_h */
