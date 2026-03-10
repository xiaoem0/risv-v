#include "rvcpu.h"                                        


void rv_decode_B(uint32 pc, Rvcpu_ISA_B* B_decode) {
	B_decode->opcode = pc & 0x7F;
	B_decode->funt3 = (pc >> 12) & 0x7;
	B_decode->rs1 = (pc >> 15) & 0x1F;
	B_decode->rs2 = (pc >> 20) & 0x1F;
	uint32 imm =  0;
	uint32 imm_11 = (pc >> 7) & 0x1;
	uint32 imm_4_1 = (pc >> 8) & 0xF;
	uint32 imm_10_5 = (pc >> 25) & 0x3F;
	uint32 imm_12 = (pc >> 31) & 0x1;
	imm =  (imm_12<<12 ) | (imm_11 << 11) | (imm_10_5 << 5) | (imm_4_1<<1);
	imm =(imm&0x1000)?(imm|0xFFFF1000):imm;
	B_decode->imm = imm << 1;
	return;
}

void execute_Btype(rvcpu* cpu, const Rvcpu_ISA_B* b) {
	int ret = 0;
	int32 src1= (int32)cpu->Registers[b->rs1];
	int32 src2 = (int32)cpu->Registers[b->rs2];
	uint32 usrc1 = cpu->Registers[b->rs1];
	uint32 usrc2 = cpu->Registers[b->rs2];
	uint32 next_pc = cpu->pc + b->imm;
	switch (b->funt3) {
	case beq:
		ret = (src1 == src2);
		break;
	case bne:
		ret = (src1 != src2);
		break;
	case blt:
		ret = (src1 < src2);
		break;
	case bge:
		ret = (src1 >= src2);
		break;
	case bltu:
		ret = (usrc1 < usrc2);
	case bgeu:
		ret = (usrc1 >= usrc2);
	default:
		break;
	}

	if (ret) {
		cpu->pc = next_pc; // 条件满足，跳转
		printf("    → PC跳转到0x%08X\n", cpu->pc);
	}
	else {
		cpu->pc += 0x04; // 条件不满足，顺序执行
	}
	return;
}