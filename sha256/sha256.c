// Naqi Ahmad 2019 project
// hash sha256 alogrithm 
// Input and Output operations performed
#include <stdio.h>
// provides a set of typedefs that specify exact-width integer types
#include <stdint.h>
#include <stdlib.h>

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
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))
#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)
#define SWAP_UINT64(val) \
( (((val) >> 56) & 0x00000000000000FF) | (((val) >> 40) & 0x000000000000FF00) | \
  (((val) >> 24) & 0x0000000000FF0000) | (((val) >>  8) & 0x00000000FF000000) | \
  (((val) <<  8) & 0x000000FF00000000) | (((val) << 24) & 0x0000FF0000000000) | \
  (((val) << 40) & 0x00FF000000000000) | (((val) << 56) & 0xFF00000000000000) )

//K = constant value to be used for the iteration t of the hash computation.
static const uint32_t  k[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

//union message block 
union msgblock {
 uint8_t e[64];
 uint32_t th[16];
 uint64_t s[8];
};
// enum for the position
enum status 
{
    READ,
    PAD0,
    PAD1,
    FINISH
};

//methods declared 
uint64_t * sha256(FILE *file);
int nextmsgblock(FILE *file, union msgblock *M, enum status *S, uint64_t *nobits); 

int main(int argc, char *argv[]){
	
	//open file as argv[1]
	FILE *file;
    uint64_t *h;
	
	//this checks if more than 2 args are passed in the running of the programe 
    if(argc < 2){
        puts("No Input file! Please Enter File"); 
        exit(1);
    }else{
		
		for(int j =1; j < argc; j++){
			file = fopen(argv[j], "r");
                        printf("The Hash of File %s\n", argv[j]);
			// run sha25
			// the sha256 returns a pointer to the hash values 
			h = sha256(file);
			// loop through the hash and print then=m
			for(int i =0; i <8 ; i++){
				printf("%08x ", *(h+i));
			}
			printf("\n\n");
			//	printf("\n%64x",*h);
			fclose(file);
		}
		
	}// end of else
    return 0;
}

uint64_t * sha256(FILE *file){
	//current message block
	union msgblock M;
	//number of bits read from file
	enum status S = READ;
	//status of mesblock i.e about padding
	uint64_t nobits = 0;

    //message schedule
    uint32_t W[64]; 
    //working variables section 6.2
    uint32_t a, b, c, d, e, f, g, h;
     // two temp variables 
    uint32_t T1, T2; 

    uint64_t *Har = malloc(sizeof(uint64_t[8]));
  
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
    // uint32_t M[16] = {0 , 0 , 0 ,0 ,0 ,0 , 0, 0};
    int i, t;

    //loop through message blocks
    while(nextmsgblock(file, &M, &S, &nobits)){
		// for loop
		// from page 22, w[t] = m[t] for 0 <= t 15
		
		// for (i = 0, j = 0; i < 16; ++i, j += 4)
		// m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
		for (t = 0; t < 16; ++t) {
			// W[t] = M.th[t];
			//check if its big endian 
			if(IS_BIG_ENDIAN){
				// dont need to convert to big endian if already big endian.
				W[t] = M.th[t];
			}else{
				//unless it is little endian then swap the data 
				W[t] = SWAP_UINT32(M.th[t]);
			}
		}
		//defines the secuirty of the algorithem 
		// trying to mix it up 
		// dificult to undo the operations
		for (t=16 ; t < 64; ++t){
		   W[t] = SIG1(W[t - 2]) + W[t - 7] + SIG0(W[t - 15]) + W[t - 16];
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

	// this here adds the H values to Har 
	for(i = 0; i < 8; i++){
		//add the 8 hashed values to the new mallocked array 
		Har[i] = H[i];      
	}
	//return the array which holds the values from the array
	return Har;

 }//end of sha256 method

 
int nextmsgblock(FILE *file, union msgblock *M, enum status *S, uint64_t *nobits) {

	//number of bytes from fread
	uint64_t nobytes;
	//for the loop
	int i =0;
	
	if(*S == FINISH)
		return 0;
	
	// checks if we need a another block full 
	// of padding
	if(*S == PAD0 || *S == PAD1){
		//if we do then set the 56 bytes to all sero bits
		for(i =0; i<56; i++){
			M->e[i] = 0x00;
		}
		//set the last 64 bits to the number of bits in the file 
		M->s[7] = *nobits;
		// then tell we are finished 
		*S = FINISH;
		
		// if it was pad1 then set the first bit of m to 1
		if(*S == PAD1){
			M->e[0] = 0x80;
		}
		// you still want the while loop to run another iteration
		// keep the loop in sha356 for one more iteration
		return 1;
	}
	
	// this is for if we havent actually came to the end of file 
	nobytes = fread(M->e, 1, 64, file);
	// printf("%llu\n", nobytes);
	//number of bytes read
	*nobits = *nobits + (nobytes * 8);
	// if we read less then 56 bytes
	// we can put all the padding in this message block
	if(nobytes < 56){
		//printf("I've Found a block with less then 55 bytes\n");
		//add the 1 bit as per standard 
		M->e[nobytes] = 0x80;
		// add zero its until the last 64bits 
		while(nobytes < 56){
			nobytes = nobytes + 1;
			M->e[nobytes] = 0x00;
		}
		//append the file size in bits as 
		// unsigned 64 bit int  
		//check if its big endian 
		if(IS_BIG_ENDIAN){
			// dont need to convert to big endian if already big endian.
			M -> s [7] = *nobits;
		}else{
			//else swap it to big endian
			M -> s [7] = SWAP_UINT64(*nobits);
		}
		//finished
		*S = FINISH;
	//check if we can put some padding into message block
	}else if (nobytes < 64){
		//tell S we need another mesblock 
		// with padding but no one bit
		*S = PAD0;
		// put the one bit into the current block
		M->e[nobytes] = 0X80;
		//pad the rest with zeros
		while( nobytes < 64){
			nobytes = nobytes + 1;
			M->e[nobytes] = 0x00;
		}
	// check if we are at the end of file 
	}else if(feof(file)){
		// tell s that we need a message block with all the padding 
		*S = PAD1;
	}

	// for(int i= 0; i < 64; i++)
		// printf("%x ", M->e[i]);
		// printf("\n");
		
	// return 1 so function is called again 

	return 1;
} // end main




