`verilator --cc --exe --build --sv hdl/pysv.sv hdl/our.sv sim_main.cpp ../build/libpysv.so`

`verilator --cc --exe --build --sv --timing  hdl/rand_array.sv hdl/adder.v hdl/our.sv sim_main.cpp ../build/libpysv.so`

# DPI性能测试

> verilator版本：5.002


> ## Pysv相关说明
> Pysv目前还没有传递数组的方法，所以目前采用的方法是将数组存储在python端（numpy），在sv要使用时才调用函数获取
> 
> 基于Pybind11，这种方法实际上是使用SV调用python代码
>
>已经支持的数据类型 


-----


## 基于加法器的测试（每次只传递一个字节）

测试结果：verilator每次推进一千个时钟

|数据量（组，每组16bit）|模拟器运行时间|
|-|-|
|200000|2.671s|
|2000000|24.799s|
|20000000|3m59.799s|


## 基于加法器的测试2（使用string）

测试结果：verilator每次推进1000个clock

|数据量（组，每组16bit）|模拟器运行时间|
|-|-|
|2000000|0.473s|
|20000000|2.212s|
|200000000|20.326s|

相比较之下，在服务器上运行cocotb（verilator）下沉BFM时的效率要高大约三倍左右，进行两百万次加法器的模拟所需时间最优接近**1.3s**（对比表中第一行）

## 流程

1. 运行python生成头文件和动态链接库
`python3 test_adder.py`

2. 将动态链接库+sv+verilog的各个部分都放在一起运行模拟器
>也许需要设置LD_LIBRARY_PATH
