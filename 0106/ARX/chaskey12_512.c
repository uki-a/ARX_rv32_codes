#include <stdio.h>

#define ROTL32(x,b) (unsigned)( ((x) >> (32 - (b))) | ( (x) << (b)) )

#define ROUND \
  do { \
    v[0] += v[1]; v[1]=ROTL32(v[1], 5); v[1] ^= v[0]; v[0]=ROTL32(v[0],16); \
    v[2] += v[3]; v[3]=ROTL32(v[3], 8); v[3] ^= v[2]; \
    v[0] += v[3]; v[3]=ROTL32(v[3],13); v[3] ^= v[0]; \
    v[2] += v[1]; v[1]=ROTL32(v[1], 7); v[1] ^= v[2]; v[2]=ROTL32(v[2],16); \
  } while(0)
  
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

//const volatile unsigned C[2] = { 0x00, 0x87 };

//#define TIMESTWO(out,in) \
//  do { \
//    out[0] = (in[0] << 1) ^ C[in[3] >> 31]; \
//    out[1] = (in[1] << 1) | (in[0] >> 31); \
//    out[2] = (in[2] << 1) | (in[1] >> 31); \
//    out[3] = (in[3] << 1) | (in[2] >> 31); \
//  } while(0)
    
unsigned main() {
    
    long inst1, inst2;

	unsigned k[4] =  {0x33221100,0x77665544,0xbbaa9988,0xffeeddcc};



	unsigned k1[4] = {0x66442287,0xeeccaa88,0x77553310,0xffddbb99}; 


	  //unsigned k2[4]=  {0x33221102,
	  //                  0x77665546,
	  //                  0xbbaa9980,
	  //                  0xffeeddce };

	unsigned v[4];

	unsigned m[length] ={
		0x03020100,0x07060504,0x0b0a0908,0x0f0e0d0c,
		0x13121110,0x17161514,0x1b1a1918,0x1f1e1d1c,
		0x03020100,0x07060504,0x0b0a0908,0x0f0e0d0c,
		0x13121110,0x17161514,0x1b1a1918,0x1f1e1d1c

	};
 
  //TIMESTWO(k1,k);
  //TIMESTWO(k2,k1);
    
  inst1 = read_csr(instret); // start

  v[0] = k[0];
  v[1] = k[1];
  v[2] = k[2];
  v[3] = k[3];


for (int i = 0; i < length-4; i+=4){

   v[0] ^= m[i];
   v[1] ^= m[i+1];
   v[2] ^= m[i+2];
   v[3] ^= m[i+3];
   //PERMUTE;

   for (int j=0; j<12; j++) {

       v[0] += v[1]; 
       v[1]=ROTL32(v[1], 5); 
       v[1] ^= v[0]; 
       v[0]=ROTL32(v[0],16);       
       v[2] += v[3]; 
       v[3]=ROTL32(v[3], 8); 
       v[3] ^= v[2];
       v[0] += v[3]; 
       v[3]=ROTL32(v[3],13); 
       v[3] ^= v[0];
       v[2] += v[1]; 
       v[1]=ROTL32(v[1], 7); 
       v[1] ^= v[2]; 
       v[2]=ROTL32(v[2],16);
	}


}
/*
printf("PERMUTE1\n");
for (int i = 0; i < 4; i++) {

   printf("%08x ",v[i]);
   //printf("%08x ",k1[i]);
   printf("%d\n",i);

}
   printf("\n");
*/
//if(mlen & 0xF == 0){
//printf("use k1\n");
//}
//else{
//printf("use k2\n");
//}

  v[0] ^= m[length-4];
  v[1] ^= m[length-3];
  v[2] ^= m[length-2];
  v[3] ^= m[length-1];




  v[0] ^= k1[0];
  v[1] ^= k1[1];
  v[2] ^= k1[2];
  v[3] ^= k1[3];


/*
printf("before PERMUTE2\n");
for (int i = 0; i < 4; i++) {

   printf("%08x ",k1[i]);
   //printf("%08x ",k1[i]);
   printf("%d\n",i);

}
   printf("\n");
*/


//PERMUTE;



   for (int j=0; j<12; j++) {

       v[0] += v[1]; 
       v[1]=ROTL32(v[1], 5); 
       v[1] ^= v[0]; 
       v[0]=ROTL32(v[0],16);       
       v[2] += v[3]; 
       v[3]=ROTL32(v[3], 8); 
       v[3] ^= v[2];
       v[0] += v[3]; 
       v[3]=ROTL32(v[3],13); 
       v[3] ^= v[0];
       v[2] += v[1]; 
       v[1]=ROTL32(v[1], 7); 
       v[1] ^= v[2]; 
       v[2]=ROTL32(v[2],16);
}

/*
printf("PERMUTE2\n");
for (int i = 0; i < 4; i++) {

   printf("%08x ",v[i]);
   //printf("%08x ",k1[i]);
   printf("%d\n",i);

}
   printf("\n");
*/
  v[0] ^= k1[0];
  v[1] ^= k1[1];
  v[2] ^= k1[2];
  v[3] ^= k1[3];
    
  inst2 = read_csr(instret); // end
    
  printf("instructions: %ld\n", inst2 - inst1);

  for (int i = 0; i < 4; i++) {

     printf("%08x ",v[i]);
     //printf("%08x ",k1[i]);
     printf("%d\n",i);

  }

  return v[4];
}
