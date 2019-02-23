// Naqi Ahmad 2019 prject
// hash sha256 alogrithm 
// Input and Output operations performed
#include <stdio.h>
// provides a set of typedefs that specify exact-width integer types
#include <stdint.h>

void sha256();

int main(int argc, char *argv[]){
    
    return 0;
}

void sha256(){

    //message schedule
    uint32_t W[64]; 
    //working variables section 6.2
    uint32_t a, b, c, d, e, f, g, h;
     // two temp variables 
    uint32_t T1, T2; 
  
    // the hash value 
    uint32_t H[8] = {
         0x6a09e667,
         0xbb67ae85,
         0x3c6ef372,
         0xa54ff53a,
         0x510e527f,
         0x9b05688c,
         0x1f83d9ab,
         0x5be0cd19
    };
  
    // the current message block
    uint32_t M[16];

    // for loop
    for (i = 0,i < 16; ++i) {
        W[i] = M[i];
    }


}
