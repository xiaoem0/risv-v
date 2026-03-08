#include "rvcpu.h"

void rv_decode_i(uint32 pc, Rvcpu_ISA_I* I_decode) {
	I_decode->opcode = pc & 0x7F;
	I_decode->rd = (pc >> 7) & 0x1F;
	I_decode->funct3 = (pc >> 12) & 0x7;
	I_decode->rs1 = (pc >> 15) & 0x1F;
	I_decode->imm = (pc >> 20) & 0xFFF;
	return;
}

void execute_itype(rvcpu* cpu, const Rvcpu_ISA_I*  i) {
	uint32 scr1 = cpu->Registers[i->rs1];
	int32 imm = (i->imm)&0x800? (i->imm)|0xFFFFF000:i->imm;

	switch (i->funct3) {
		case addi://加法立即数
			cpu->Registers[i->rd] = cpu->Registers[i->rs1] + imm;
			printf("addi  rd[%d]  rc1[%d]  %d->rc1:%d + imm: %d = rd: %d\n", i->rd, i->rs1, i->imm, cpu->Registers[i->rs1],imm, cpu->Registers[i->rd]);
			goto R0_0;
		case slli://逻辑左移
			cpu->Registers[i->rd] = cpu->Registers[i->rs1] << (imm & 0x1F);
			printf("slli  rd[%d]  rc1[%d]  %d->rc1:%d << imm: %d = rd: %d\n", i->rd, i->rs1, i->imm, cpu->Registers[i->rs1], imm & 0x1F, cpu->Registers[i->rd]);
			goto R0_0;
		case slti://有符号比较大小
			cpu->Registers[i->rd] = (((int32)cpu->Registers[i->rs1])<((int32)imm))?1:0 ;
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
			cpu->Registers[i->rd] = cpu->Registers[i->rs1] &imm;
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
