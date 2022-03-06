/*root@affa35580b2f:/work/riscv-isa-sim/riscv/insns# cat roli.h*/
//require_extension(EXT_ZBB);
require(SHAMT < xlen);
int shamt = SHAMT & (xlen-1);
int rshamt = -shamt & (xlen-1);
WRITE_RD(sext_xlen((RS1 << shamt) | (zext_xlen(RS1) >> rshamt)));