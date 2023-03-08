# 这个文件相当于testbench
# 编译生成链接库 在./build下

from pysv import sv, compile_lib, generate_sv_binding, DataType, generate_cxx_binding
import random
import numpy as np

class RandArray:
    @sv(len=DataType.UInt)
    def __init__(self, len) -> None:
        self.__array = np.random.randint(0, 127, len, dtype=np.byte)

    @sv(i=DataType.UInt, return_type=DataType.UByte)
    def get(self, i):
        return self.__array[i]

    @sv(return_type=DataType.UInt)
    def len(self):
        return len(self.__array)
    

@sv(return_type=DataType.String, len=DataType.UInt)
def get_rand_array(len):
    """传递一个随机数组"""
    return np.random.randint(1, 127, len, dtype="byte").tobytes()

# 编译代码，默认名字libpysv.so
# lib_path = compile_lib([generate_num], cwd="build")
# 生成sv的biding
# generate_sv_binding([generate_num], filename="hdl/pysv.sv")
# 生成DPI头文件，如果要在verilator里面使用这些导出函数才使用这个
# generate_cxx_binding([generate_array], filename="dpi_header.cpp")

# lib_path = compile_lib([RandArray], cwd='build')
# generate_sv_binding([RandArray], filename="hdl/rand_array.sv", pkg_name="rand_array")

lib_path = compile_lib([get_rand_array], cwd='build')
generate_sv_binding([get_rand_array], filename="hdl/rand_array.sv", pkg_name="rand_array")
