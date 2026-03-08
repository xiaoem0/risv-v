#include "rvmem.h"

// 初始化内存
void rvmem_init(rvmem* mem, uint32 base, uint32 size) {
    mem->base = base;
    mem->size = size;
    memset(mem->mem, 0, mem_size);
} 

//地址越界检查
_Bool rvmem_check(rvmem* mem, uint32 addr) {
    if (addr > mem->base || addr < mem->base + mem->size) {
        return 1;
    }
    else {
        return 0;
    }
}

//加载镜像
int rvmem_load_image(rvmem* mem, const char* file_path,uint32 addr_load) {
    FILE* fp = fopen(file_path, "rb");
    if (fp == NULL) {
        printf("file open fail");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    long file_size= ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (file_size == -1) {
        printf("file_size fail");
        fclose(fp);
        return -1;
    }

    if (!(rvmem_check(mem, addr_load) && rvmem_check(mem, addr_load + file_size)) ){
        printf("ADDR_LOAD fail\n");
        return -1;
    }
     
    uint32 offset = addr_load - mem->base;
    size_t read_bytes = fread(mem->mem + offset, sizeof(uint8), file_size, fp);
    if (read_bytes != file_size) {
        printf("image fail\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    printf("image success load_addr: 0x%08X,File_path: %s\n", addr_load, file_path);


    return 1;

}