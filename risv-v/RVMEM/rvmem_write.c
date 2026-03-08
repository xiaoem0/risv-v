#include "rvmem.h"

//读内存8字节
void rvmem_write8(rvmem* mem, uint32 addr, uint8 data) {
    if (!rvmem_check(mem, addr)) {
        printf("write8 fail\n");
        return;
    }
    uint32 offset = addr - mem->base;
    mem->mem[offset] = data;
}


//读内存16字节
void rvmem_write16(rvmem* mem, uint32 addr, uint16 val) {
    if (!rvmem_check(mem, addr)) {
        printf("write16 fail\n");
        return;
    }
    uint32 offset = addr - mem->base;
    mem->mem[offset] = val & 0xFF;
    mem->mem[offset + 1] = (val >> 8) & 0xFF;
}


//读内存32字节
void rvmem_write32(rvmem* mem, uint32 addr, uint32 val) {
    if (!rvmem_check(mem, addr)) {
        printf("write32 fail\n");
        return;
    }
    uint32 offset = addr - mem->base;
    mem->mem[offset] = val & 0xFF;
    mem->mem[offset + 1] = (val >> 8) & 0xFF;
    mem->mem[offset + 2] = (val >> 16) & 0xFF;
    mem->mem[offset + 3] = (val >> 24) & 0xFF;
}
