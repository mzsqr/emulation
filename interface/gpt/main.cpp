#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include "Vcounter_8bit.h"

struct Transaction : public tlm::tlm_generic_payload {
  int data;
  Transaction() : data(0) {}
};

SC_MODULE(Counter) {
  tlm::tlm_target_socket<> socket;
  Vcounter_8bit* dut;

  SC_CTOR(Counter) : socket("counter socket"){
    dut = new Vcounter_8bit("counter");
  }
}

SC_MODULE(Testbench) {
  tlm_utils::simple_initiator_socket<Testbench> socket;
  sc_core::sc_out<bool> clk;
  sc_core::sc_out<bool> rst_n;

  void run() {
    Transaction tx;
    for (int i = 0; i < 256; i++) { // 发送 256 个事务
      tx.data = i;
      auto t {sc_core::sc_time(1, sc_core::SC_NS)};
      socket->b_transport(tx, t); // 发送事务到计数器
      sc_core::wait(1, sc_core::SC_NS); // 等待一个时钟周期
      if (i == 255) { // 最后一个事务
        if (tx.data != 0) { // 检查计数器是否正确复位
          std::cerr << "Error: counter not reset correctly" << std::endl;
          sc_core::sc_stop();
        }
      } else {
        if (tx.data != i + 1) { // 检查计数器是否正确计数
          std::cerr << "Error: counter not counting correctly" << std::endl;
          sc_core::sc_stop();
        }
      }
    }
    std::cout << "Test passed!" << std::endl;
    sc_core::sc_stop();
  }

  SC_CTOR(Testbench) {
    SC_THREAD(run);
    sensitive << clk.pos();
  }
};

int sc_main(int argc, char* argv[]) {
  // 实例化测试平台和计数器
  Testbench tb("testbench");
  Vcounter_8bit counter("counter");

  // 连接测试平台和计数器
  counter.clk(tb.clk);
  counter.rst(tb.rst_n);
  tb.socket.bind(counter.socket);

  // 开始仿真
  sc_core::sc_start(1000, sc_core::SC_NS);

  return 0;
}