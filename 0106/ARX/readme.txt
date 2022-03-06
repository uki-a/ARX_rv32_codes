chacha20.c   
	chacha20 length=512bit

chaskey12_512.c 
	same as chaskey12_wom.c but length=512bit	

simon_test_512_noks.c
	simon length=512bit, no key schedule

speck_test_512_noks.c
	speck length=512bit, no key schedule


// to enable key schedule, do not initialize rk but initialize K,
// and uncomment code session "enable for ks"

