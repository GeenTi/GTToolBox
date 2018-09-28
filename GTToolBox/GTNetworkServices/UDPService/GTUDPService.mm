//
//  GTUDPService.mm
//  GTToolBox
//
//  Created by WMYeah on 15/8/25.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//


#import "GTUDPService.h"
#import "GTEncryption.h"

#import "GTDataUntills.h"

#include <stdio.h>
#include <string.h>

extern "C" {
    extern int initUDP();
    extern int initUDPWithPoints(int sendPoint,int recivePoint);
    extern long sendUDP(unsigned char *data, int len);
    extern long sendUDPToAddress(unsigned char *data, int len, const char *address);
    extern long sendUDPToAddressAndPort(unsigned char *data, int len, const char *address, int sendPort);
    extern long recvUDP(unsigned char *data, int len);
    extern void closeUDP();
};


@interface GTUDPService ()

@property (nonatomic,assign)dispatch_queue_t recvDisPathQueuel;

@end


@implementation GTUDPService

+ (instancetype)sharedInstance
{
    static GTUDPService *_instance = nil;
    static dispatch_once_t once_token;
    
    dispatch_once(&once_token, ^{
        if (_instance == nil) {
            _instance = [[GTUDPService alloc] init];
        }
    });
    return _instance;
}

- (void)startUDP
{
    [self stopUDP];
    
    int rect = initUDPWithPoints(_udpSendPort, _udpRecivePort);
    switch (rect) {
        case 0:
            NSLog(@"\n初始化UDP 成功");
            break;
        default:
            break;
    }
    
    if (!_recvDisPathQueuel) {
        _recvDisPathQueuel = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    }
    
    dispatch_async(_recvDisPathQueuel, ^{
        [self reciveUDPData];
    });
}
- (void)stopUDP
{
    closeUDP();
    if (_recvDisPathQueuel) {
        _recvDisPathQueuel = nil;
        NSLog(@"\nUDP 服务 stop");
    }
}

- (void)setInitDatasWithUDPThreadName:(NSString *)udpReciveThreadName sendDataPort:(int)sendDataPort reciveDataPort:(int)reciveDataPort
{
    _udpSendPort    = sendDataPort;
    _udpRecivePort  = reciveDataPort;
    _udpReciveThreadName = udpReciveThreadName;
}

+ (void)startUDPServiceWithUDPThreadName:(NSString *)udpReciveThreadName sendDataPort:(int)sendDataPort reciveDataPort:(int)reciveDataPort
{
    [[GTUDPService sharedInstance] setInitDatasWithUDPThreadName:udpReciveThreadName sendDataPort:sendDataPort reciveDataPort:reciveDataPort];
    [[GTUDPService sharedInstance] startUDP];
}

+ (void)stopUDPService
{
    [[GTUDPService sharedInstance] stopUDP];
}


+ (void)sendUDPDataWithUDPDataExchangeModel:(GTUDPDataExchangeModel *)UDPDataExchangeModel
{
    UDPDataExchangeModel.msg = [GTEncryption GT_encryptionStrWithWaitingEncryptionString:UDPDataExchangeModel.msg keyString:UDPDataExchangeModel.TKIP];
    
    NSString    *sendStr = [GTDataUntills handleObjectTOJsonstringWithObject:UDPDataExchangeModel objectClass:[GTUDPDataExchangeModel class]];
    NSData      *sendData = [sendStr dataUsingEncoding:NSUTF8StringEncoding];
    
    Byte *buffer = (Byte *)[sendData bytes];
    int len = (int)[sendData length];
    
    sendUDP(buffer, len);
}

+ (void)sendUDPDataWithUDPDataExchangeModel:(GTUDPDataExchangeModel *)UDPDataExchangeModel toAddress:(NSString *)address;
{
    UDPDataExchangeModel.msg = [GTEncryption GT_encryptionStrWithWaitingEncryptionString:UDPDataExchangeModel.msg keyString:UDPDataExchangeModel.TKIP];
    
    NSString    *sendStr = [GTDataUntills handleObjectTOJsonstringWithObject:UDPDataExchangeModel objectClass:[GTUDPDataExchangeModel class]];

    NSData      *sendData = [sendStr dataUsingEncoding:NSUTF8StringEncoding];
    
    Byte *buffer = (Byte *)[sendData bytes];
    
    int len = (int)[sendData length];
    
    sendUDPToAddress(buffer, len, [address cStringUsingEncoding:NSUTF8StringEncoding]);
}

+ (void)sendUDPDataWithUDPDataExchangeModel:(GTUDPDataExchangeModel *)UDPDataExchangeModel toAddress:(NSString *)address port:(NSUInteger)port
{
    UDPDataExchangeModel.msg = [GTEncryption GT_encryptionStrWithWaitingEncryptionString:UDPDataExchangeModel.msg keyString:UDPDataExchangeModel.TKIP];
    
    NSString    *sendStr = [GTDataUntills handleObjectTOJsonstringWithObject:UDPDataExchangeModel objectClass:[GTUDPDataExchangeModel class]];
    
    NSData      *sendData = [sendStr dataUsingEncoding:NSUTF8StringEncoding];
    
    Byte *buffer = (Byte *)[sendData bytes];
    
    int len = (int)[sendData length];
    sendUDPToAddressAndPort(buffer, len, [address cStringUsingEncoding:NSUTF8StringEncoding], (int)port);
}

- (void)reciveUDPData
{
    NSLog(@"当前线程 %@",[NSThread currentThread].name);
    
    long rlen;
    unsigned char data[1024];
    NSData *msgData;
    NSString* str;
    while(TRUE){
        memset(data,0x00,1024);
        rlen=recvUDP(data,1024);
        if(rlen<=0){
            [NSThread sleepForTimeInterval:0.01];
//            [weakSelf stopUDP];
//            [weakSelf startUDP];
            
        }else {
            msgData = [NSData dataWithBytes:data length:rlen];
            str = [[NSString alloc] initWithData:msgData encoding:NSUTF8StringEncoding];	// 以后必须改成 UTF-8 的字符串！！！
            
            GTUDPDataExchangeModel *recUDPMod = [GTDataUntills parserNormalDataWithJSONData:msgData model:[GTUDPDataExchangeModel class]];
            recUDPMod.msg = [GTEncryption GT_decryptionStrWithWaitingDecryptionString:recUDPMod.msg keyString:recUDPMod.TKIP];

            [self handleReceiveUDPDataWithReceiveUDPData:recUDPMod];
        }
    }
}

- (void)handleReceiveUDPDataWithReceiveUDPData:(GTUDPDataExchangeModel *)receiveUDPData
{
    dispatch_async(dispatch_get_main_queue(), ^{
        if (self.delegate && [self.delegate respondsToSelector:@selector(reciveUDPDataWithUDPDataExchangeModel:)]) {
            [self.delegate reciveUDPDataWithUDPDataExchangeModel:receiveUDPData];
        }
    });
}

@end
