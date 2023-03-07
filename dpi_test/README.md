`verilator --cc --exe --build --sv hdl/pysv.sv hdl/our.sv sim_main.cpp ../build/libpysv.so`

`verilator --cc --exe --build --sv --timing  hdl/rand_array.sv hdl/adder.v hdl/our.sv sim_main.cpp ../build/libpysv.so`

# DPI性能测试


> ## Pysv相关说明
> Pysv目前还没有传递数组的方法，所以目前采用的方法是将数组存储在python端（numpy），在sv要使用时才调用函数获取
> 
> 基于Pybind11，这种方法实际上是使用SV调用python代码


-----


## 基于加法器的测试

测试结果：verilator每次推进一千个时钟

|数据量（组，每组16bit）|模拟器运行时间|
|-|-|
|200000|2.671s|
|2000000|24.799s|
|20000000|3m59.799s|
