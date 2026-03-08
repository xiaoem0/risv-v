#include "rvcpu.h"
#define JAL_OFFSET(instr)  {                                        \
    uint32_t imm20 = ((instr) >> 31) & 0x1;                          \
    uint32_t imm10_1 = ((instr) >> 21) & 0x3FF;                      \
    uint32_t imm11 = ((instr) >> 20) & 0x1;                          \
    uint32_t imm19_12 = ((instr) >> 12) & 0xFF;                      \
    uint32_t imm_20bit = (imm20 << 19) | (imm19_12 << 11) | (imm11 << 10) | imm10_1; \
    int32_t offset = imm20 ? (int32_t)(0xFFFFF000 | imm_20bit) : (int32_t)imm_20bit; \
    offset << 1;                                                     \
}

void rv_decode_J(uint32 pc, Rvcpu_ISA_J* J_decode) {
	J_decode->opcode = pc & 0x7F;
	J_decode->rd = (pc >> 7) & 0x1F;
	J_decode->offset  = (pc >> 12) & 0xFF;
	return;
}

void execute_jtype(rvcpu* cpu, const Rvcpu_ISA_I* i) {
	uint32 scr1 = cpu->Registers[i->rs1];
	JAL_OFFSET()

	switch (i->funct3) {
	case addi://加法立即数
		cpu->Registers[i->rd] = cpu->Registers[i->rs1] + imm;
		printf("addi  rd[%d]  rc1[%d]  %d->rc1:%d + imm: %d = rd: %d\n", i->rd, i->rs1, i->imm, cpu->Registers[i->rs1], imm, cpu->Registers[i->rd]);
		goto R0_0;
	case slli://逻辑左移
		cpu->Registers[i->rd] = cpu->Registers[i->rs1] << (imm & 0x1F);
		printf("slli  rd[%d]  rc1[%d]  %d->rc1:%d << imm: %d = rd: %d\n", i->rd, i->rs1, i->imm, cpu->Registers[i->rs1], imm & 0x1F, cpu->Registers[i->rd]);
		goto R0_0;
	case slti://有符号比较大小
		cpu->Registers[i->rd] = (((int32)cpu->Registers[i->rs1]) < ((int32)imm)) ? 1 : 0;
		printf("slti  rd[%d]  rc1[%d]  %d->rc1:%d < imm: %d = rd: %d\n", i->rd, i->rs1, i->imm, cpu->Registers[i->rs1], imm & 0x1F, cpu->Registers[i->rd]);
		goto R0_0;
	case sltiu://无符号比较大小
		cpu->Registers[i->rd] = ((cpu->Registers[i->rs1]) < ((uint32)imm)) ? 1 : 0;
		printf("sltiu  rd[%d]  rc1[%d]  %d->rc1:%d < imm: %d = rd: %d\n", i->rd, i->rs1, i->imm, cpu->Registers[i->rs1], imm & 0x1F, cpu->Registers[i->rd]);
		goto R0_0;
	case xori://异或
		cpu->Registers[i->rd] = cpu->Registers[i->rs1] ^ imm;
		printf("xori  rd[%d]  rc1[%d]  %d->rc1:%d < imm: %d = rd: %d\n", i->rd, i->rs1, i->imm, cpu->Registers[i->rs1], imm & 0x1F, cpu->Registers[i->rd]);
		goto R0_0;
	case srli_srai:
		switch ((i->imm >> 30) & 0x1) {
		case 0:
			cpu->Registers[i->rd] = cpu->Registers[i->rs1] >> (imm & 0x1F);
			printf("srli  rd[%d]  rc1[%d]  %d->rc1:%d >> imm: %d = rd: %d\n", i->rd, i->rs1, i->imm, cpu->Registers[i->rs1], imm & 0x1F, cpu->Registers[i->rd]);
			goto R0_0;
		case 1:
			cpu->Registers[i->rd] = ((int32)cpu->Registers[i->rs1]) >> (imm & 0x1F);
			printf("srai  rd[%d]  rc1[%d]  %d->rc1:%d >> imm: %d = rd: %d\n", i->rd, i->rs1, i->imm, cpu->Registers[i->rs1], imm & 0x1F, cpu->Registers[i->rd]);
			goto R0_0;
		}
	case ori:
		cpu->Registers[i->rd] = cpu->Registers[i->rs1] | imm;
		printf("ori  rd[%d]  rc1[%d]  %d->rc1:%d | imm: %d = rd: %d\n", i->rd, i->rs1, i->imm, cpu->Registers[i->rs1], imm, cpu->Registers[i->rd]);
		goto R0_0;
	case andi:
		cpu->Registers[i->rd] = cpu->Registers[i->rs1] & imm;
		printf("andi  rd[%d]  rc1[%d]  %d->rc1:%d & imm: %d = rd: %d\n", i->rd, i->rs1, i->imm, cpu->Registers[i->rs1], imm & 0x1F, cpu->Registers[i->rd]);
		goto R0_0;
	default:
		printf("risc-v isa not is i opcode");
		break;
	}

	return;

R0_0:
	if (i->rd == 0) {
		cpu->Registers[i->rd] = 0;
	}
	return;
}
