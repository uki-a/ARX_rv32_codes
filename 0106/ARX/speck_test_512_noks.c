#include <stdio.h>
#include <stdint.h>
#define ROTR32(x,b) (uint32_t)( ((x) << (32 - (b))) | ( (x) >> (b)) )
#define ROTL32(x,b) (uint32_t)( ((x) >> (32 - (b))) | ( (x) << (b)) )
#define ER32(x,y,k) (x=ROTR32(x,8), x+=y, x^=k, y=ROTL32(y,3), y^=x)
#define DR32(x,y,k) (y^=x, y=ROTR32(y,3), x^=k, x-=y, x=ROTL32(x,8))

#define ER32(x,y,k)({ \
asm volatile ("ror8.add %[z], %[x], %[y]\n\t"\
	: [z] "=r" (v[0])\
                                                : [x] "r" (v[0]), [y] "r" (v[1]));\
        v[0] = v[0] ^ k;\
        asm volatile ("rol3.xor %[z], %[x], %[y]\n\t"\
                                                : [z] "=r" (v[1])\
                                                : [x] "r" (v[1]), [y] "r" (v[0]));}) \


#define length 16

#define read_csr(reg) ({unsigned long __tmp;\
asm volatile ("csrr %0, " #reg : "=r"(__tmp));\
__tmp;})

void main()
{   long inst1, inst2;
	//uint32_t K[4]= {0x33221100,0x77665544,0xbbaa9988,0xffeeddcc};
	uint32_t rk[27]= {
			0x33221100, 
			0xee89ff54, 
			0x030a534b, 
			0xc858d872, 
			0x5f16b27c, 
			0xb3386bc3, 
			0x47cb281d, 
			0x0fb1b862, 
			0x4d70854d, 
			0x25caa7a1, 
			0x83a9ad99, 
			0xfd97c619, 
			0x24582462, 
			0x97c703ef, 
			0xd39fc1e8, 
			0x1d96a8b4, 
			0xf0feeb7b, 
			0x029bc896, 
			0xe1c3759c, 
			0xb2c46dbf, 
			0x6a6ab7bc, 
			0xc40a691a, 
			0x3c940018, 
			0x9a304925, 
			0x4245e1c2, 
			0x024da700, 
			0xf4a10f50
		};
	
	unsigned Pt[length] = {
	0x00000001,0x00000002,0x00000003,0x00000004,
	0x00000005,0x00000006,0x00000007,0x00000008,
	0x00000009,0x0000000a,0x0000000b,0x0000000c,
	0x0000000d,0x0000000e,0x0000000f,0x00000010};	

	uint32_t Ct[length];
	

	////enable for ks
	//uint32_t D=K[3],C=K[2],B=K[1],A=K[0];
	//for(int i=0;i<27;){
	//	rk[i]=A; ER32(B,A,i++);
	//	rk[i]=A; ER32(C,A,i++);
	//	rk[i]=A; ER32(D,A,i++);
	//}
	
	//for (int i = 0; i < 27; i++) {
   	//	printf("0x%08x, ",rk[i]);
   	//	printf("\n");

	//}
	
    inst1 = read_csr(instret); // start
    
	for (int k=0; k<length; k+=2){ 

		Ct[k]=Pt[k]; 
		Ct[k+1]=Pt[k+1];
		for(int i=0;i<27;) {
			ER32(Ct[k+1],Ct[k],rk[i++]);
		}
	}
    
    inst2 = read_csr(instret); // end
    
    printf("instructions: %ld\n", inst2 - inst1);
	
	for (int i = 0; i < length; i++) {
   		printf("%08x ",Ct[i]);
   		printf("%d\n",i);
	}
    
}

