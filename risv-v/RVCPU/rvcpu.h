#ifndef RVCPU_H
#define RVCPU_H


#include "../RVMEM/rvmem.h"

//Risc-Cpu结构体
typedef struct {
	uint32 pc;
	uint32 Registers[32];
	rvmem* mem;
}rvcpu;


//R型指令集结构体和功能码枚举
enum R_Funct3 {
	add_sub,
	sll,
	slt,
	sltu,
	xor,
	srl_sra,
	or,
	and
};

enum Funt7 {
	funct7_1,
	funct7_2 = 64
};

typedef struct {
	uint8 opcode;
	uint8 rd;
	uint8 funct3;
	uint8 rs1;
	uint8 rs2;
	uint8 funct7;
}Rvcpu_ISA_R;



//I型指令集结构体
enum I_Funct3 {
	addi,
	slli,
	slti,
	sltiu,
	xori,
	srli_srai,
	ori,
	andi
};
typedef struct {
	uint8 opcode;
	uint8 rd;
	uint8 funct3;
	uint8 rs1;
	uint16 imm;
}Rvcpu_ISA_I;

//J型指令结构体
typedef struct {
	uint8 opcode;
	uint8 rd;
	uint32 offset;
}Rvcpu_ISA_J;


//R/I/J opceode
enum opcode_name {
		I = 19,
		R = 51,
		J=111
};
//rv_cpu初始化
void rvcpu_init(rvcpu* cpu, rvmem* mem, uint32 entry_addr);
//rv_cpu获取内存指令
uint32 rvcpu_get_pc(rvcpu* cpu);

//risc-v中R型指令集函数
void rv_decode_r(uint32 pc, Rvcpu_ISA_R* R_decode);
void execute_rtype(rvcpu* cpu, Rvcpu_ISA_R  r);


//risc-v中I型指令集函数
void rv_decode_i(uint32 pc, Rvcpu_ISA_I* I_decode);
void execute_itype(rvcpu* cpu, const Rvcpu_ISA_I* i);

#endif