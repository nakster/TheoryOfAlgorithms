# Theory of Algorithms 

This is a implementation of the SHA256 Hashing Algorithm in C.

## What is SHA256?

<p align="center"> 
<img src="https://www.digicert.com/images/sysicons/account-sha2-icon.png"/>
</p>

SHA-256 is a cryptographic hash function with digest length of 256 bits. It is a keyless hash function. A message is processed by blocks of 512 = 16 × 32 bits, each block requiring 64 rounds.

What is a hash function? A hash function is one that takes in a input, and outputs a value deterministic of the input value. For example if I input value abc, I will always get the same output for the value abc when the hash is run. So in a hash function every input has a detremined output.

A Good Hashing Algorithm Has The Following Properties
- The number is large enough that you will never find two messages with the same number 
- It is computationally unfeasible to extract message information from its hash
- A small (1 bit) change in the message will produce a huge change in the hash.

<p align="center"> 
<img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcT-SFgXIDffcVPHjFqBX53OorNfz44U28G1KaYOHorC_0tqk8UjHg"/>
</p>

I am using C programming language. One of the things that makes C such a versatile language is that the we can scale down a program to run with a very small amount of memory. C is the go-to language if we need a lot of control over memory usage. We can control everything even down to bytes and bits. This makes it a perfect language to code the hash Algorithm. 

Pointers
- Pointers in C language is a variable that stores/points the address of another variable
- The malloc() function reserves a block of memory of the specified number of bytes. 
- And, it returns a pointer of type void which can be casted into pointer of any form.

```C
uint64_t * sha256(FILE *file){

    uint64_t *Har = malloc(sizeof(uint64_t[8]));
    // Code

    return Har;
}

```
- I am using malloc() to allocate memory to store the hashed array 
- Then I return the pointer of that array 
- The array is then printed in the Main Method

```C
  //intialise a new uint64_t variable 
  uint64_t *h;
  
  // the h stores the pointer returned by the sha256
  h = sha256(file);
  
  // loop through the hash array and print it
  for(int i =0; i <8 ; i++){
    //print the hash
    printf("%08x ", *(h+i));
  }
  
```
## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

To run the SHA256 Hashing Algorithm Install the Following to your Machine</br>

```bash
For Windows Install MinGW From http://www.mingw.org/
```
```bash
For Linux Run 
sudo apt-get install build-essential
```


### Installing

#### Clone My Repo

Inside Your Bash/Terminal Copy And Paste This
```bash
Git clone https://github.com/nakster/TheoryOfAlgorithms.git

Change Into the Directory
cd "Location\TheoryOfAlgorithms"

Compile SHA256 
gcc -o sha256 sha256.c

```
#### Run SHA256
- You can Hash a File or A String
- To Hash A File Run This(You can Hash Multiple Files)

```bash
./sha256 <name of file>

Hash Multiple Files
./sha256 <name of file> <name of file> .... 

```
![](https://github.com/nakster/gif/blob/master/testfile.PNG)

- To Hash A String Run This
- The First Argument Must be S/s And Then The String You'd Like To Hash(You can Hash Multiple Strings)


```bash
./sha256 S abc

Hash Multiple Strings
./sha256 S "String .." "String .." ....
    
```

![](https://github.com/nakster/gif/blob/master/teststring.PNG)

## Implentation

### Basic operations

- Boolean operations AND, XOR and OR, denoted by ∧, ⊕ and ∨, respectively.
- ROTRIGHT(a, b) denotes the circular right shift of n bits of the binary word A.
- SHR n(x) The right shift operation, where x is a w-bit word and n is an integer with 0.

### Functions and constants

```C
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))
```
K = constant value to be used for the iteration t of the hash computation.
```C
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

```
### PREPROCESSING

Preprocessing consists of three steps:
- Padding the message, M 
- Parsing the message into message blocks
- Setting the initial hash value, H

#### Padding
To ensure that the Message Block has length multiple of 512 bits:
- First, a bit 1 is appended to the end of the message block,
- Next, k bits 0 are appended, with k being the smallest positive integer 
- such that l + 1 + k ≡ 448 mod 512, where l is the length in bits of the initial message,
- Finally, the length l < 2^64 of the initial message is represented with exactly 64 bits, and these bits
  are added at the end of the message.The message shall always be padded, even if the initial length is already a multiple of 512.
 - For example, the (8-bit ASCII) message “abc” has length 8x3 = 24, so the message is padded with a one bit
 - then 448 - (24 + 1) = 423 zero bits, and then the message length, to become the 512-bit padded message

### Block decomposition
For each block M ∈ {0, 1}^512, 64 words of 32 bits each are constructed as follows:
- The first 16 are obtained by splitting M in 32-bit blocks

```C
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
        
 ```
 
 - The remaining 48 are obtained with the formula:
```C
for (t=16 ; t < 64; ++t){
   W[t] = SIG1(W[t - 2]) + W[t - 7] + SIG0(W[t - 15]) + W[t - 16];
}
        
 ```
 
### Hash computation

-  SHA-256, eight variables are set to their initial values, in hex:

```C
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

// These words were obtained by taking the first thirty-two bits of the fractional parts of the square roots of the first eight prime 
// numbers
```

## Technologies Used

* Procedural Programming
* Google Cloud
* GitHub

## Authors

* **Naqi Ahmad**

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
