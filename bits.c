#include <stdio.h>
#include <stdint.h>

void binprint(uint32_t x){

	int i;
	uint32_t one = 1;

	for (i =0; i<32; i++){
		if((one <<(31 -i)) & x)
			printf("1");
		else
			printf("0");

	
	}
	
}
int main(int argc, char *argv[]){

    uint32_t a = 0x428a2f98;
    uint32_t b = 0x71374491;
    
    printf("   a: %0x\n", a); 
    printf("   b: %0x\n", b);
   
    printf("   a: "); binprint(a); printf("\n");

    //printf(" b: %x\n", b);
    printf("   b: "); binprint(b); printf("\n");
    //printf(" &: %08x\n", (a&b));
    printf(" a&b: "); binprint(a&b); printf("\n");
    //printf(" |: %08x\n", (a|b));  
    printf(" a|b: "); binprint(a|b); printf("\n");
    //printf(" ^: %08x\n", (a^b));
    printf(" a^b: "); binprint(a^b); printf("\n");
    //printf(" ~: %08x\n", (~a));
    printf("  ~a: "); binprint(~a); printf("\n");
    //printf("<<: %08x\n", (a<<1));
    printf("a<<1: "); binprint(a<<1); printf("\n");
    //printf(">>1: %08x\n", (a>>1));
    printf("a>>1: "); binprint(a>>1); printf("\n");



    return 0;
}
