/*root@affa35580b2f:/work/riscv-isa-sim/riscv/insns# cat ror8_add.h */
int shamt = 8 & (xlen-1);
int rshamt = -shamt & (xlen-1);
WRITE_RD( sext_xlen((RS1 << rshamt) | (zext_xlen(RS1) >> shamt)) + sext_xlen(RS2) );