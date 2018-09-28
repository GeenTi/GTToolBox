//
//  GTHTTPService.mm
//  GTToolBox
//
//  Created by WMYeah on 15/8/25.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//


#import "GTHTTPService.h"
#import "GTEncryption.h"

#import "mongoose.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <ifaddrs.h>


@interface GTHTTPService ()

@property (readwrite)       struct mg_context *ctx;
@property (nonatomic,assign)  GT_Block_Complate_Result handleParmarBlock;
@end


@implementation GTHTTPService

// Return the localized IP address - From Erica Sadun's cookbook

- (NSString *) localIPAddress
{
    NSString *localIP = nil;
    struct ifaddrs *addrs;
    if (getifaddrs(&addrs)==0) {
        const struct ifaddrs *cursor = addrs;
        while (cursor != NULL) {
            if (cursor->ifa_addr->sa_family == AF_INET && (cursor->ifa_flags & IFF_LOOPBACK) == 0)
            {
                NSString *name = [NSString stringWithUTF8String:cursor->ifa_name];
                if ([name isEqualToString:@"en0"]) // Wi-Fi adapter
                {
                    localIP = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)cursor->ifa_addr)->sin_addr)];
                    break;
                }
            }
            cursor = cursor->ifa_next;
        }
        freeifaddrs(addrs);
    }
    return localIP;
}


+ (instancetype)sharedInstance
{
    static GTHTTPService *_instance = nil;
    static dispatch_once_t once_token;
    
    dispatch_once(&once_token, ^{
        if (_instance == nil) {
            _instance = [[GTHTTPService alloc] init];
        }
    });
    return _instance;
}

+ (void)startHTTPServiceWithWebRootDicPath:(NSString *)webRootDicPath port:(int)port reiveServiceParmarHandle:(GT_Block_Complate_Result)reciveServiceParmarBlock
{
    [GTHTTPService sharedInstance].handleParmarBlock = reciveServiceParmarBlock;
    BOOL isDir = NO;
    NSFileManager *fileManager = [NSFileManager defaultManager];
    BOOL existed = [fileManager fileExistsAtPath:webRootDicPath isDirectory:&isDir];
    if ( !(isDir == YES && existed == YES) )
    {
        [fileManager createDirectoryAtPath:webRootDicPath withIntermediateDirectories:YES attributes:nil error:nil];
    }
    
    [[GTHTTPService sharedInstance] setInitDatasWithWebRootDicPath:webRootDicPath port:port];
    
    [[GTHTTPService sharedInstance] startWebService];
}

- (void)setInitDatasWithWebRootDicPath:(NSString *)webRootDicPath port:(int)port
{
    _webServicePort = [NSString stringWithFormat:@"%d",port];
    _webRootDicPath = webRootDicPath;
}

- (void)startWebService
{
    self.ctx = mg_start();
    
    mg_set_option(self.ctx, "root", [_webRootDicPath UTF8String]);  // Set document root
    mg_set_option(self.ctx, "ports", [_webServicePort UTF8String]);    // Listen on port XXXX
    
    mg_set_handleRequest_callback(self.ctx, reciveHttpServiceUrlParmar,NULL);
    
    _locationIPAddress = [self localIPAddress];
    _webHost = [NSString stringWithFormat:@"http://%@:%@",_locationIPAddress,_webServicePort];
    
    NSLog(@"\nWEB服务已开启：%@\n",_webHost);
}

void reciveHttpServiceUrlParmar(struct mg_connection *connection, const struct mg_request_info *requestInfo, void *user_data)
{
    //将字符串整体作为分割条件 返回值为NSArray不可变数组
    char *query_string = requestInfo ->query_string;
    
    id data = nil;
    if (query_string && strcmp(query_string, "") != 0) {
        
        //获取IP地址
        NSString *ipAddress = [[GTHTTPService sharedInstance] convertNumberToIPAddressWithNumber:requestInfo->remote_ip];
        
//        ipAddress = @"192.168.168.232";
        
        NSString *sourceString = [NSString stringWithUTF8String:query_string];
        NSArray *getValue = [sourceString componentsSeparatedByString:@"="];
        
        if ([getValue[0] isEqualToString:@"p"]) {
            
            
            NSString *des_String = [GTEncryption GT_decryptionStrWithWaitingDecryptionString:getValue[1] keyString:[[GTHTTPService sharedInstance] getDesKeyWithIPAddress:ipAddress]];
            if (des_String && ![des_String isEqualToString:@""]) {
                data =[NSJSONSerialization JSONObjectWithData:[des_String dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
                
                if (!data) {
                    data =  [NSString stringWithFormat:@"\n错误  访问地址 %@ 源数据 %@",ipAddress,[NSString stringWithUTF8String:query_string]];
                }
            }else{
                data = @"解析错误";
            }
        }
    }
    
    [GTHTTPService sharedInstance].handleParmarBlock(data);
}

+ (void)stopHTTPService
{
    [[GTHTTPService sharedInstance] stopWebService];
}

- (void)stopWebService
{
    mg_stop(self.ctx);
    NSLog(@"\nWEB服务关闭\n");
}

- (NSString *)convertNumberToIPAddressWithNumber:(long)number
{
    in_addr inaddr;
    inaddr.s_addr = (unsigned int)number;
    NSString *ipaddr = [NSString stringWithUTF8String:inet_ntoa(inaddr)];
    NSArray *ipNumbers = [ipaddr componentsSeparatedByString:@"."];
    NSMutableString *ipAddress = [[NSMutableString alloc] init];
    for (NSUInteger i = ipNumbers.count - 1; i<ipNumbers.count; i --) {
        [ipAddress appendFormat:@"%@.",ipNumbers[i]];
    }
    return ipAddress;
}
- (NSString *)getDesKeyWithIPAddress:(NSString *)ipaddress
{
    NSMutableString *deskey = [[NSMutableString alloc] init];
    NSArray *strings = [ipaddress componentsSeparatedByString:@"."];
    for (int i = 0; i < 4; i++) {
        [deskey appendFormat:@"%ld",[strings[i] integerValue]];
    }
    
    return [deskey stringByReplacingOccurrencesOfString:deskey withString:[NSString stringWithFormat:@"%ld",[deskey integerValue] -1024]] ;
}

@end
