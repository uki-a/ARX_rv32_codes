/*root@affa35580b2f:/work/riscv-isa-sim/riscv/insns# cat add_rol5_xor.h && cat add_rol8_xor.h && cat add_rol7_xor.h && cat add_rol13_xor.h && cat add_rol16.h*/
// add, xor, roli
int shamt = 5 & (xlen-1);
int rshamt = -5 & (xlen-1);
WRITE_RD(sext_xlen((RS1 + RS2)) ^ sext_xlen(((RS1 << shamt) | (zext_xlen(RS1) >> rshamt))));
// add, xor, roli
int shamt = 8 & (xlen-1);
int rshamt = -8 & (xlen-1);
WRITE_RD(sext_xlen((RS1 + RS2)) ^ sext_xlen(((RS1 << shamt) | (zext_xlen(RS1) >> rshamt))));
// add, xor, roli
int shamt = 7 & (xlen-1);
int rshamt = -7 & (xlen-1);
WRITE_RD(sext_xlen((RS1 + RS2)) ^ sext_xlen(((RS1 << shamt) | (zext_xlen(RS1) >> rshamt))));
// add, xor, roli
int shamt = 13 & (xlen-1);
int rshamt = -13 & (xlen-1);
WRITE_RD(sext_xlen((RS1 + RS2)) ^ sext_xlen(((RS1 << shamt) | (zext_xlen(RS1) >> rshamt))));
// xor, rol16
int shamt = 16 & (xlen-1);
int rshamt = -shamt & (xlen-1);
WRITE_RD(sext_xlen(((RS1 + RS2) << shamt) | (zext_xlen(RS1 + RS2) >> rshamt)));