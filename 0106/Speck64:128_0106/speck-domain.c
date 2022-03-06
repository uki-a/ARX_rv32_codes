#include <stdio.h>

//#define DR32(x,y,k) (y^=x, y=ROTR32(y,3), x^=k, x-=y, x=ROTL32(x,8))

#define ER32(a, b, k)({\
asm volatile ("roli %[z], %[x], 24\n\t"\
                : [z] "=r" (a)\
                : [x] "r" (a));\
asm volatile ("add %[z], %[x], %[y]\n\t"\
                : [z] "=r" (a)\
                : [x] "r" (a), [y] "r" (b));\
asm volatile ( "xor %[z], %[x], %[y]\n\t"\
        		: [z] "=r" (a)\
        		: [x] "r" (a), [y] "r" (k));\
asm volatile ("rol3.xor %[z], %[x], %[y]\n\t"\
                : [z] "=r" (b)\
                : [x] "r" (b), [y] "r" (a));})

#define length 16

#define read_csr(reg) ({unsigned long __tmp;\
asm volatile ("csrr %0, " #reg : "=r"(__tmp));\
__tmp;})

void main()
{   long inst1, inst2;

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