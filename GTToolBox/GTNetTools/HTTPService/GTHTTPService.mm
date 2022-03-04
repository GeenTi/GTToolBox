//
//  GTHTTPService.mm
//  GTToolBox
//
//  Created by WMYeah on 15/8/25.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//


#import "GTHTTPService.h"
#import "GTEncryption.h"


#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <ifaddrs.h>
#include "mongoose.h"
#include "mjson.h"

@interface GTHTTPService ()

@property (readwrite)       struct mg_connection *web_server_connection_http;
@property (readwrite)       struct mg_connection *web_server_connection_https;
@property (readwrite)       struct mg_mgr *web_server_mgr;
@property (readwrite)       struct mg_http_serve_opts web_server_http_opts;
@property (readwrite)       struct mg_tls_opts web_server_https_opts;

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

void gt_handler_recive_datas(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;

        if (mg_http_match_uri(hm, "/api/sum")) {
        // Attempt to fetch parameters from the body, hm->body
        double num1, num2;
        if (mjson_get_number(hm->body.ptr, hm->body.len, "$[0]", &num1) &&
            mjson_get_number(hm->body.ptr, hm->body.len, "$[1]", &num2)) {
          // Success! create a JSON response
          char resp[100];
          mjson_snprintf(resp, sizeof(resp), "{%Q:%g}", "result", num1 + num2);
          mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\n", resp);
        } else {
          mg_http_reply(c, 500, NULL, "%s", "Parameters missing");
        }
        } else {
        mg_http_reply(c, 500, NULL, "%s", "Invalid URI");
        }
        [GTHTTPService sharedInstance].handleParmarBlock([NSString stringWithCString:hm->query.ptr encoding:NSUTF8StringEncoding]);
    }

    (void) fn_data;
}
    
- (void)startWebService{
    _locationIPAddress = [self localIPAddress];

    mg_mgr_init(_web_server_mgr);                                   // Init manager
    _webHost = [NSString stringWithFormat:@"http://%@:%@",_locationIPAddress,_webServicePort];
    // Setup listener
    self.web_server_connection_http = mg_http_listen(_web_server_mgr, [_webHost UTF8String], gt_handler_recive_datas, _web_server_mgr);
    // Create HTTP listener
    _web_server_connection_http = mg_http_listen(_web_server_mgr, [_webHost UTF8String], gt_handler_recive_datas, NULL);
    // Create HTTPS listener
    _web_server_connection_https = mg_http_listen(_web_server_mgr, [_webHost UTF8String], gt_handler_recive_datas, (void *) 1);
    
    
    NSLog(@"\nWEB服务已开启：%@\n",_webHost);

    
    for (;;) mg_mgr_poll(_web_server_mgr, 1000);                        // Infinite event loop
    mg_mgr_free(self.web_server_mgr);
}

//void reciveHttpServiceUrlParmar(struct mg_connection *connection, const struct mg_request_info *requestInfo, void *user_data)
//{
//    //将字符串整体作为分割条件 返回值为NSArray不可变数组
//    char *query_string = requestInfo ->query_string;
//
//    id data = nil;
//    if (query_string && strcmp(query_string, "") != 0) {
//
//        //获取IP地址
//        NSString *ipAddress = [[GTHTTPService sharedInstance] convertNumberToIPAddressWithNumber:requestInfo->remote_ip];
//
////        ipAddress = @"192.168.168.232";
//
//        NSString *sourceString = [NSString stringWithUTF8String:query_string];
//        NSArray *getValue = [sourceString componentsSeparatedByString:@"="];
//
//        if ([getValue[0] isEqualToString:@"p"]) {
//
//
//            NSString *des_String = [GTEncryption GT_decryptionStrWithWaitingDecryptionString:getValue[1] keyString:[[GTHTTPService sharedInstance] getDesKeyWithIPAddress:ipAddress]];
//            if (des_String && ![des_String isEqualToString:@""]) {
//                data =[NSJSONSerialization JSONObjectWithData:[des_String dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
//
//                if (!data) {
//                    data =  [NSString stringWithFormat:@"\n错误  访问地址 %@ 源数据 %@",ipAddress,[NSString stringWithUTF8String:query_string]];
//                }
//            }else{
//                data = @"解析错误";
//            }
//        }
//    }
//
//    [GTHTTPService sharedInstance].handleParmarBlock(data);
//}

+ (void)stopHTTPService
{
    [[GTHTTPService sharedInstance] stopWebService];
}

- (void)stopWebService
{
    mg_mgr_free(self.web_server_mgr);
    
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
        [deskey appendFormat:@"%ld",(long)[strings[i] integerValue]];
    }
    
    return [deskey stringByReplacingOccurrencesOfString:deskey withString:[NSString stringWithFormat:@"%ld",(long)[deskey integerValue] -1024]] ;
}

@end
