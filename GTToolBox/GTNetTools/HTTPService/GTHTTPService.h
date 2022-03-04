//
//  GTHTTPService.h
//  GTToolBox
//
//  Created by WMYeah on 15/8/25.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "GTFuncExtension.h"


@interface GTHTTPService : NSObject

/*!
 *  WebService 服务端口
 */
@property (nonatomic,assign,readonly) NSString      *webServicePort;
/*!
 *  Web域名 例 http://ip:port
 */
@property (nonatomic,retain,readonly) NSString      *webHost;
/*!
 *  webRootDicPath      服务根目录
 */
@property (nonatomic,retain,readonly) NSString      *webRootDicPath;
/*!
 *  本机  IP
 */
@property (nonatomic,retain,readonly) NSString      *locationIPAddress;

/*!
 *  HTTP服务单例
 */
+ (instancetype)sharedInstance;
/*!
 *  启动HTTP服务
 *  port                服务端口
 *  webRootDicPath      服务根目录
 *  webRootDicPath样例[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]
 */
+ (void)startHTTPServiceWithWebRootDicPath:(NSString *)webRootDicPath port:(int)port reiveServiceParmarHandle:(GT_Block_Complate_Result)reciveServiceParmarBlock;
/*!
 *  停止  HTTP服务
 */
+ (void)stopHTTPService;

@end
