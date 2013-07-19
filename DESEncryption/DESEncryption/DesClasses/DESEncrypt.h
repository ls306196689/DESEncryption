//
//  DESEncrypt.h
//  testAnimation
//
//  Created by pengfei sun on 5/22/13.
//
//

#ifndef __testAnimation__DESEncrypt__
#define __testAnimation__DESEncrypt__

#include <iostream>
typedef bool BYTE;

class CCDESEncrypt {
  

public:
    
    
    //lengthdatain:带加密或者解密的数据长度; 返回值为 加密或者解密后存储数据的char 数组需要分配的长度
    static long getDESEncryptDataLength(long lengthdatain);
    
    
    //datain 为待加密或者待解密的数据指针； dataout 为加密或者解密后存储数据的指针；length 作为datain长度，加密或者解密之后作为dataout的数据长度
    static bool DESEncrypt(const char* datain, char* dataout, std::string key,long &length, bool isencrypt);
private:
    static void chars_2_byte(const char *cdata, BYTE *byte, int counterbits);
    static void byte_2_chars(const BYTE *byte, char *cdata, int counterbits);
    static void DES_encode_bit64(BYTE datain[64], BYTE dataout[64], bool isencrypt );
    static void DES_generate_K_16x48(const char* key);
    
    
    
};
#endif /* defined(__testAnimation__DESEncrypt__) */
