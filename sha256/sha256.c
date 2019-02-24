// Naqi Ahmad 2019 prject
// hash sha256 alogrithm 
// Input and Output operations performed
#include <stdio.h>
// provides a set of typedefs that specify exact-width integer types
#include <stdint.h>

//----------Macros-------------
//macros are used as these are one statement funcs 
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
    sha256();
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
    for (t = 0; t < 16; ++t) {
        W[t] = M[t];
    }

    for (t=16 ; t < 64; ++t){
        SIG1(W[t - 2]) + W[t - 7] + SIG0(W[t - 15]) + W[t - 16];
    }


    // intialise a,b,c,d,e,f,g and h as per step 2 page 22
    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];

    for (t = 0; t < 64; t++){
        T1 = h + EP1(e) + CH(e,f,g) + k[t] + W[t];
        T2 = EP0(a) + MAJ(a,b,c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    
    }
    //4. Compute the ith intermediate hash value H^(i)
    H[0] = a + H[0];
    H[1] = b + H[1]; 
    H[2] = c + H[2]; 
    H[3] = d + H[3]; 
    H[4] = e + H[4]; 
    H[5] = f + H[5]; 
    H[6] = g + H[6]; 
    H[7] = h + H[7];
 }
