// risv-v.cpp: 定义应用程序的入口点。
//

#include <stdio.h>
#include "uint.h"
#include "RVMEM/rvmem.h"
#include "RVCPU/rvcpu.h"

int main()
{
    printf("Hello, Risv!\n");
    rvmem mem;
    rvmem_init(&mem, 0x80000000, mem_size);
    const char* test_image = "test_image.bin";
    //uint8_t test_data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
    uint32_t test_instructions[] = {
        0x12C00093, // addi x1, x0, 0x100
        //0x00000113, // addi x2, x0, 0x200
        0x000000B3,//add x1,x0,x0
        0x002081B3, // add x3, x1, x2   
        0x0030A023, // sw x3, 0(x1) → 地址=0x80000000 + x1 = 0x80000100
        0x0000A203, // lw x4, 0(x1) → 从0x80000100读取到x4
        0x00000000  // 空指令，终止执行
    };
    FILE* fp = fopen(test_image, "wb");
    if (fp) {
        fwrite(test_instructions, sizeof(test_instructions), sizeof(test_instructions)/sizeof(uint32), fp);
        fclose(fp);
    }
    // 2. 加载测试镜像到内存地址 0x80000010
    int load_size = rvmem_load_image(&mem, test_image, 0x80000010);
    if (load_size > 0) {
        // 3. 验证加载结果
        printf("验证加载结果：\n");
        printf("0x80000010: 0x%02X\n", rvmem_read8(&mem, 0x80000010));  // 应输出 0x01
        printf("0x80000013: 0x%02X\n", rvmem_read8(&mem, 0x80000013));  // 应输出 0x04
        printf("0x80000010 (32bit): 0x%08X\n", rvmem_read32(&mem, 0x80000010));  // 应输出 0x04030201
    }




    rvcpu cpu;
    uint32 val;
    Rvcpu_ISA_R r;
    rvcpu_init(&cpu, &mem, 0x80000010);
    val = rvcpu_get_pc(&cpu);
    printf("0x%08X\n",val );
    rvcpu_decode(&cpu, val);
    printf("0x%08X\n",cpu.pc);
    printf("regs r1 %u", cpu.Registers[1]);

    return 0;
}
