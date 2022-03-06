#include <stdio.h>

#define ROTL32(x,b) (unsigned)( ((x) >> (32 - (b))) | ( (x) << (b)) )

#define ROUND ({ uint32_t tmp;\
asm volatile ( "add %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[0])\
        : [x] "r" (v[0]), [y] "r" (v[1]));\
asm volatile ( "slli %[z], %[x], 5\n\t"\
        : [z] "=r" (tmp)\
        : [x] "r" (v[1]));\
asm volatile ( "srli %[z], %[x], 27\n\t"\
        : [z] "=r" (v[1])\
        : [x] "r" (v[1]));\
asm volatile ( "or %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[1])\
        : [x] "r" (v[1]), [y] "r" (tmp));\
asm volatile ( "xor %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[1])\
        : [x] "r" (v[1]), [y] "r" (v[0]));\
asm volatile ( "slli %[z], %[x], 16\n\t"\
        : [z] "=r" (tmp)\
        : [x] "r" (v[0]));\
asm volatile ( "srli %[z], %[x], 16\n\t"\
        : [z] "=r" (v[0])\
        : [x] "r" (v[0]));\
asm volatile ( "or %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[0])\
        : [x] "r" (v[0]), [y] "r" (tmp));\
\
asm volatile ( "add %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[2])\
        : [x] "r" (v[2]), [y] "r" (v[3]));\
asm volatile ( "slli %[z], %[x], 8\n\t"\
        : [z] "=r" (tmp)\
        : [x] "r" (v[3]));\
asm volatile ( "srli %[z], %[x], 24\n\t"\
        : [z] "=r" (v[3])\
        : [x] "r" (v[3]));\
asm volatile ( "or %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[3])\
        : [x] "r" (v[3]), [y] "r" (tmp));\
asm volatile ( "xor %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[3])\
        : [x] "r" (v[3]), [y] "r" (v[2]));\
\
asm volatile ( "add %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[0])\
        : [x] "r" (v[0]), [y] "r" (v[3]));\
asm volatile ( "slli %[z], %[x], 13\n\t"\
        : [z] "=r" (tmp)\
        : [x] "r" (v[3]));\
asm volatile ( "srli %[z], %[x], 19\n\t"\
        : [z] "=r" (v[3])\
        : [x] "r" (v[3]));\
asm volatile ( "or %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[3])\
        : [x] "r" (v[3]), [y] "r" (tmp));\
asm volatile ( "xor %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[3])\
        : [x] "r" (v[3]), [y] "r" (v[0]));\
\
asm volatile ( "add %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[2])\
        : [x] "r" (v[2]), [y] "r" (v[1]));\
asm volatile ( "slli %[z], %[x], 7\n\t"\
        : [z] "=r" (tmp)\
        : [x] "r" (v[1]));\
asm volatile ( "srli %[z], %[x], 25\n\t"\
        : [z] "=r" (v[1])\
        : [x] "r" (v[1]));\
asm volatile ( "or %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[1])\
        : [x] "r" (v[1]), [y] "r" (tmp));\
asm volatile ( "xor %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[1])\
        : [x] "r" (v[1]), [y] "r" (v[2]));\
asm volatile ( "slli %[z], %[x], 16\n\t"\
        : [z] "=r" (tmp)\
        : [x] "r" (v[2]));\
asm volatile ( "srli %[z], %[x], 16\n\t"\
        : [z] "=r" (v[2])\
        : [x] "r" (v[2]));\
asm volatile ( "or %[z], %[x], %[y]\n\t"\
        : [z] "=r" (v[2])\
        : [x] "r" (v[2]), [y] "r" (tmp));\
})

/*#define ROUND \
  do { \
    v[0] += v[1]; v[1]=ROTL32(v[1], 5); v[1] ^= v[0]; v[0]=ROTL32(v[0],16); \
    v[2] += v[3]; v[3]=ROTL32(v[3], 8); v[3] ^= v[2]; \
    v[0] += v[3]; v[3]=ROTL32(v[3],13); v[3] ^= v[0]; \
    v[2] += v[1]; v[1]=ROTL32(v[1], 7); v[1] ^= v[2]; v[2]=ROTL32(v[2],16); \
  } while(0)*/
  
#define PERMUTE \
  ROUND; \
  ROUND; \
  ROUND; \
  ROUND; \
  ROUND; \
  ROUND; \
  ROUND; \
  ROUND; \
  ROUND; \
  ROUND; \
  ROUND; \
  ROUND;

#define length 16

#define read_csr(reg) ({unsigned long __tmp;\
asm volatile ("csrr %0, " #reg : "=r"(__tmp));\
__tmp;})
    
unsigned main() {
    
    long inst1, inst2;

	unsigned k[4] =  {0x33221100,0x77665544,0xbbaa9988,0xffeeddcc};



	unsigned k1[4] = {0x66442287,0xeeccaa88,0x77553310,0xffddbb99}; 

	unsigned v[4];

	unsigned m[length] ={
		0x03020100,0x07060504,0x0b0a0908,0x0f0e0d0c,
		0x13121110,0x17161514,0x1b1a1918,0x1f1e1d1c,
		0x03020100,0x07060504,0x0b0a0908,0x0f0e0d0c,
		0x13121110,0x17161514,0x1b1a1918,0x1f1e1d1c

	};
 
  v[0] = k[0];
  v[1] = k[1];
  v[2] = k[2];
  v[3] = k[3];

inst1 = read_csr(instret); // start

for (int i = 0; i < length-4; i+=4){

   v[0] ^= m[i];
   v[1] ^= m[i+1];
   v[2] ^= m[i+2];
   v[3] ^= m[i+3];
   
   PERMUTE;

}
inst2 = read_csr(instret); // end

printf("instructions: %ld\n", inst2 - inst1);


  v[0] ^= m[length-4];
  v[1] ^= m[length-3];
  v[2] ^= m[length-2];
  v[3] ^= m[length-1];


  v[0] ^= k1[0];
  v[1] ^= k1[1];
  v[2] ^= k1[2];
  v[3] ^= k1[3];

PERMUTE;

  v[0] ^= k1[0];
  v[1] ^= k1[1];
  v[2] ^= k1[2];
  v[3] ^= k1[3];

  for (int i = 0; i < 4; i++) {

     printf("%08x ",v[i]);
     printf("%d\n",i);

  }

  return v[4];
}