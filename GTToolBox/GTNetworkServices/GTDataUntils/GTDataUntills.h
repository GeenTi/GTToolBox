//
//  ZXDataUntills.h
//  GTToolBox
//
//  Created by WMYeah on 15/8/25.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GTDataUntills : NSObject
/*!
    支持 字典、数组  自定义数据类型  objectClass 必须是  自定义类 Class
    例如 ZXCustomString : NSString   ZXCustomString *testString = [[ZXCustomString alloc] init] 应该传入  [ZXCustomString:NSString Class]; 而不是[testString Class]、[NSString Class]
 */
+ (nullable NSString *)handleObjectTOJsonstringWithObject:(_Nonnull id)object objectClass:(_Nonnull Class)objectClass;
/*!
 *  JSONDic to Model
 *
 *  @param jsonDic     json字典
 *  @param objectClass 转成类型Class
 *
 *  @return 返回数据模型
 */
+ (nullable id)handleJsonsDicToObjectWithJsonDic:(nonnull NSDictionary*)jsonDic objectClass:(_Nonnull Class)objectClass;

/*!
 *  通过类名 获取对象 指定 属性 的value
 *
 *  @param object       对象 object
 *  @param objectClass  对象类名
 *  @param propertyName 属性名
 *
 *  @return 返回Value
 */
+ (nullable NSString *)getVlueWihtObject:(_Nonnull id)object objectClass:(_Nonnull Class)objectClass property:(nullable NSString *)propertyName;
/*!
 *  设置Model 默认值  值为 属性名  仅适用于 单一属性 对象拥有子对象不适用
 *
 *  @param object      Model object
 *  @param objectClass Model Class
 */
+ (void)getDefaultVlueFromPropertyNameWithObject:(_Nonnull id)object objcetClass:(_Nonnull Class)objectClass;


+ (nullable id)parserNormalDataWithJSONData:(nonnull NSData *)jsondata model:(_Nonnull Class)modelclass;

@end
