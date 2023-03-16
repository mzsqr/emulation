# TLM-CPP (Simple version)


## TLM数据传输接口

包含以下内容：
> put
> 
> get
>
> peek
>
> try_put
> 
> try_get
>
> try_peek
>
> can_put
>
> can_get
>
> can_peek
>
> transport
>
> nb_transport
>
> write
>
> put_req
> 
> put_response
>
> get_next_item
>
> item_done
>
> get_response
>

目前只实现了put和get(3/16)

另外关于TLM其它的阻塞非阻塞端口的概念就暂时不再实现了


-----

## 工作流程

- 用户需要继承DataSource基类,实现自己的数据传输方法,但是中间通过DPI传输的细节都被屏蔽掉了
- 用户继承的DataSource类需要通过DataSourceMgr进行注册,注册的方式可以提供两种
  1. 对于工作在C++语言验证环境下的验证工作,可以在入口函数中注册
  2. 其它验证环境则需要通过SV端进行注册,可以自行编译init函数,并且在SV端开始时调用
- 在SV端使用数据源时,只需要通过getDataSourceByName方法获取数据源指针,使用该指针进行调用

---

## 示例

sim_main.cpp 中包含继承的DataSource类,test.sv中为使用示例

编译:`verilator --cc --exe --build --sv sim_main.cpp tlm.sv test.sv tlm.cpp` (编译时间可能略长,之后先把tlm的部分编译为链接库)