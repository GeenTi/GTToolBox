#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

static int udp_sendPoint    =   16000;
static int udp_recivePoint  =   16001;

static int sockfd=-1;
static struct sockaddr_in struAddr;
static struct sockaddr_in toAddr;


#pragma mark -- 添加于 WMYeah

long sendUDPToAddressAndPort(unsigned char *data, int len, const char *address, int sendPort)
{
    long slen;
    //   bzero ( &toAddr, sizeof(toAddr) );
    memset(&toAddr, 0, sizeof(toAddr));
    toAddr.sin_family = AF_INET;
    toAddr.sin_port = htons(sendPort);
    toAddr.sin_addr.s_addr = inet_addr(address);// 192.168.56.1
    //  bzero(&(toAddr.sin_zero),8);
    
    slen=sendto(sockfd,data,len,0,(const struct sockaddr *)&toAddr,sizeof(toAddr));
    if(slen<0)
        perror("socket send");
    return slen;
}


long sendUDPToAddress(unsigned char *data, int len, const char *address)
{
    long slen;
    
	   //   bzero ( &toAddr, sizeof(toAddr) );
    memset(&toAddr, 0, sizeof(toAddr));
    toAddr.sin_family = AF_INET;
    toAddr.sin_port = htons(udp_sendPoint);
    toAddr.sin_addr.s_addr = inet_addr(address);// 192.168.56.1
    //  bzero(&(toAddr.sin_zero),8);
    
    slen=sendto(sockfd,data,len,0,(const struct sockaddr *)&toAddr,sizeof(toAddr));
    if(slen<0)
        perror("socket send");
    return slen;
}



long sendUDP(unsigned char *data, int len)
{
    long slen;
	  
	   //   bzero ( &toAddr, sizeof(toAddr) ); 
    memset(&toAddr, 0, sizeof(toAddr));
    toAddr.sin_family = AF_INET;
	  toAddr.sin_port = htons(udp_sendPoint);
	  toAddr.sin_addr.s_addr = inet_addr("255.255.255.255");// 192.168.56.1 
	//  bzero(&(toAddr.sin_zero),8);
	
    slen=sendto(sockfd,data,len,0,(const struct sockaddr *)&toAddr,sizeof(toAddr));
    if(slen<0)
    	perror("socket send");
    return slen;
}

long recvUDP(unsigned char *data, int len)
{
    unsigned int nOn;
    long rlen;
    struct sockaddr_in fromAddr;
    
    nOn = sizeof(struct sockaddr);
    rlen = recvfrom(sockfd, data, len, 0, (struct sockaddr *)&fromAddr, &nOn);
    
    
    if(rlen<0)
        perror("socket recv");
    return rlen;
}

int initUDPWithPoints(int sendPoint,int recivePoint)
{
    //接收 外部传入的 UDP侦听端口 及 发送UDP数据端口
    udp_sendPoint = sendPoint;
    udp_recivePoint = recivePoint;
    
//    printf("\nUDPSendPort = %d\nUDPRecivePoint%d",udp_sendPoint,udp_recivePoint);

    int tmp;
    
    close(sockfd);
    usleep(100);
    
    /* ¥¥Ω® socket ”√”⁄UDPÕ®—∂ */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        printf("socket creating err in udptalk\n");
        return -1;
    }
    
    //   bzero ( &struAddr, sizeof(struAddr) );
    memset(&struAddr, 0, sizeof(struAddr));
    struAddr.sin_family = AF_INET;
    struAddr.sin_port = htons(recivePoint);
    struAddr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("192.168.33.36");
    //  bzero(&(struAddr.sin_zero),8);
    
    
    // ∞Û∂®º‡Ã˝∂Àø⁄
    if(bind(sockfd, (const struct sockaddr *)&struAddr, sizeof(struAddr)) < 0)
    {
        fprintf(stderr,"bind failed ! \n");
        return -1;
    }
    
    tmp = 0x100000;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &tmp, sizeof(tmp)) < 0)
    {
        fprintf(stderr,"setsockopt(SO_RECVBUF): %s\n", strerror(errno));
        return -1;
    }
    
    tmp=1;
    if(setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&tmp,sizeof(tmp))<0)
    {
        fprintf(stderr,"setsockopt(SO_BROADCAST): %s\n", strerror(errno));
        return -1;
    }
    
    return 0;
}

int initUDP(void)
{
    int tmp;
    
    /* ¥¥Ω® socket ”√”⁄UDPÕ®—∂ */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
    {
        printf("socket creating err in udptalk\n");
        return -1;
    }

 //   bzero ( &struAddr, sizeof(struAddr) ); 
     memset(&struAddr, 0, sizeof(struAddr));
    struAddr.sin_family = AF_INET;
	  struAddr.sin_port = htons(udp_recivePoint);
	  struAddr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("192.168.33.36");
	//  bzero(&(struAddr.sin_zero),8);


	  // ∞Û∂®º‡Ã˝∂Àø⁄
    if(bind(sockfd, (const struct sockaddr *)&struAddr, sizeof(struAddr)) < 0)
    {
        fprintf(stderr,"bind failed ! \n");
        return -1;
    }
    
    tmp = 0x100000;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &tmp, sizeof(tmp)) < 0) 
    {
        fprintf(stderr,"setsockopt(SO_RECVBUF): %s\n", strerror(errno));
        return -1;
    }
    
    tmp=1;
    if(setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&tmp,sizeof(tmp))<0)
    {
        fprintf(stderr,"setsockopt(SO_BROADCAST): %s\n", strerror(errno));
        return -1;
    }
    
    return 0;
}

void closeUDP(void)
{
	  if(sockfd>=0)
	  	  close(sockfd);
	  sockfd=-1;
}
