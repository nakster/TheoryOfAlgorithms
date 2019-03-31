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

### C

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
- To Hash A File Run This
- You can Hash Multiple Files

```bash
./sha256 <name of file>

Hash Multiple Files
./sha256 <name of file> <name of file> .... 

```
![](https://github.com/nakster/gif/blob/master/testfile.PNG)

- To Hash A String Run This
- The First Argument Must be S/s And Then The String You'd Like To Hash
- You can Hash Multiple Strings


```bash
./sha256 S abc

Hash Multiple Strings
./sha256 S "String .." "String .." ....
    
```

![](https://github.com/nakster/gif/blob/master/teststring.PNG)







