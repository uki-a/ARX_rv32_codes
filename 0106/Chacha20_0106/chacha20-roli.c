#include <stdio.h>

#define QR(a, b, c, d) ({\
asm volatile ( "add %[z], %[x], %[y]\n\t"\
        : [z] "=r" (a)\
        : [x] "r" (a), [y] "r" (b));\
asm volatile ( "xor %[z], %[x], %[y]\n\t"\
        : [z] "=r" (d)\
        : [x] "r" (d), [y] "r" (a));\
asm volatile ("roli %[z], %[x], 16\n\t" \
		: [z] "=r" (d) \
		: [x] "r" (d));\
\
asm volatile ( "add %[z], %[x], %[y]\n\t"\
        : [z] "=r" (c)\
        : [x] "r" (c), [y] "r" (d));\
asm volatile ( "xor %[z], %[x], %[y]\n\t"\
        : [z] "=r" (b)\
        : [x] "r" (b), [y] "r" (c));\
asm volatile ("roli %[z], %[x], 12\n\t" \
		: [z] "=r" (b) \
		: [x] "r" (b));\
\
asm volatile ( "add %[z], %[x], %[y]\n\t"\
        : [z] "=r" (a)\
        : [x] "r" (a), [y] "r" (b));\
asm volatile ( "xor %[z], %[x], %[y]\n\t"\
        : [z] "=r" (d)\
        : [x] "r" (d), [y] "r" (a));\
asm volatile ("roli %[z], %[x], 8\n\t" \
		: [z] "=r" (d) \
		: [x] "r" (d));\
\
asm volatile ( "add %[z], %[x], %[y]\n\t"\
        : [z] "=r" (c)\
        : [x] "r" (c), [y] "r" (d));\
asm volatile ( "xor %[z], %[x], %[y]\n\t"\
        : [z] "=r" (b)\
        : [x] "r" (b), [y] "r" (c));\
asm volatile ("roli %[z], %[x], 7\n\t" \
		: [z] "=r" (b) \
		: [x] "r" (b));\
})

#define ROUNDS 20

#define read_csr(reg) ({unsigned long __tmp;\
asm volatile ("csrr %0, " #reg : "=r"(__tmp));\
__tmp;})
 
unsigned main()
{   long inst1, inst2;
    
	unsigned in[16] = {
	0x61707876,0x3320646E,0x79622D32,0x6B206574,
	0x13020100,0x17060504,0x1b0a0908,0x1f0e0d0c,
  	0x23020100,0x27060504,0x2b0a0908,0x2f0e0d0c,
  	0x00000001,0x37060504,0x3b0a0908,0x3f0e0d0c};
	
	unsigned x[16] ={
	0x61707876,0x3320646E,0x79622D32,0x6B206574,
	0x13020100,0x17060504,0x1b0a0908,0x1f0e0d0c,
  	0x23020100,0x27060504,0x2b0a0908,0x2f0e0d0c,
  	0x00000001,0x37060504,0x3b0a0908,0x3f0e0d0c};

	unsigned pt[16] = {
	0x00000001,0x00000002,0x00000003,0x00000004,
	0x00000005,0x00000006,0x00000007,0x00000008,
	0x00000009,0x0000000a,0x0000000b,0x0000000c,
	0x0000000d,0x0000000e,0x0000000f,0x00000010};	
	
	unsigned out[16];
    
    inst1 = read_csr(instret); // start
				
	// 10 loops × 2 rounds/loop = 20 rounds
	for (int i = 0; i < ROUNDS; i += 2) {
		// Odd round
		QR(x[0], x[4], x[ 8], x[12]); 
		QR(x[1], x[5], x[ 9], x[13]); 
		QR(x[2], x[6], x[10], x[14]); 
		QR(x[3], x[7], x[11], x[15]); 
		// Even round
		QR(x[0], x[5], x[10], x[15]); 
		QR(x[1], x[6], x[11], x[12]); 
		QR(x[2], x[7], x[ 8], x[13]);
		QR(x[3], x[4], x[ 9], x[14]);
		
	}
	
    inst2 = read_csr(instret); // end

    printf("chacha 20 rounds instruction counts: %ld\n", inst2 - inst1);
	
	for (int i = 0; i < 16; ++i)
		out[i] = x[i] + in[i];

	for (int i = 0; i < 16; ++i)
		out[i] ^= pt[i];

	for (int i = 0; i < 16; i++) {

		printf("%08x ",out[i]);
		printf("%d\n",i);

	}

  return out[16];	
		
}