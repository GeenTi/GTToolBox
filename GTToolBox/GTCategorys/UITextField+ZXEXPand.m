//
//  UITextField+ZXEXPand.m
//  TangKuOne
//
//  Created by WMYeah on 2017/9/29.
//  Copyright © 2017年 XingData. All rights reserved.
//

#import "UITextField+ZXEXPand.h"

@implementation UITextField (ZXEXPand)

- (void)GT_Add_ToolBar_Done
{
    UIView  *toolbarVIew = [[UIView alloc] initWithFrame:CGRectMake(0, 0, [[UIScreen mainScreen] bounds].size.width, 50)];
    toolbarVIew.backgroundColor = [UIColor whiteColor];
    
    UIButton *losebtn = [UIButton buttonWithType:UIButtonTypeCustom];
    losebtn.frame = CGRectMake(toolbarVIew.frame.size.width - 70, 0, 50, 50);
    [losebtn addTarget:self action:@selector(btnClick) forControlEvents:UIControlEventTouchUpInside];
    [losebtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [losebtn setTitle:@"收起" forState:UIControlStateNormal];
    [toolbarVIew addSubview:losebtn];
    
    self.inputAccessoryView = toolbarVIew;
}

- (void)btnClick{
    
    [self resignFirstResponder];
}

@end
