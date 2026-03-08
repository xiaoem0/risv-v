# CMakeList.txt: risv-v 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。
add_executable (risv-v "risv-v.c"  "RVMEM/rvmem.h" "RVMEM/rvmem_write.c" "RVMEM/rvmem.c" "RVMEM/rvmem_read.c" "RVCPU/rvcpu.c" "RVCPU/rvcpu.h" "uint.h" "RVCPU/rv_rdecode.c" "RVCPU/rv_idecode.c" "RVCPU/rv_jdecode.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET risv-v PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
