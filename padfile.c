#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
union msgblock {
 uint8_t e[64];
 uint32_t t[16];
 uint64_t s[8];
};

enum status 
{
    READ,
    PAD0,
    PAD1,
    FINISH
};

int main(int argc, char *argv[]) {
     union msgblock M;
     uint64_t nobytes;
     uint64_t nobits = 0;
     FILE *f;
     int i =0;

     enum status s = READ;
    //this checks if more than 2 args are passed in the running of the programe 
    if(argc < 2){
        puts("No Input file"); 
        exit(1);
    }

    // this is for more then one file needs to be hashed 
    int x;
    for(x=1; x < argc; x++){
          //if it is then open the file
         f = fopen(argv[1], "r");
        //this check if the file exists 
        if(NULL != f){
             s = READ;
             while (s == READ) {
                nobytes = fread(M.e, 1, 64, f);
                printf("%llu\n", nobytes);
                nobits = nobits + (nobytes * 8);
    
                if(nobytes < 56){
                    printf("I've Found a block with less then 55 bytes\n");
                    M.e[nobytes] = 0x80;
                    
                    while(nobytes < 56){
                    
                       nobytes = nobytes + 1;
                       M.e[nobytes] = 0x00;
                    }
                    M.s[7] = nobits;
                    s = FINISH;
                }else if (nobytes < 64){
                    s = PAD0;
                    M.e[nobytes] = 0X80;
                    while( nobytes < 64){
                        nobytes = nobytes + 1;
                        M.e[nobytes] = 0x00;
                    }
                }else if(feof(f)){
                    s = PAD1;
                }
             
                     // printf("%llu\n", nobytes);
            } // end loop 
            if(s == PAD0 || s == PAD1){
                 for(i =0; i<56; i++){
                     M.e[i] = 0x00;
                 }
                 M.s[7] = nobits;
             }
             if(s == PAD1){
                 M.e[0] = 0x80;
             }
             fclose(f);
    
             for(int i= 0; i < 64; i++)
                 printf("%x ", M.e[i]);
    
             printf("\n");
        }else{
        //if the file doesnt exist then print this out 
             puts("File Doesnt open!!!");
        }
    }//for loop end open files 

    return 0;

} // end main
