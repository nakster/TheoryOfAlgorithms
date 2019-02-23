// Naqi Ahmad 2019 prject
// hash sha256 alogrithm 
// Input and Output operations performed
#include <stdio.h>
// provides a set of typedefs that specify exact-width integer types
#include <stdint.h>

//----------Macros-------------
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

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

    int t;
    // for loop
    // from page 22, w[t] = m[t] for 0 <= t 15
    for (t = 0,t < 16; ++t) {
        W[t] = M[t];
    }

    for (t=16 ; t < 64; ++t){
        SIG1(W[t - 2]) + W[t - 7] + SIG0(W[t - 15]) + W[t - 16];
    }

}
