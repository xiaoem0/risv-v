#include "rvcpu.h"                                        


void rv_decode_S(uint32 pc, Rvcpu_ISA_S* S_decode) {
	S_decode->opcode = pc & 0x7F;
	S_decode->funt3 = (pc >> 12) & 0x7;
	S_decode->rs1 = (pc >> 15) & 0x1F;
	S_decode->rs2 = (pc >> 20) & 0x1F;
	uint32 imm =  (((pc>>7)&0x1F) | ((pc>>20)&0xFE0));
	S_decode->imm = imm&0x800?(imm| 0xFFFFF000): imm;
	return;
}

void execute_stype(rvcpu* cpu, const Rvcpu_ISA_S* s) {
	switch (s->funt3) {
		case STORE_TYPE_SB:
			rvmem_write8(cpu->mem, cpu->Registers[s->rs1] + s->imm, (cpu->Registers[s->rs2])>>0xFF);
			break;
		case STORE_TYPE_SH:
			rvmem_write16(cpu->mem, cpu->Registers[s->rs1] + s->imm, (cpu->Registers[s->rs2]) >> 0xFF);
			break;
		case STORE_TYPE_SW:
			rvmem_write32(cpu->mem, cpu->Registers[s->rs1] + s->imm, (cpu->Registers[s->rs2]) >> 0xFF);
			break;
		default:
			break;
	}
	return;

}