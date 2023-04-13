# SystemC + TLM 示例代码 

## 一般的编译过程 -- 原型验证(没有RTL代码) -- adder

1. 复制一份Makefile.run
2. 自己写Makefile.config 配置SystemC的路径
3. 自己写Makefile作为入口文件

## 加上Verilator的编译过程　－－　adder_with_veilator -- 还想不清楚

1. 先要设置好环境变量　－－　SYSTEMC_INCLUDE SYSTEMC_LIBDIR
2. verilator 时加上　－－　sc选项就可以接入自己的sc啦，当然还要自己写sc_main