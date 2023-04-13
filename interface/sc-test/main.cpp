#include <systemc>
#include <tlm>
#include <iostream>

using namespace sc_core;
using namespace std;

SC_MODULE(half_adder)
{
    sc_in<bool> a, b;
    sc_out<bool> sum, carry;
    void prc_half_add()
    {
        sum = a^b;
        carry = a&b;
    }

    SC_CTOR(half_adder){
        SC_METHOD(prc_half_add);
        sensitive<<a<<b;
    }
};

SC_MODULE(testbench){
    sc_out<bool> a, b;
    sc_in<bool> sum, carry;

    void init()
    {
        cout << "sum\tcarry" << endl;
        for(int i{0};i<10;++i){
            a = 0;
            b= 1;
            wait(1, SC_NS);
            cout << sum <<"\t" << carry << endl;
        }
    }

    SC_CTOR(testbench)
    {
        SC_THREAD(init);
    }
};

int sc_main(int argc, char** argv)
{
    half_adder ha {"half_adder"};
    testbench tb {"tb"};
    sc_signal<bool> a, b, sum, carry;
    ha.a.bind(a);
    ha.b.bind(b);
    ha.sum.bind(sum);
    ha.carry.bind(carry);
    tb.a.bind(a);
    tb.b.bind(b);
    tb.sum.bind(sum);
    tb.carry.bind(carry);

    sc_core::sc_start();
    return 0;
}