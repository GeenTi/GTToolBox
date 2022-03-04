//
//  NSString+GTEXPand.m
//  GTToolBox
//
//  Created by WMYeah on 2017/9/21.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#import "NSString+GTEXPand.h"


@implementation NSString (GTEXPand)


- (UIImage *)GT_Convert_To_Image_WithFrame:(CGSize)size BackGroupColor:(UIColor *)backgroupColor StringColor:(UIColor *)stringColor
{
    if (!self) {
        return nil;
    }
    
    if (!backgroupColor) {
        backgroupColor = [UIColor whiteColor];
    }
    CGRect rect = CGRectMake(0.0f, 0.0f, size.width, size.height);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [backgroupColor CGColor]);
    CGContextFillRect(context, rect);
    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    
    UIImage *headerimg = [self GT_imageToAddText:img withText:self textColor:stringColor];
    return headerimg;
}

//把文字绘制到图片上
- (UIImage *)GT_imageToAddText:(UIImage *)img withText:(NSString *)text textColor:(UIColor *)textColor
{
    //1.获取上下文
    UIGraphicsBeginImageContext(img.size);
    //2.绘制图片
    [img drawInRect:CGRectMake(0, 0, img.size.width, img.size.height)];
    //3.绘制文字
    CGRect rect = CGRectMake(0,img.size.height/3, img.size.width, img.size.height/3 * 2);
    NSMutableParagraphStyle *style = [[NSMutableParagraphStyle defaultParagraphStyle] mutableCopy];
    style.alignment = NSTextAlignmentCenter;
    //文字的属性
    NSDictionary *dic = @{NSFontAttributeName:[UIFont systemFontOfSize:20],NSParagraphStyleAttributeName:style,NSForegroundColorAttributeName:textColor};
    //将文字绘制上去
    [text drawInRect:rect withAttributes:dic];
    //4.获取绘制到得图片
    UIImage *watermarkImg = UIGraphicsGetImageFromCurrentImageContext();
    //5.结束图片的绘制
    UIGraphicsEndImageContext();
    
    return watermarkImg;
}


@end
