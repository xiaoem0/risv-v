#include <stdio.h>
#include "rvcpu.h"



//cpu初始化函数
void rvcpu_init(rvcpu* cpu,rvmem* mem, uint32 entry_addr) {
	cpu->pc = entry_addr;
	cpu->mem = mem;
	memset(cpu->Registers, 0, sizeof(cpu->Registers));
}


//cpu取值函数
uint32 rvcpu_get_pc(rvcpu* cpu) {
	uint32 pc_val = rvmem_read32(cpu->mem, cpu->pc);
	if (pc_val == 0) {
		return 0;
	}
	return pc_val;
}

//cpu译指和执行函数
int rvcpu_decode(rvcpu* cpu,uint32 pc) {
	Rvcpu_ISA_I i;
	Rvcpu_ISA_R r;
	switch (pc & 0x7F)
	{
	case I:
		rv_decode_i(pc,&i);
		execute_itype(cpu, &i);
		break;
	case R:
		rv_decode_r(pc, &r);
		execute_rtype(cpu, r);
		break;

	}
	//execute_rtype(cpu, );
	cpu->pc +=0x4 ;
}






