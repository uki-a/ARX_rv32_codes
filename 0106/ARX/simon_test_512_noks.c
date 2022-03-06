#include <stdio.h>
#include <stdint.h>
#define ROTR32(x,b) (uint32_t)( ((x) << (32 - (b))) | ( (x) >> (b)) )
#define ROTL32(x,b) (uint32_t)( ((x) >> (32 - (b))) | ( (x) << (b)) )
#define f32(x) ((ROTL32(x,1) & ROTL32(x,8)) ^ ROTL32(x,2))
#define R32x2(x,y,k1,k2) (y^=f32(x), y^=k1, x^=f32(y), x^=k2)

#define length 16

#define read_csr(reg) ({unsigned long __tmp;\
asm volatile ("csrr %0, " #reg : "=r"(__tmp));\
__tmp;})

void main()
{
    long inst1, inst2;
    
	//uint32_t i,c=0xfffffffc;
	//uint64_t z=0xfc2ce51207a635dbLL;
	
	//uint32_t K[4]= {0x33221100,0x77665544,0xbbaa9988,0xffeeddcc};
	uint32_t rk[44]={
			0x33221100, 
			0x77665544, 
			0xbbaa9988, 
			0xffeeddcc, 
			0xd00ba77e, 
			0x59e7b16d, 
			0xbaee5865, 
			0x54ec787a, 
			0x353379d0, 
			0xc4746261, 
			0x1f4229b5, 
			0x76a52512, 
			0x853c238f, 
			0xa39ce6bb, 
			0x6300336f, 
			0xd4a8edfd, 
			0x6f4edaf4, 
			0x45fe056f, 
			0xbee3776b, 
			0xbf8cfc14, 
			0xabb97293, 
			0x945f8f37, 
			0x2a98039d, 
			0x49ec4878, 
			0x8795884b, 
			0x1cff9b14, 
			0x7a2d9af6, 
			0x5aab911a, 
			0x8415ea1a, 
			0x5cf8d086, 
			0x5c7cab84, 
			0xad032e39, 
			0xa61efa07, 
			0x5fe7e1dc, 
			0x96036f7b, 
			0xec4d0dd9, 
			0x8ab865af, 
			0xf4e64c08, 
			0xe245b6f3, 
			0x1e3a48ec, 
			0xb9f61dcd, 
			0x74df7c1b, 
			0xd54b3dd7, 
			0x0335705c

		};
	
	unsigned Pt[length] = {
	0x00000001,0x00000002,0x00000003,0x00000004,
	0x00000005,0x00000006,0x00000007,0x00000008,
	0x00000009,0x0000000a,0x0000000b,0x0000000c,
	0x0000000d,0x0000000e,0x0000000f,0x00000010};	

	uint32_t Ct[length];
	
	////enable for ks

	//rk[0]=K[0]; rk[1]=K[1]; rk[2]=K[2]; rk[3]=K[3];
	//for(i=4;i<44;i++){
	//	rk[i]=c^(z&1)^rk[i-4]^ROTR32(rk[i-1],3)^rk[i-3]^ROTR32(rk[i-1],4)^ROTR32(rk[i-3],1);
	//	z>>=1;
	//}
	
	//for (int i = 0; i < 44; i++) {
   	//	printf("0x%08x, ",rk[i]);
   	//	printf("\n");

	//}
    
    inst1 = read_csr(instret); // start
	
	for (int k=0; k<length; k+=2){ 

		Ct[k+1]=Pt[k+1]; Ct[k]=Pt[k];
		for(int i=0;i<44;){ 

			Ct[k]^=f32(Ct[k+1]);
			Ct[k]^=rk[i++];

			Ct[k+1]^=f32(Ct[k]); 
			Ct[k+1]^=rk[i++];


		}
	}
    
    inst2 = read_csr(instret); // end
      
    printf("instructions: %ld\n", inst2 - inst1);

	for (int i = 0; i < length; i++) {
   		printf("%08x ",Ct[i]);
   		printf("%d\n",i);
	}
	
}

