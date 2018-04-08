//
//  GTEncryptionDes.c
//  GTToolBox
//
//  Created by WMYeah on 15/8/27.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef byte
#define byte unsigned char
#endif



extern void ZX_ASCToBCD(byte *bcd_buf,byte *asc_buf,int asclen);
extern void ZX_BCDToASC(byte *asc_buf,byte *bcd_buf,int asclen);


void zx_des(unsigned char * inBuff, unsigned char * outBuff, unsigned char * keyBuff, unsigned char opFlag)
{
    unsigned short  flage2, temp1, temp2;
    short     flage1;
    short   i, j, k, flage3;
    
    const unsigned char des_table6[16] = {
        1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
    };
    
    const unsigned char des_table7[64] = {
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1,
        0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1,
        1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1,
        1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1                  };
    
    
    const unsigned char des_s1[4][16] = {
        14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
        0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
        4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13                    };
    
    const unsigned char des_s2[4][16] = {
        15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
        3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
        0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
        13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9                    };
    
    const unsigned char des_s3[4][16] = {
        10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
        13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
        13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
        1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12                    };
    
    const unsigned char des_s4[4][16] = {
        7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
        13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
        10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
        3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14                    };
    
    const unsigned char des_s5[4][16] = {
        2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
        14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
        4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
        11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3                    };
    
    const unsigned char des_s6[4][16] = {
        12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
        10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
        9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
        4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13                    };
    
    const unsigned char des_s7[4][16] = {
        4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
        13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
        1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
        6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12                    };
    
    const unsigned char des_s8[4][16] = {
        13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
        1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
        7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
        2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11                    };
    
    unsigned short des_table[64], des_table2[56], des_table1[48], des_table5[48], des_table3[64], des_table8[64];
    
    
    for (i = 0; i < 8; i++) {
        des_table8[8*i] = ((j = keyBuff[i]) / 128) % 2;
        des_table8[8*i+1] = (j / 64) % 2;
        des_table8[8*i+2] = (j / 32) % 2;
        des_table8[8*i+3] = (j / 16) % 2;
        des_table8[8*i+4] = (j / 8) % 2;
        des_table8[8*i+5] = (j / 4) % 2;
        des_table8[8*i+6] = (j / 2) % 2;
        des_table8[8*i+7] = j % 2;
        
    }
    
    for (i = 0; i < 8; i++) {
        des_table3[8*i] = ((j = *(inBuff + i)) / 128) % 2;
        des_table3[8*i+1] = (j / 64) % 2;
        des_table3[8*i+2] = (j / 32) % 2;
        des_table3[8*i+3] = (j / 16) % 2;
        des_table3[8*i+4] = (j / 8) % 2;
        des_table3[8*i+5] = (j / 4) % 2;
        des_table3[8*i+6] = (j / 2) % 2;
        des_table3[8*i+7] = j % 2;
        
    }
    
    des_table[ 0] = des_table3[57];
    des_table[ 1] = des_table3[49];
    des_table[ 2] = des_table3[41];
    des_table[ 3] = des_table3[33];
    des_table[ 4] = des_table3[25];
    des_table[ 5] = des_table3[17];
    des_table[ 6] = des_table3[ 9];
    des_table[ 7] = des_table3[ 1];
    des_table[ 8] = des_table3[59];
    des_table[ 9] = des_table3[51];
    des_table[10] = des_table3[43];
    des_table[11] = des_table3[35];
    des_table[12] = des_table3[27];
    des_table[13] = des_table3[19];
    des_table[14] = des_table3[11];
    des_table[15] = des_table3[ 3];
    des_table[16] = des_table3[61];
    des_table[17] = des_table3[53];
    des_table[18] = des_table3[45];
    des_table[19] = des_table3[37];
    des_table[20] = des_table3[29];
    des_table[21] = des_table3[21];
    des_table[22] = des_table3[13];
    des_table[23] = des_table3[ 5];
    des_table[24] = des_table3[63];
    des_table[25] = des_table3[55];
    des_table[26] = des_table3[47];
    des_table[27] = des_table3[39];
    des_table[28] = des_table3[31];
    des_table[29] = des_table3[23];
    des_table[30] = des_table3[15];
    des_table[31] = des_table3[ 7];
    des_table[32] = des_table3[56];
    des_table[33] = des_table3[48];
    des_table[34] = des_table3[40];
    des_table[35] = des_table3[32];
    des_table[36] = des_table3[24];
    des_table[37] = des_table3[16];
    des_table[38] = des_table3[ 8];
    des_table[39] = des_table3[ 0];
    des_table[40] = des_table3[58];
    des_table[41] = des_table3[50];
    des_table[42] = des_table3[42];
    des_table[43] = des_table3[34];
    des_table[44] = des_table3[26];
    des_table[45] = des_table3[18];
    des_table[46] = des_table3[10];
    des_table[47] = des_table3[ 2];
    des_table[48] = des_table3[60];
    des_table[49] = des_table3[52];
    des_table[50] = des_table3[44];
    des_table[51] = des_table3[36];
    des_table[52] = des_table3[28];
    des_table[53] = des_table3[20];
    des_table[54] = des_table3[12];
    des_table[55] = des_table3[ 4];
    des_table[56] = des_table3[62];
    des_table[57] = des_table3[54];
    des_table[58] = des_table3[46];
    des_table[59] = des_table3[38];
    des_table[60] = des_table3[30];
    des_table[61] = des_table3[22];
    des_table[62] = des_table3[14];
    des_table[63] = des_table3[ 6];
    
    des_table2[ 0] = des_table8[56];
    des_table2[ 1] = des_table8[48];
    des_table2[ 2] = des_table8[40];
    des_table2[ 3] = des_table8[32];
    des_table2[ 4] = des_table8[24];
    des_table2[ 5] = des_table8[16];
    des_table2[ 6] = des_table8[ 8];
    des_table2[ 7] = des_table8[ 0];
    des_table2[ 8] = des_table8[57];
    des_table2[ 9] = des_table8[49];
    des_table2[10] = des_table8[41];
    des_table2[11] = des_table8[33];
    des_table2[12] = des_table8[25];
    des_table2[13] = des_table8[17];
    des_table2[14] = des_table8[ 9];
    des_table2[15] = des_table8[ 1];
    des_table2[16] = des_table8[58];
    des_table2[17] = des_table8[50];
    des_table2[18] = des_table8[42];
    des_table2[19] = des_table8[34];
    des_table2[20] = des_table8[26];
    des_table2[21] = des_table8[18];
    des_table2[22] = des_table8[10];
    des_table2[23] = des_table8[ 2];
    des_table2[24] = des_table8[59];
    des_table2[25] = des_table8[51];
    des_table2[26] = des_table8[43];
    des_table2[27] = des_table8[35];
    des_table2[28] = des_table8[62];
    des_table2[29] = des_table8[54];
    des_table2[30] = des_table8[46];
    des_table2[31] = des_table8[38];
    des_table2[32] = des_table8[30];
    des_table2[33] = des_table8[22];
    des_table2[34] = des_table8[14];
    des_table2[35] = des_table8[ 6];
    des_table2[36] = des_table8[61];
    des_table2[37] = des_table8[53];
    des_table2[38] = des_table8[45];
    des_table2[39] = des_table8[37];
    des_table2[40] = des_table8[29];
    des_table2[41] = des_table8[21];
    des_table2[42] = des_table8[13];
    des_table2[43] = des_table8[ 5];
    des_table2[44] = des_table8[60];
    des_table2[45] = des_table8[52];
    des_table2[46] = des_table8[44];
    des_table2[47] = des_table8[36];
    des_table2[48] = des_table8[28];
    des_table2[49] = des_table8[20];
    des_table2[50] = des_table8[12];
    des_table2[51] = des_table8[ 4];
    des_table2[52] = des_table8[27];
    des_table2[53] = des_table8[19];
    des_table2[54] = des_table8[11];
    des_table2[55] = des_table8[ 3];
    
    for (flage3 = 1; flage3 < 17; flage3++) {
        for (i = 0; i < 32; i++)
            des_table3[i] = des_table[32+i];
        
        des_table1[ 0] = des_table3[31];
        des_table1[ 1] = des_table3[ 0];
        des_table1[ 2] = des_table3[ 1];
        des_table1[ 3] = des_table3[ 2];
        des_table1[ 4] = des_table3[ 3];
        des_table1[ 5] = des_table3[ 4];
        des_table1[ 6] = des_table3[ 3];
        des_table1[ 7] = des_table3[ 4];
        des_table1[ 8] = des_table3[ 5];
        des_table1[ 9] = des_table3[ 6];
        des_table1[10] = des_table3[ 7];
        des_table1[11] = des_table3[ 8];
        des_table1[12] = des_table3[ 7];
        des_table1[13] = des_table3[ 8];
        des_table1[14] = des_table3[ 9];
        des_table1[15] = des_table3[10];
        des_table1[16] = des_table3[11];
        des_table1[17] = des_table3[12];
        des_table1[18] = des_table3[11];
        des_table1[19] = des_table3[12];
        des_table1[20] = des_table3[13];
        des_table1[21] = des_table3[14];
        des_table1[22] = des_table3[15];
        des_table1[23] = des_table3[16];
        des_table1[24] = des_table3[15];
        des_table1[25] = des_table3[16];
        des_table1[26] = des_table3[17];
        des_table1[27] = des_table3[18];
        des_table1[28] = des_table3[19];
        des_table1[29] = des_table3[20];
        des_table1[30] = des_table3[19];
        des_table1[31] = des_table3[20];
        des_table1[32] = des_table3[21];
        des_table1[33] = des_table3[22];
        des_table1[34] = des_table3[23];
        des_table1[35] = des_table3[24];
        des_table1[36] = des_table3[23];
        des_table1[37] = des_table3[24];
        des_table1[38] = des_table3[25];
        des_table1[39] = des_table3[26];
        des_table1[40] = des_table3[27];
        des_table1[41] = des_table3[28];
        des_table1[42] = des_table3[27];
        des_table1[43] = des_table3[28];
        des_table1[44] = des_table3[29];
        des_table1[45] = des_table3[30];
        des_table1[46] = des_table3[31];
        des_table1[47] = des_table3[ 0];
        
        if (opFlag){
            flage2 = des_table6[flage3-1];
            for (i = 0; i < (int) flage2; i++) {
                temp1 = des_table2[0];
                temp2 = des_table2[28];
                for (j = 0; j < 27; j++) {
                    des_table2[j] = des_table2[j+1];
                    des_table2[j+28] = des_table2[j+29];
                }
                des_table2[27] = temp1;
                des_table2[55] = temp2;
            }
        } else if (flage3 > 1) {
            flage2 = des_table6[17-flage3];
            for (i = 0; i < (int) flage2; i++) {
                temp1 = des_table2[27];
                temp2 = des_table2[55];
                for (j = 27; j > 0; j--) {
                    des_table2[j] = des_table2[j-1];
                    des_table2[j+28] = des_table2[j+27];
                }
                des_table2[0] = temp1;
                des_table2[28] = temp2;
            }
        }
        
        des_table5[ 0] = des_table2[13];
        des_table5[ 1] = des_table2[16];
        des_table5[ 2] = des_table2[10];
        des_table5[ 3] = des_table2[23];
        des_table5[ 4] = des_table2[ 0];
        des_table5[ 5] = des_table2[ 4];
        des_table5[ 6] = des_table2[ 2];
        des_table5[ 7] = des_table2[27];
        des_table5[ 8] = des_table2[14];
        des_table5[ 9] = des_table2[ 5];
        des_table5[10] = des_table2[20];
        des_table5[11] = des_table2[ 9];
        des_table5[12] = des_table2[22];
        des_table5[13] = des_table2[18];
        des_table5[14] = des_table2[11];
        des_table5[15] = des_table2[ 3];
        des_table5[16] = des_table2[25];
        des_table5[17] = des_table2[ 7];
        des_table5[18] = des_table2[15];
        des_table5[19] = des_table2[ 6];
        des_table5[20] = des_table2[26];
        des_table5[21] = des_table2[19];
        des_table5[22] = des_table2[12];
        des_table5[23] = des_table2[ 1];
        des_table5[24] = des_table2[40];
        des_table5[25] = des_table2[51];
        des_table5[26] = des_table2[30];
        des_table5[27] = des_table2[36];
        des_table5[28] = des_table2[46];
        des_table5[29] = des_table2[54];
        des_table5[30] = des_table2[29];
        des_table5[31] = des_table2[39];
        des_table5[32] = des_table2[50];
        des_table5[33] = des_table2[44];
        des_table5[34] = des_table2[32];
        des_table5[35] = des_table2[47];
        des_table5[36] = des_table2[43];
        des_table5[37] = des_table2[48];
        des_table5[38] = des_table2[38];
        des_table5[39] = des_table2[55];
        des_table5[40] = des_table2[33];
        des_table5[41] = des_table2[52];
        des_table5[42] = des_table2[45];
        des_table5[43] = des_table2[41];
        des_table5[44] = des_table2[49];
        des_table5[45] = des_table2[35];
        des_table5[46] = des_table2[28];
        des_table5[47] = des_table2[31];
        
        for (i = 0; i < 48; i++)
            des_table1[i] = des_table1[i] ^ des_table5[i];
        
        flage1 = des_s1[2*des_table1[ 0]+des_table1[ 5]]
        [2*(2*(2*des_table1[ 1]+des_table1[ 2])+
            des_table1[ 3])+des_table1[ 4]];
        flage1 = flage1 * 4;
        des_table5[ 0] = des_table7[0+flage1];
        des_table5[ 1] = des_table7[1+flage1];
        des_table5[ 2] = des_table7[2+flage1];
        des_table5[ 3] = des_table7[3+flage1];
        flage1 = des_s2[2*des_table1[ 6]+des_table1[11]]
        [2*(2*(2*des_table1[ 7]+des_table1[ 8])+
            des_table1[ 9])+des_table1[10]];
        flage1 = flage1 * 4;
        des_table5[ 4] = des_table7[0+flage1];
        des_table5[ 5] = des_table7[1+flage1];
        des_table5[ 6] = des_table7[2+flage1];
        des_table5[ 7] = des_table7[3+flage1];
        flage1 = des_s3[2*des_table1[12]+des_table1[17]]
        [2*(2*(2*des_table1[13]+des_table1[14])+
            des_table1[15])+des_table1[16]];
        flage1 = flage1 * 4;
        des_table5[ 8] = des_table7[0+flage1];
        des_table5[ 9] = des_table7[1+flage1];
        des_table5[10] = des_table7[2+flage1];
        des_table5[11] = des_table7[3+flage1];
        flage1 = des_s4[2*des_table1[18]+des_table1[23]]
        [2*(2*(2*des_table1[19]+des_table1[20])+
            des_table1[21])+des_table1[22]];
        flage1 = flage1 * 4;
        des_table5[12] = des_table7[0+flage1];
        des_table5[13] = des_table7[1+flage1];
        des_table5[14] = des_table7[2+flage1];
        des_table5[15] = des_table7[3+flage1];
        flage1 = des_s5[2*des_table1[24]+des_table1[29]]
        [2*(2*(2*des_table1[25]+des_table1[26])+
            des_table1[27])+des_table1[28]];
        flage1 = flage1 * 4;
        des_table5[16] = des_table7[0+flage1];
        des_table5[17] = des_table7[1+flage1];
        des_table5[18] = des_table7[2+flage1];
        des_table5[19] = des_table7[3+flage1];
        flage1 = des_s6[2*des_table1[30]+des_table1[35]]
        [2*(2*(2*des_table1[31]+des_table1[32])+
            des_table1[33])+des_table1[34]];
        flage1 = flage1 * 4;
        des_table5[20] = des_table7[0+flage1];
        des_table5[21] = des_table7[1+flage1];
        des_table5[22] = des_table7[2+flage1];
        des_table5[23] = des_table7[3+flage1];
        flage1 = des_s7[2*des_table1[36]+des_table1[41]]
        [2*(2*(2*des_table1[37]+des_table1[38])+
            des_table1[39])+des_table1[40]];
        flage1 = flage1 * 4;
        des_table5[24] = des_table7[0+flage1];
        des_table5[25] = des_table7[1+flage1];
        des_table5[26] = des_table7[2+flage1];
        des_table5[27] = des_table7[3+flage1];
        flage1 = des_s8[2*des_table1[42]+des_table1[47]]
        [2*(2*(2*des_table1[43]+des_table1[44])+
            des_table1[45])+des_table1[46]];
        flage1 = flage1 * 4;
        des_table5[28] = des_table7[0+flage1];
        des_table5[29] = des_table7[1+flage1];
        des_table5[30] = des_table7[2+flage1];
        des_table5[31] = des_table7[3+flage1];
        
        des_table1[ 0] = des_table5[15];
        des_table1[ 1] = des_table5[ 6];
        des_table1[ 2] = des_table5[19];
        des_table1[ 3] = des_table5[20];
        des_table1[ 4] = des_table5[28];
        des_table1[ 5] = des_table5[11];
        des_table1[ 6] = des_table5[27];
        des_table1[ 7] = des_table5[16];
        des_table1[ 8] = des_table5[ 0];
        des_table1[ 9] = des_table5[14];
        des_table1[10] = des_table5[22];
        des_table1[11] = des_table5[25];
        des_table1[12] = des_table5[ 4];
        des_table1[13] = des_table5[17];
        des_table1[14] = des_table5[30];
        des_table1[15] = des_table5[ 9];
        des_table1[16] = des_table5[ 1];
        des_table1[17] = des_table5[ 7];
        des_table1[18] = des_table5[23];
        des_table1[19] = des_table5[13];
        des_table1[20] = des_table5[31];
        des_table1[21] = des_table5[26];
        des_table1[22] = des_table5[ 2];
        des_table1[23] = des_table5[ 8];
        des_table1[24] = des_table5[18];
        des_table1[25] = des_table5[12];
        des_table1[26] = des_table5[29];
        des_table1[27] = des_table5[ 5];
        des_table1[28] = des_table5[21];
        des_table1[29] = des_table5[10];
        des_table1[30] = des_table5[ 3];
        des_table1[31] = des_table5[24];
        
        for (i = 0; i < 32; i++) {
            des_table[i+32] = des_table[i] ^ des_table1[i];
            des_table[i] = des_table3[i];
        }
    }
    
    for (i = 0; i < 32; i++) {
        j = des_table[i];
        des_table[i] = des_table[32+i];
        des_table[32+i] = j;
    }
    
    des_table3[ 0] = des_table[39];
    des_table3[ 1] = des_table[ 7];
    des_table3[ 2] = des_table[47];
    des_table3[ 3] = des_table[15];
    des_table3[ 4] = des_table[55];
    des_table3[ 5] = des_table[23];
    des_table3[ 6] = des_table[63];
    des_table3[ 7] = des_table[31];
    des_table3[ 8] = des_table[38];
    des_table3[ 9] = des_table[ 6];
    des_table3[10] = des_table[46];
    des_table3[11] = des_table[14];
    des_table3[12] = des_table[54];
    des_table3[13] = des_table[22];
    des_table3[14] = des_table[62];
    des_table3[15] = des_table[30];
    des_table3[16] = des_table[37];
    des_table3[17] = des_table[ 5];
    des_table3[18] = des_table[45];
    des_table3[19] = des_table[13];
    des_table3[20] = des_table[53];
    des_table3[21] = des_table[21];
    des_table3[22] = des_table[61];
    des_table3[23] = des_table[29];
    des_table3[24] = des_table[36];
    des_table3[25] = des_table[ 4];
    des_table3[26] = des_table[44];
    des_table3[27] = des_table[12];
    des_table3[28] = des_table[52];
    des_table3[29] = des_table[20];
    des_table3[30] = des_table[60];
    des_table3[31] = des_table[28];
    des_table3[32] = des_table[35];
    des_table3[33] = des_table[ 3];
    des_table3[34] = des_table[43];
    des_table3[35] = des_table[11];
    des_table3[36] = des_table[51];
    des_table3[37] = des_table[19];
    des_table3[38] = des_table[59];
    des_table3[39] = des_table[27];
    des_table3[40] = des_table[34];
    des_table3[41] = des_table[ 2];
    des_table3[42] = des_table[42];
    des_table3[43] = des_table[10];
    des_table3[44] = des_table[50];
    des_table3[45] = des_table[18];
    des_table3[46] = des_table[58];
    des_table3[47] = des_table[26];
    des_table3[48] = des_table[33];
    des_table3[49] = des_table[ 1];
    des_table3[50] = des_table[41];
    des_table3[51] = des_table[ 9];
    des_table3[52] = des_table[49];
    des_table3[53] = des_table[17];
    des_table3[54] = des_table[57];
    des_table3[55] = des_table[25];
    des_table3[56] = des_table[32];
    des_table3[57] = des_table[ 0];
    des_table3[58] = des_table[40];
    des_table3[59] = des_table[ 8];
    des_table3[60] = des_table[48];
    des_table3[61] = des_table[16];
    des_table3[62] = des_table[56];
    des_table3[63] = des_table[24];
    
    j = 0;
    for (i = 0; i < 8; i++) {
        outBuff[i] = 0x00;
        for (k = 0; k < 7; k++)
            outBuff[i] = (unsigned char)(((unsigned short)outBuff[i] + des_table3[j+k]) * 2);
        outBuff[i] = (unsigned char)((unsigned short)outBuff[i] + des_table3[j+7]);
        j += 8;
    }
}

void ZX_3desEncryption(unsigned char *input, unsigned char *output, unsigned char *doubleKey)
{
    unsigned char buffer1[9],buffer2[9];
    zx_des(input,buffer1,doubleKey,1);
    zx_des(buffer1,buffer2,&doubleKey[8],0);
    zx_des(buffer2,output,doubleKey,1);
}
void ZX_3desEncryption2(unsigned char *input, unsigned char *output, unsigned char *doubleKeyStr)
{
    unsigned char doubleKey[33];
    ZX_ASCToBCD(doubleKey,doubleKeyStr,32);
    ZX_3desEncryption(input, output, doubleKey);
}
void ZX_3desEncryptionStr(unsigned char *inputStr, unsigned char *output, unsigned char *doubleKey)
{
    unsigned char input[33];
    int i;
    int len=(int)strlen((char *)inputStr);
    for(i=0;i<len/16;i++)
    {
        ZX_ASCToBCD(input,inputStr+i*16,16);
        ZX_3desEncryption(input, output+i*8, doubleKey);
    }
}

void ZX_3desDecryption(unsigned char *input, unsigned char *output, unsigned char *doubleKey)
{
    unsigned char buffer1[9],buffer2[9];
    zx_des(input,buffer1,doubleKey,0);
    zx_des(buffer1,buffer2,&doubleKey[8],1);
    zx_des(buffer2,output,doubleKey,0);
}
void ZX_3desDecryption2(unsigned char *input, unsigned char *output, unsigned char *doubleKeyStr)
{
    unsigned char doubleKey[33];
    ZX_ASCToBCD(doubleKey,doubleKeyStr,32);
    ZX_3desDecryption(input, output, doubleKey);
}
void ZX_3desDecryptionStr(unsigned char *inputStr, unsigned char *output, unsigned char *doubleKey)
{
    unsigned char input[33];
    int i;
    int len=(int)strlen((char *)inputStr);
    for(i=0;i<len/16;i++)
    {
        ZX_ASCToBCD(input,inputStr+i*16,16);
        ZX_3desDecryption(input, output+i*8, doubleKey);
    }
}

int ZX_3desEncryptionText(unsigned char *inputStr, unsigned char *output, unsigned char *doubleKey)
{
    unsigned char input[33];
    int i;
    int len=(int)strlen((char *)inputStr);
//    int len2;
    
    for(i=0;i<(len+7)/8;i++)
    {
        memcpy(input,inputStr+i*8,8);
        ZX_3desEncryption(input, output+i*8, doubleKey);
    }
    return 0;
}
int ZX_3desDecryptionText(unsigned char *inputBuff,int inputLen, unsigned char *output, unsigned char *doubleKey)
{
    unsigned char input[33];
    int i;
    int len=inputLen;
//    int len2;
    
    for(i=0;i<(len+7)/8;i++)
    {
        memcpy(input,inputBuff+i*8,8);
        ZX_3desDecryption(input, output+i*8, doubleKey);
    }
    return 0;
}



void zx_mac(char *inBuffer,int inLen,char *macBlock,char *mackey)
{
    int  len, i, j;
    byte keybuf[128], tmpbuf[128],tmpBlock[128];
    char strBuffer[128];
    
    memset(tmpBlock, '\0', 9);
    memset(&inBuffer[inLen], '\0', 8);
    len= (inLen % 8) ? (inLen / 8 + 1) :( inLen / 8 );
    for (i = 0; i< len; i++)
    {
        for (j = 0; j < 8; j++)
            tmpBlock[j] ^= inBuffer[i*8+j];
    }
    memcpy(tmpbuf, tmpBlock, 8);
    tmpbuf[8] = '\0';
    
    ZX_BCDToASC((unsigned char*)strBuffer,tmpbuf,16);
    
    memcpy(keybuf, mackey, 16);
    keybuf[16] = 0;
    
    zx_des((unsigned char*)strBuffer,(unsigned char*)tmpBlock,(unsigned char*)keybuf,1);
    ZX_BCDToASC(tmpbuf,tmpBlock,16);
    
    for (j = 0; j < 8; j++)
        tmpBlock[j] ^= strBuffer[8+j];
    ZX_BCDToASC(tmpbuf,tmpBlock,16);
    
    zx_des((unsigned char*)tmpBlock,(unsigned char*)tmpbuf,(unsigned char*)keybuf,1);
    ZX_BCDToASC((unsigned char*)strBuffer,tmpbuf,16);
    memcpy(macBlock, strBuffer, 8);
    macBlock[8] = 0;
}


int zx_unx98 (char *pin,unsigned char *pinBlock,char *cardNo,unsigned char *pinkey, int flag)
{
    int i, len;
    unsigned char tmp_buf[17], len_buf[3];
    unsigned char pan_block_bcd[9], pin_block_bcd[9];
    
    memset (tmp_buf, 0, sizeof(tmp_buf));
    memset (pan_block_bcd, 0, sizeof(pan_block_bcd));
    memset (pin_block_bcd, 0, sizeof(pin_block_bcd));
    
    if (flag == 0)
    {
        zx_des(pinBlock,pin_block_bcd,pinkey,0);
    }
    else
    {
        ZX_3desDecryption(pinBlock,pin_block_bcd,pinkey);
    }
    if(cardNo!=NULL && strlen(cardNo)>=12)
    {
        len=(int)strlen(cardNo);
        memset (tmp_buf, 0, sizeof(tmp_buf));
        memset (tmp_buf, '0', 16);
        memcpy (tmp_buf+4, cardNo + len - 12 -1, 12);
        ZX_BCDToASC((unsigned char*)pan_block_bcd, (unsigned char*)tmp_buf,16);
        
        for (i=0; i<8; i++)
            pin_block_bcd[i]^=pan_block_bcd[i];
    }
    ZX_BCDToASC((unsigned char*)tmp_buf, (unsigned char*)pin_block_bcd,16);
    
    memset (len_buf, 0, sizeof(len_buf));
    memcpy (len_buf, tmp_buf, 2);
    len = atoi((char *)len_buf);
    if (len > 12 || len < 0) return (-2);
    
    memcpy (pin, tmp_buf+2, len);
    pin[len]=0;
    
    return (0);
}

void zx_x98(char *cardNo,char *pin,char *pinBlock,char *pinkey,int flag)
{
    char card[32];
    char buff1[32];
    char buff2[32];
    char pinBuff[32];
    int i;
    
    memset(buff1,0,sizeof(buff1));
    sprintf(buff1,"%02d",(int)strlen(pin));
    strcat(buff1,pin);
    strcat(buff1,"FFFFFFFFFFFFFFFF");
    buff1[16]=0;
    ZX_ASCToBCD((unsigned char*)pinBuff, (unsigned char*)buff1,16);
    pinBuff[8] = 0;
    
    if(cardNo!=NULL && strlen(cardNo)>=12)
    {
        memset(card,'0',16);
        if(strlen(cardNo)>12)
        {
            memcpy(card+4,cardNo+strlen(cardNo)-13,12);
        }
        else
        {
            strcpy(card+16-strlen(cardNo),cardNo);
        }
        card[16]=0;
        ZX_ASCToBCD((unsigned char*)buff2, (unsigned char*)card,16);
        
        for (i = 0; i < 8; i++)
            pinBuff[i] = pinBuff[i] ^ buff2[i];
    }
    if(flag == 0)
        zx_des((unsigned char*)pinBuff,(unsigned char*)pinBlock,(unsigned char*)pinkey,1);
    else
        ZX_3desEncryption((unsigned char*)pinBuff,(unsigned char*)pinBlock,(unsigned char*)pinkey);
    
}
