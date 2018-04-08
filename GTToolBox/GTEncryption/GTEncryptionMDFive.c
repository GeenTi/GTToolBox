//
//  GTEncryptionMDFive.c
//  GTToolBox
//
//  Created by WMYeah on 15/8/27.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;
/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;
/* UINT4 defines a four byte word */
typedef unsigned int UINT4;

#define PROTO_LIST(list) list

/* MD5 context.*/
typedef struct _MD5_CTX
{
    UINT4 state[4]; /* state (ABCD) */
    UINT4 count[2]; /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64]; /* input buffer */
} MD5_CTX;

/* Constants for MD5Transform routine.*/
#define RC_S11 7
#define RC_S12 12
#define RC_S13 17
#define RC_S14 22
#define RC_S21 5
#define RC_S22 9
#define RC_S23 14
#define RC_S24 20
#define RC_S31 4
#define RC_S32 11
#define RC_S33 16
#define RC_S34 23
#define RC_S41 6
#define RC_S42 10
#define RC_S43 15
#define RC_S44 21


/* F, G, H and I are basic MD5 functions.*/
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.Rotation is separate from addition to prevent recomputation.*/
#define FF(a, b, c, d, x, s, ac) {(a) += F ((b), (c), (d)) + (x) + (UINT4)(ac);(a) = ROTATE_LEFT ((a), (s));(a) += (b);}
#define GG(a, b, c, d, x, s, ac) {(a) += G ((b), (c), (d)) + (x) + (UINT4)(ac);(a) = ROTATE_LEFT ((a), (s));(a) += (b);}
#define HH(a, b, c, d, x, s, ac) {(a) += H ((b), (c), (d)) + (x) + (UINT4)(ac);(a) = ROTATE_LEFT ((a), (s));(a) += (b);}
#define II(a, b, c, d, x, s, ac) {(a) += I ((b), (c), (d)) + (x) + (UINT4)(ac);(a) = ROTATE_LEFT ((a), (s));(a) += (b);}

#define TEST_BLOCK_LEN 1000
#define TEST_BLOCK_COUNT 1000

static void ZX_MD5Transform PROTO_LIST ((UINT4 [4], unsigned char [64]));
static void ZX_Encode PROTO_LIST ((unsigned char *, UINT4 *, unsigned int));
static void ZX_Decode PROTO_LIST ((UINT4 *, unsigned char *, unsigned int));
static void ZX_MD5_memcpy PROTO_LIST ((POINTER, POINTER, unsigned int));
static void ZX_MD5_memset PROTO_LIST ((POINTER, int, unsigned int));
static void ZX_MD5Init PROTO_LIST ((MD5_CTX *));
static void ZX_MD5Update PROTO_LIST ((MD5_CTX *, unsigned char *, unsigned int));
static void ZX_MD5Final PROTO_LIST ((unsigned char [16], MD5_CTX *));
//static void ZX_MDTimeTrial PROTO_LIST ((void));
static void ZX_Encode PROTO_LIST ((unsigned char *, UINT4 *, unsigned int));
static void ZX_Decode PROTO_LIST ((UINT4 *, unsigned char *, unsigned int));

/* MD5 initialization. Begins an MD5 operation, writing a new context.*/
static void ZX_MD5Init(MD5_CTX *context)
{
    context->count[0] = context->count[1] = 0;
    /* Load magic initialization constants.*/
    context->state[0] = 0x67452301;
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;
}

/*MD5 block update operation. Continues an MD5 message-digest operation, processing another message block, and updating the context.*/
static void ZX_MD5Update(MD5_CTX *context,unsigned char *input,unsigned int inputLen)
{
    unsigned int i, index, partLen;
    
    /* Compute number of bytes mod 64 */
    index = (unsigned int)((context->count[0] >> 3) & 0x3F);
    
    /* Update number of bits */
    if ((context->count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
    {
        context->count[1]++;
    }
    context->count[1] += ((UINT4)inputLen >> 29);
    
    partLen = 64 - index;
    
    /* Transform as many times as possible.
     */
    if(inputLen >= partLen)
    {
        ZX_MD5_memcpy ((POINTER)&context->buffer[index], (POINTER)input, partLen);
        ZX_MD5Transform (context->state, context->buffer);
        
        for (i = partLen; i + 63 < inputLen; i += 64)
        {
            ZX_MD5Transform (context->state, &input[i]);
        }
        
        index = 0;
    }
    else
        i = 0;
    
    /* Buffer remaining input */
    ZX_MD5_memcpy((POINTER)&context->buffer[index], (POINTER)&input[i],inputLen-i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
 the message digest and zeroizing the context.
 */
static void ZX_MD5Final(unsigned char digest[16],MD5_CTX *context)
{
    unsigned char bits[8];
    unsigned int index, padLen;
    static unsigned char PADDING[64] = {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    
    /* Save number of bits */
    ZX_Encode (bits, context->count, 8);
    
    /* Pad out to 56 mod 64.*/
    index = (unsigned int)((context->count[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    ZX_MD5Update (context, PADDING, padLen);
    
    /* Append length (before padding) */
    ZX_MD5Update (context, bits, 8);
    
    /* Store state in digest */
    ZX_Encode (digest, context->state, 16);
    
    /* Zeroize sensitive information.*/
    ZX_MD5_memset ((POINTER)context, 0, sizeof (*context));
}

/* MD5 basic transformation. Transforms state based on block.*/
static void ZX_MD5Transform(UINT4 state[4],unsigned char block[64])
{
    UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
    
    ZX_Decode (x, block, 64);
    
    /* Round 1 */
    FF (a, b, c, d, x[ 0], RC_S11, 0xd76aa478); /* 1 */
    FF (d, a, b, c, x[ 1], RC_S12, 0xe8c7b756); /* 2 */
    FF (c, d, a, b, x[ 2], RC_S13, 0x242070db); /* 3 */
    FF (b, c, d, a, x[ 3], RC_S14, 0xc1bdceee); /* 4 */
    FF (a, b, c, d, x[ 4], RC_S11, 0xf57c0faf); /* 5 */
    FF (d, a, b, c, x[ 5], RC_S12, 0x4787c62a); /* 6 */
    FF (c, d, a, b, x[ 6], RC_S13, 0xa8304613); /* 7 */
    FF (b, c, d, a, x[ 7], RC_S14, 0xfd469501); /* 8 */
    FF (a, b, c, d, x[ 8], RC_S11, 0x698098d8); /* 9 */
    FF (d, a, b, c, x[ 9], RC_S12, 0x8b44f7af); /* 10 */
    FF (c, d, a, b, x[10], RC_S13, 0xffff5bb1); /* 11 */
    FF (b, c, d, a, x[11], RC_S14, 0x895cd7be); /* 12 */
    FF (a, b, c, d, x[12], RC_S11, 0x6b901122); /* 13 */
    FF (d, a, b, c, x[13], RC_S12, 0xfd987193); /* 14 */
    FF (c, d, a, b, x[14], RC_S13, 0xa679438e); /* 15 */
    FF (b, c, d, a, x[15], RC_S14, 0x49b40821); /* 16 */
    
    /* Round 2 */
    GG (a, b, c, d, x[ 1], RC_S21, 0xf61e2562); /* 17 */
    GG (d, a, b, c, x[ 6], RC_S22, 0xc040b340); /* 18 */
    GG (c, d, a, b, x[11], RC_S23, 0x265e5a51); /* 19 */
    GG (b, c, d, a, x[ 0], RC_S24, 0xe9b6c7aa); /* 20 */
    GG (a, b, c, d, x[ 5], RC_S21, 0xd62f105d); /* 21 */
    GG (d, a, b, c, x[10], RC_S22, 0x2441453); /* 22 */
    GG (c, d, a, b, x[15], RC_S23, 0xd8a1e681); /* 23 */
    GG (b, c, d, a, x[ 4], RC_S24, 0xe7d3fbc8); /* 24 */
    GG (a, b, c, d, x[ 9], RC_S21, 0x21e1cde6); /* 25 */
    GG (d, a, b, c, x[14], RC_S22, 0xc33707d6); /* 26 */
    GG (c, d, a, b, x[ 3], RC_S23, 0xf4d50d87); /* 27 */
    GG (b, c, d, a, x[ 8], RC_S24, 0x455a14ed); /* 28 */
    GG (a, b, c, d, x[13], RC_S21, 0xa9e3e905); /* 29 */
    GG (d, a, b, c, x[ 2], RC_S22, 0xfcefa3f8); /* 30 */
    GG (c, d, a, b, x[ 7], RC_S23, 0x676f02d9); /* 31 */
    GG (b, c, d, a, x[12], RC_S24, 0x8d2a4c8a); /* 32 */
    
    /* Round 3 */
    HH (a, b, c, d, x[ 5], RC_S31, 0xfffa3942); /* 33 */
    HH (d, a, b, c, x[ 8], RC_S32, 0x8771f681); /* 34 */
    HH (c, d, a, b, x[11], RC_S33, 0x6d9d6122); /* 35 */
    HH (b, c, d, a, x[14], RC_S34, 0xfde5380c); /* 36 */
    HH (a, b, c, d, x[ 1], RC_S31, 0xa4beea44); /* 37 */
    HH (d, a, b, c, x[ 4], RC_S32, 0x4bdecfa9); /* 38 */
    HH (c, d, a, b, x[ 7], RC_S33, 0xf6bb4b60); /* 39 */
    HH (b, c, d, a, x[10], RC_S34, 0xbebfbc70); /* 40 */
    HH (a, b, c, d, x[13], RC_S31, 0x289b7ec6); /* 41 */
    HH (d, a, b, c, x[ 0], RC_S32, 0xeaa127fa); /* 42 */
    HH (c, d, a, b, x[ 3], RC_S33, 0xd4ef3085); /* 43 */
    HH (b, c, d, a, x[ 6], RC_S34, 0x4881d05); /* 44 */
    HH (a, b, c, d, x[ 9], RC_S31, 0xd9d4d039); /* 45 */
    HH (d, a, b, c, x[12], RC_S32, 0xe6db99e5); /* 46 */
    HH (c, d, a, b, x[15], RC_S33, 0x1fa27cf8); /* 47 */
    HH (b, c, d, a, x[ 2], RC_S34, 0xc4ac5665); /* 48 */
    
    /* Round 4 */
    II (a, b, c, d, x[ 0], RC_S41, 0xf4292244); /* 49 */
    II (d, a, b, c, x[ 7], RC_S42, 0x432aff97); /* 50 */
    II (c, d, a, b, x[14], RC_S43, 0xab9423a7); /* 51 */
    II (b, c, d, a, x[ 5], RC_S44, 0xfc93a039); /* 52 */
    II (a, b, c, d, x[12], RC_S41, 0x655b59c3); /* 53 */
    II (d, a, b, c, x[ 3], RC_S42, 0x8f0ccc92); /* 54 */
    II (c, d, a, b, x[10], RC_S43, 0xffeff47d); /* 55 */
    II (b, c, d, a, x[ 1], RC_S44, 0x85845dd1); /* 56 */
    II (a, b, c, d, x[ 8], RC_S41, 0x6fa87e4f); /* 57 */
    II (d, a, b, c, x[15], RC_S42, 0xfe2ce6e0); /* 58 */
    II (c, d, a, b, x[ 6], RC_S43, 0xa3014314); /* 59 */
    II (b, c, d, a, x[13], RC_S44, 0x4e0811a1); /* 60 */
    II (a, b, c, d, x[ 4], RC_S41, 0xf7537e82); /* 61 */
    II (d, a, b, c, x[11], RC_S42, 0xbd3af235); /* 62 */
    II (c, d, a, b, x[ 2], RC_S43, 0x2ad7d2bb); /* 63 */
    II (b, c, d, a, x[ 9], RC_S44, 0xeb86d391); /* 64 */
    
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    
    /* Zeroize sensitive information.*/
    ZX_MD5_memset((POINTER)x, 0, sizeof (x));
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is a multiple of 4.*/
static void ZX_Encode(unsigned char *output,UINT4 *input,unsigned int len)
{
    unsigned int i, j;
    
    for (i = 0, j = 0; j < len; i++, j += 4)
    {
        output[j] = (unsigned char)(input[i] & 0xff);
        output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
}

/* Decodes input (unsigned char) into output (UINT4). Assumes len is a multiple of 4.*/
static void ZX_Decode(UINT4 *output,unsigned char *input,unsigned int len)
{
    unsigned int i, j;
    
    for (i = 0, j = 0; j < len; i++, j += 4)
        output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8) | (((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
}

/* Note: Replace "for loop" with standard memcpy if possible.*/
static void ZX_MD5_memcpy(POINTER output,POINTER input,unsigned int len)
{
    unsigned int i;
    
    for (i = 0; i < len; i++)
        output[i] = input[i];
}

/* Note: Replace "for loop" with standard memset if possible.*/
static void ZX_MD5_memset(POINTER output,int value,unsigned int len)
{
    unsigned int i;
    
    for (i = 0; i < len; i++)
        ((char *)output)[i] = (char)value;
}

/* Digests a string and prints the result.*/
void  ZX_MD5HexByte16(char *inString,char *md5HexByte16)
{
    MD5_CTX context;
    unsigned char digest[16+1];
    unsigned int inStringLen;
    
    inStringLen = (int)strlen (inString);
    
    ZX_MD5Init(&context);
    ZX_MD5Update(&context,(unsigned char*)inString, inStringLen);
    ZX_MD5Final(digest, &context);
    
    memcpy(md5HexByte16,digest,16);
}
void ZX_MD5HexString32(char *inString,char *md5String)
{
    unsigned char digest[16];
    char output[64]={""};
    int i;
    
    ZX_MD5HexByte16(inString,(char*)digest);
    
    for(i = 0; i < 16; i++)
    {
        sprintf(&(output[2*i]),"%02X",(unsigned char)digest[i]);
        sprintf(&(output[2*i+1]),"%02X",(unsigned char)(digest[i]<<4));
    }
    output[32]=0;
    strcpy(md5String,output);
}

void  ZX_MD5HexByte16FromBuffer(char *inBuffer,int inLen,char *md5HexByte16)
{
    MD5_CTX context;
    unsigned char digest[16+1];
    
    
    ZX_MD5Init(&context);
    ZX_MD5Update(&context,(unsigned char*)inBuffer, inLen);
    ZX_MD5Final(digest, &context);
    
    memcpy(md5HexByte16,digest,16);
}
void  ZX_MD5HexString32FromBuffer(char *inBuffer,int inLen,char *md5String)
{
    unsigned char digest[16];
    char output[64]={""};
    int i;
    
    ZX_MD5HexByte16FromBuffer(inBuffer,inLen,(char*)digest);
    
    for(i = 0; i < 16; i++)
    {
        sprintf(&(output[2*i]),"%02x",(unsigned char)digest[i]);
        sprintf(&(output[2*i+1]),"%02x",(unsigned char)(digest[i]<<4));
    }
    output[32]=0;
    strcpy(md5String,output);
}
