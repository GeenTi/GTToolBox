//
//  GTUDPDataExchangeModel.h
//  GTToolBox
//
//  Created by WMYeah on 15/8/25.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GTUDPDataExchangeModel : NSObject
/*!
 @brief 服务响应时间
 */
@property (nonatomic,retain) NSString *time;
/*!
 @brief 接口类型 标识
 */
@property (nonatomic,retain) NSString *type;
/*!
 @brief 返回消息 返回数据消息体
 */
@property (nonatomic,retain) NSString *msg;
/*!
 @brief 密钥 这个自己生成6位数随机码，需要每次发送消息的时候传送出去
 */
@property (nonatomic,retain) NSString *TKIP;
/*!
 @brief 设备标识
 */
@property (nonatomic,retain) NSString *device;

@end
