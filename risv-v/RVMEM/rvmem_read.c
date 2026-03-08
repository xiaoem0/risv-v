#include "rvmem.h"

uint8 rvmem_read8(rvmem* mem, uint32 addr) {
    if (!rvmem_check(mem, addr)) {
        printf("read8 fail\n");
        return;
    }
    uint32 offset = addr - mem->base;
    return mem->mem[offset];
}

uint16 rvmem_read16(rvmem* mem, uint32 addr) {
    if (!rvmem_check(mem, addr)) {
        printf("read16 fail\n");
        return;
    }
    uint16 val = 0;
    uint32 offset = addr - mem->base;
    val = mem->mem[offset];
    val = val | (mem->mem[offset + 1] << 8);
    return val;
}

uint32 rvmem_read32(rvmem* mem, uint32 addr) {
    if (!rvmem_check(mem, addr)) {
        printf("write32 fail\n");
        return;
    }
    uint32 val = 0;
    uint32 offset = addr - mem->base;
    val = mem->mem[offset];
    val |= (mem->mem[offset + 1] << 8);
    val |= (mem->mem[offset + 2] << 16);
    val |= (mem->mem[offset + 3] << 24);
    return val;
}