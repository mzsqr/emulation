#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include "verilated.h"
#include "Vcounter.h"

using namespace tlm;
using namespace tlm_utils;

SC_MODULE(Target) {
    tlm_utils::simple_target_socket<Target> socket;
    Vcounter* counter;

    SC_CTOR(Target) {
        // Do nothing
    }

    void b_transport(tlm_generic_payload& trans, sc_time& delay){
        tlm_command cmd = trans.get_command();
        sc_dt::uint64 addr = trans.get_address();
        unsigned char* data = trans.get_data_ptr();
        unsigned int len = trans.get_data_length();
        unsigned char* byte_en = trans.get_byte_enable_ptr();
        unsigned int wid = trans.get_streaming_width();

        switch (cmd)
        {
        case TLM_READ_COMMAND:
            
            break;
        
        default:
            break;
        }
    }
}; // 记住这个分号