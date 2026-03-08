#pragma once
#ifndef RVMEM_H
#define RVMEM_H


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../uint.h"


#define mem_size 1024



// 内存结构体
typedef struct {
    uint8 mem[mem_size];
    uint32 base; //内存起始地址
    uint32 size;//内存大小
} rvmem;


uint8 rvmem_read8(rvmem* mem, uint32 addr);
uint16 rvmem_read16(rvmem* mem, uint32 addr);
uint32 rvmem_read32(rvmem* mem, uint32 addr);

void rvmem_write8(rvmem* mem, uint32 addr, uint8 data);
void rvmem_write16(rvmem* mem, uint32 addr, uint16 data);
void rvmem_write32(rvmem* mem, uint32 addr, uint32 data);

void rvmem_init(rvmem* mem, uint32 base, uint32 size);
_Bool rvmem_check(rvmem* mem, uint32 addr);
int rvmem_load_image(rvmem* mem, const char* file_path, uint32 addr_load);


#endif //UINT_H