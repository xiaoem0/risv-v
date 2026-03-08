#include "rvcpu.h"

//译码函数
void rv_decode_r(uint32 pc, Rvcpu_ISA_R * R_decode) {
	R_decode->opcode = pc & 0x7F;
	R_decode->rd = (pc >> 7) & 0x1F;
	R_decode->funct3 = (pc >> 12) & 0x7;
	R_decode->rs1 = (pc >> 15) & 0x1F;
	R_decode->rs2 = (pc >> 20) & 0x1F;
	R_decode->funct7 = (pc >> 25) & 0x7F;
	return;
}


//cpu执行函数
void execute_rtype(rvcpu* cpu,Rvcpu_ISA_R  r) {
	uint32 src1 = cpu->Registers[r.rs1];
	uint32 src2 = cpu->Registers[r.rs2];
	switch (r.funct3)
	{
	case add_sub://加法和减法指令
		if (r.funct7 == funct7_1) {
			cpu->Registers[r.rd] = src1 + src2;
			printf("add  rd[%d]  rc1[%d]  rc2[%d]->rc1:%d + rc2: %d =rd: %d\n", r.rd, r.rs1, r.rs2, cpu->Registers[r.rs1], cpu->Registers[r.rs2], cpu->Registers[r.rd]);
		}
		else if(r.funct7== funct7_2){
			cpu->Registers[r.rd] = src1 - src2;
			printf("sub  rd[%d]   rc1[%d]  rc2[%d]->rc1:%d  - rc2: %d =rd: %d\n", r.rd, r.rs1, r.rs2, cpu->Registers[r.rs1], cpu->Registers[r.rs2], cpu->Registers[r.rd]);
		}
		else {
			printf("fail \n");
			return;
		}
		goto R0_0;

	case sll://逻辑左移指令
		cpu->Registers[r.rd] = src1 << (src2&0x1F);
		printf("sll  rd[%d]  rc1[%d]  rc2[%d]->rc1:%d <<rc2: %d =rd: %d\n", r.rd, r.rs1, r.rs2, cpu->Registers[r.rs1], ((cpu->Registers[r.rs2])&0x1F), cpu->Registers[r.rd]);
		goto R0_0;

	case slt://比较有符号俩个数指令
		cpu->Registers[r.rd] = ((int32)src1 < (int32)src2) ? 1 : 0;
		printf("slt  rd[%d]  rc1[%d]  rc2[%d]->rc1:%d < rc2: %d ? 1:0=rd: %d\n", r.rd, r.rs1, r.rs2, cpu->Registers[r.rs1], cpu->Registers[r.rs2], cpu->Registers[r.rd]);
		goto R0_0;

	case sltu://比较无符号俩个数指令
		cpu->Registers[r.rd] = (src1 < src2) ? 1 : 0;
		printf("sltu  rd[%d]  rc1[%d]  rc2[%d]->rc1:%u < rc2: %u ? 1:0=rd: %d\n", r.rd, r.rs1, r.rs2, cpu->Registers[r.rs1], cpu->Registers[r.rs2], cpu->Registers[r.rd]);
		goto R0_0;

	case xor://异或指令
		cpu->Registers[r.rd] = src1 ^ src2;
		printf("xor  rd[%d]  rc1[%d]  rc2[%d]->rc1:%d ^ rc2: %d =rd: %d\n", r.rd, r.rs1, r.rs2, cpu->Registers[r.rs1], cpu->Registers[r.rs2], cpu->Registers[r.rd]);
		goto R0_0;

	case srl_sra://逻辑右移和算数右移
		if (r.funct7 == funct7_1) {
			cpu->Registers[r.rd] = src1 >> (src2 & 0x1F);
			printf("srl  rd[%d]  rc1[%d]  rc2[%d]->rc1:%d >> rc2: %d =rd: %d\n", r.rd, r.rs1, r.rs2, cpu->Registers[r.rs1], cpu->Registers[r.rs2], cpu->Registers[r.rd]);
		}
		else if(r.funct7==funct7_2){
			cpu->Registers[r.rd] = ((int32)src1) >> (src2 & 0x1F);
			printf("sra  rd[%d]  rc1[%d]  rc2[%d]->rc1:%d >> rc2: %d =rd: %d\n", r.rd, r.rs1, r.rs2, cpu->Registers[r.rs1], cpu->Registers[r.rs2], cpu->Registers[r.rd]);
		}
		else {
			printf("fail\n");
			return;
		}
		goto R0_0;

	case or://或指令
		cpu->Registers[r.rd] = src1 | src2 ;
		printf("or  rd[%d]  rc1[%d]  rc2[%d]->rc1:%d | rc2: %d =rd: %d\n", r.rd, r.rs1, r.rs2, cpu->Registers[r.rs1], cpu->Registers[r.rs2], cpu->Registers[r.rd]);
		goto R0_0;

	case and://与指令
		cpu->Registers[r.rd] = src1 & src2;
		printf("and  rd[%d]  rc1[%d]  rc2[%d]->rc1:%d && rc2: %d =rd: %d\n", r.rd, r.rs1, r.rs2, cpu->Registers[r.rs1], cpu->Registers[r.rs2], cpu->Registers[r.rd]);
		goto R0_0;

	default:
		break;
	}

	return;

R0_0:
	if (r.rd == 0) {
		cpu->Registers[r.rd] = 0;
	}
	return;
}











