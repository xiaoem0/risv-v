#ifndef RVCPU_H
#define RVCPU_H


#include "../RVMEM/rvmem.h"

//Risc-Cpu结构体
typedef struct {
	uint32 pc;
	uint32 Registers[32];
	rvmem* mem;
}rvcpu;


//R/I/J opceode
typedef enum opcode_name {
		Load =3,
		I = 19,
		Store =35,
		R = 51,
		J=111
}Opcode;

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
	Opcode opcode;
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

//S型指令结构体
typedef struct {
	Opcode opcode;
	uint8 funt3;
	uint8 rs1;
	uint8 rs2;
	uint32 imm;
}Rvcpu_ISA_S;





//Load-funt3-type
typedef enum {
	LOAD_TYPE_LB = 0x0, // 加载字节（有符号）
	LOAD_TYPE_LH = 0x1, // 加载半字（有符号）
	LOAD_TYPE_LW = 0x2, // 加载字
	LOAD_TYPE_LBU = 0x4, // 加载字节（无符号）
	LOAD_TYPE_LHU = 0x5, // 加载半字（无符号）
	LOAD_TYPE_UNKNOWN = 0xFF
} LoadType;
//Store-funt3-type
typedef enum {
	STORE_TYPE_SB = 0x0, // 存储字节
	STORE_TYPE_SH = 0x1, // 存储半字
	STORE_TYPE_SW = 0x2, // 存储字
	STORE_TYPE_UNKNOWN = 0xFF
} StoreType;
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

//J型指令译码和执行函数
void rv_decode_r(uint32 pc, Rvcpu_ISA_R* R_decode);
void execute_jtype(rvcpu* cpu, const Rvcpu_ISA_J* j);

//S型指令译码和执行函数
void rv_decode_S(uint32 pc, Rvcpu_ISA_S* S_decode);
void execute_stype(rvcpu* cpu, const Rvcpu_ISA_S* s);
#endif