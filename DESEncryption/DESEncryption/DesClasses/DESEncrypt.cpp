//
//  DESEncrypt.cpp
//  testAnimation
//
//  Created by pengfei sun on 5/22/13.
//
//
#include <fstream>
#include "DESEncrypt.h"
using namespace std;

template <class T>
void log_array(T array[], int counter)
{
    printf("\n--------------------\n");
    for (int i = 0; i < counter; i ++) {
        printf("%x ", array[i]);
        if ((i+1)%8 == 0) {
            printf("| ");
        }
    }
    printf("\n--------------------\n");
}
void log_bits_array(BYTE array[], int counter)
{
    printf("\n--------------------\n");
    for (int i = 0; i < counter; i ++) {
        printf("%d ", array[i]);
        if ((i+1)%8 == 0) {
            printf("| ");
        }
    }
    printf("\n--------------------\n");
}
//bool des_lock = false;



int des_a_i_p[56] = {
    57,49,41,33,25,17,9,1,
    58,50,42,34,26,18,10,2,
    59,51,43,35,27,19,11,3,
    60,52,44,36,63,55,47,39,
    31,23,15,7,62,54,46,38,
    30,22,14,6,61,53,45,37,
    29,21,13,5,28,20,12,4
};
int des_a_key_56_48[48] = {
    14,17,11,24, 1, 5, 3,28,
    15, 6,21,10,23,19,12, 4,
    26, 8,16, 7,27,20,13, 2,
    41,52,31,37,47,55,30,40,
    51,45,33,48,44,49,39,56,
    34,53,46,42,50,36,29,32
};
int des_a_data_64_64[64] = {
    58,50,42,34,26,18,10, 2,
    60,52,44,36,28,20,12, 4,
    62,54,46,38,30,22,14, 6,
    64,56,48,40,32,24,16, 8,
    57,49,41,33,25,17, 9, 1,
    59,51,43,35,27,19,11, 3,
    61,53,45,37,29,21,13, 5,
    63,55,47,39,31,23,15, 7
};
int des_a_data_32_48[48] = {
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
};
int des_a_sub_key_transform[17] = {0,1,  1,  2,  2,  2,  2,  2,  2,  1,   2,  2,   2,   2,   2,   2,  1};
int des_a_S_8[8][4][16] = {
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

const int des_a_L_R_TRAN[64] ={
    40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49, 17,57,25
};
int des_a_B_S_8_4[32] ={
    16,7,20,21,29,12,28,17,
    1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,
    19,13,30,6,22,11,4,25
};

BYTE des_a_K_16x48[16][48] = {0};


void CCDESEncrypt::DES_generate_K_16x48(const char* key)
{
    BYTE key_56[56] = {0};
    BYTE key_64[64] = {0};
    BYTE C[17][28] = {0};
    BYTE D[17][28] = {0};
    chars_2_byte(key, key_64, 64);
    for (int i = 0; i < 56; i ++) {
        key_56[i] = key_64[des_a_i_p[i]];
    }
    memcpy(C[0], key_56, sizeof(BYTE)*28);
    memcpy(D[0], key_56+28, sizeof(BYTE)*28);
    for (int i = 1; i < 17; i ++) {
        
        memcpy(C[i], C[i-1]+des_a_sub_key_transform[i], sizeof(BYTE)*(28 - des_a_sub_key_transform[i]));
        memcpy(C[i]+(28-des_a_sub_key_transform[i]), C[i-1], sizeof(BYTE)*(des_a_sub_key_transform[i]));
        memcpy(D[i], D[i-1]+des_a_sub_key_transform[i], sizeof(BYTE)*(28 - des_a_sub_key_transform[i]));
        memcpy(D[i]+(28-des_a_sub_key_transform[i]), D[i-1], sizeof(BYTE)*(des_a_sub_key_transform[i]));
    }
    int sub_key_16[16][56] = {0};
    for (int i = 0; i < 16; i ++) {
        memcpy(sub_key_16[i], C[i+1], 28*sizeof(BYTE));
        memcpy(sub_key_16[i]+28, D[i+1], 28*sizeof(BYTE));
    }
    for (int i = 0; i < 16; i ++) {
        for (int j = 0; j < 48; j ++) {
            des_a_K_16x48[i][j] = sub_key_16[i][des_a_key_56_48[j] - 1];
        }
    }
}
void CCDESEncrypt::DES_encode_bit64(BYTE datain[64], BYTE dataout[64], bool isencrypt )
{
//    if (des_lock) {
//        return;
//    }
//    des_lock = true;
    BYTE L[32] = {0};
    BYTE R[32] = {0};
    BYTE data_64_0[64] = {0};
 
    for (int i = 0; i < 64; i ++) {
        data_64_0[i] = datain[des_a_data_64_64[i] -1];
    }
    memcpy(L, data_64_0, sizeof(BYTE)*32);
    memcpy(R, data_64_0+32, sizeof(BYTE)*32);
    BYTE R48[48] = {0};
    for (int k = 0; k < 16; k ++) {
        for (int j = 0; j < 48; j ++) {
            R48[j] = R[des_a_data_32_48[j] - 1];
        }
        int k_index = isencrypt? k: (15- k);
        for (int j = 0; j < 48; j ++) {
            R48[j] ^= des_a_K_16x48[k_index][j];
        }
        BYTE B[8][6] = {0};
        for (int j = 0; j < 8; j ++) {
            memcpy(&(B[j][0]), R48+(j*6), sizeof(BYTE)*6);
        }
        BYTE dada_r[32]={0};
        for (int j = 0; j < 8; j ++) {
            int m = (B[j][0] <<1) + B[j][5];
            int n = (B[j][1] <<3) +(B[j][2] <<2 )+ (B[j][3] <<1) + B[j][4];
            BYTE bb_4[4] = {0};
            char c = des_a_S_8[j][m][n];
            chars_2_byte(&(c), bb_4, 4);
            memcpy(dada_r+ (j<<2), bb_4, sizeof(BYTE)*4);
        }
        
        BYTE data_r[32] = {0};
        for (int i = 0; i < 32; i ++) {
            data_r[i] = dada_r[des_a_B_S_8_4[i]-1];
        }
        BYTE rr[32] = {0};
        for (int j = 0; j < 32; j ++) {
            rr[j] = L[j] ^ data_r[j];
        }
        
        memcpy(L, R, sizeof(BYTE)*32);
        memcpy(R, rr, sizeof(BYTE)*32);
    }
    memcpy(data_64_0, R, sizeof(BYTE)*32);
    memcpy(data_64_0 + 32, L, sizeof(BYTE)*32);
    
    
    for (int j = 0; j < 64; j ++) {
        dataout[j] = data_64_0[des_a_L_R_TRAN[j]-1];
    }
//    des_lock = false;
}


void CCDESEncrypt::chars_2_byte(const char *cdata, BYTE *byte, int counterbits)
{
    int ccounters = counterbits/8+1;

    for (int i = 0; i < ccounters; i ++) {
        
        int bitcounter = (counterbits - (i << 3))-1;
        bitcounter = bitcounter < 7? bitcounter:7;
        for (int j = 0; j <=  bitcounter; j ++) {
            *(byte++) = ((*(cdata)>>( bitcounter - j))&0x01);
        }
        cdata++;
    }
}
void CCDESEncrypt::byte_2_chars(const BYTE *byte, char *cdata, int counterbits)
{
    
    int ccounters = counterbits/8 +1;
    for (int i = 0; i < ccounters; i ++) {
        *(cdata++) = 0;
    }
    cdata -= ccounters;
    for (int i = 0; i < ccounters; i ++) {
        int bitcounter = (counterbits - (i << 3))-1;
        bitcounter = bitcounter < 7? bitcounter:7;
        for (int j = 0; j <=  bitcounter; j ++) {
            *(cdata) |= (*(byte ++) <<(7-j ) );
        }
        cdata++;
    }
}


long CCDESEncrypt::getDESEncryptDataLength(long lengthdatain)
{
    return lengthdatain + 16;
}
bool CCDESEncrypt::DESEncrypt(const char* datain,char* dataout, std::string key,long &length, bool isencrypt){
    int length0 = 8 - length%8;
    int  counter = length/8+1;
    if (isencrypt ) {
        length += length0;
        if (length0 != 8) {
            counter ++;
            length += 8;
        }
    }
    else
    {
        if (length0 == 8) {
            counter --;
        }
        else
        {
            return false;
        }
    }

    DES_generate_K_16x48(key.c_str());
    char cdata[9] = {0};
    BYTE bitin[64] = {0};
    BYTE bitout[64] = {0};
    int i = 0;
    for (i  = 0; i < counter; i ++) {
        if (isencrypt && i == counter -1) {
            memcpy(cdata, datain + (i << 3), sizeof(char)*(8 - length0));
            for (int k = 0; k < length0 -1; k ++) {
                cdata[8 - length0 + k] = ' ';
            }
            cdata[7] = length0;
            if (length0 != 8) {
                cdata[7] += 8;
            }
        }
        else
        {
            memcpy(cdata, datain + (i << 3), sizeof(char)*8);
        }

        chars_2_byte(cdata, bitin, 64);
        DES_encode_bit64(bitin, bitout, isencrypt);
        byte_2_chars(bitout, cdata, 64);
        memcpy(dataout+(i << 3), cdata, sizeof(char)*8);
        
    }

    if (!isencrypt) {
        int data = dataout[length-1];
        length -= data;
        dataout[length] = 0;
    }
    return true;
}
