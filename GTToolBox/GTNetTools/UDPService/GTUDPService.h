//
//  GTUDPService.h
//  GTToolBox
//
//  Created by WMYeah on 15/8/25.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "GTUDPDataExchangeModel.h"



@protocol GTUDPServiceDelegate;


@interface GTUDPService : NSObject
/*!
 *  UDP服务相关代理
 */
@property (nonatomic,assign) id<GTUDPServiceDelegate> delegate;
/*!
 *  UDP监听线程名称
 */
@property (nonatomic,retain,readonly) NSString      *udpReciveThreadName;
/*!
 *  UDP 接收数据端口
 */
@property (nonatomic,assign,readonly) int    udpRecivePort;
/*!
 *  UDP 发送数据端口
 */
@property (nonatomic,assign,readonly) int    udpSendPort;
/*!
 *  UDP服务单例
 */
+ (instancetype)sharedInstance;
/*!
 *  启动  UDP服务
 *  udpReciveThreadName     UDP侦听线程名
 *  reciveDataPort          接收  UDP数据端口
 *  sendDataPort            发送  UDP数据端口
 */
+ (void)startUDPServiceWithUDPThreadName:(NSString *)udpReciveThreadName sendDataPort:(int)sendDataPort reciveDataPort:(int)reciveDataPort;
/*!
 *  停止  UDP服务
 */
+ (void)stopUDPService;
/*!
 *  发送UDP 数据
 *  UDPDataExchangeModel 封装好的 简单UDP 数据传输模型
 */
+ (void)sendUDPDataWithUDPDataExchangeModel:(GTUDPDataExchangeModel *)UDPDataExchangeModel;
/*!
 *  发送UDP 数据  到指定 IP
 *  UDPDataExchangeModel 封装好的 简单UDP 数据传输模型
 *  address    192.168.0.1  为指定发送    255.255.255.255 为广播域 局域网内
 */
+ (void)sendUDPDataWithUDPDataExchangeModel:(GTUDPDataExchangeModel *)UDPDataExchangeModel toAddress:(NSString *)address;


/*!
 *  发送UDP 数据  到指定 IP
 *
 *  @param UDPDataExchangeModel 封装好的 简单UDP 数据传输模型
 *  @param address              ip地址
 *  @param port                 端口
 */
+ (void)sendUDPDataWithUDPDataExchangeModel:(GTUDPDataExchangeModel *)UDPDataExchangeModel toAddress:(NSString *)address port:(NSUInteger)port;

@end

@protocol GTUDPServiceDelegate <NSObject>
/*!
 *  UDP 接受数据侦听代理 
 *  UDPDataExchangeModel 封装好的 简单UDP 数据传输模型
 *  推荐使用方法  dispatch_async(dispatch_get_main_queue(), ^{
                    //进行UI操作
                });
 */
-(void)reciveUDPDataWithUDPDataExchangeModel:(GTUDPDataExchangeModel *)UDPDataExchangeModel;

@end
