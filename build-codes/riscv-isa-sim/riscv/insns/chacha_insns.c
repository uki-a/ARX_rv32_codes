/*root@affa35580b2f:/work/riscv-isa-sim/riscv/insns# cat xor_rol12.h  xor_rol16.h  xor_rol7.h   xor_rol8.h*/
// xor, rol12
int shamt = 12 & (xlen-1);
int rshamt = -shamt & (xlen-1);
WRITE_RD(sext_xlen(((RS1 ^ RS2) << shamt) | (zext_xlen(RS1 ^ RS2) >> rshamt)));
// xor, rol16
int shamt = 16 & (xlen-1);
int rshamt = -shamt & (xlen-1);
WRITE_RD(sext_xlen(((RS1 ^ RS2) << shamt) | (zext_xlen(RS1 ^ RS2) >> rshamt)));
// xor, rol7
int shamt = 7 & (xlen-1);
int rshamt = -shamt & (xlen-1);
WRITE_RD(sext_xlen(((RS1 ^ RS2) << shamt) | (zext_xlen(RS1 ^ RS2) >> rshamt)));
// xor, rol8
int shamt = 8 & (xlen-1);
int rshamt = -shamt & (xlen-1);
WRITE_RD(sext_xlen(((RS1 ^ RS2) << shamt) | (zext_xlen(RS1 ^ RS2) >> rshamt)));