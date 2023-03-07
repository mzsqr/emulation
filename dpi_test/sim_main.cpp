#include "Vrand_array.h"
#include "verilated.h"

#include <memory>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    auto contextp {make_unique<VerilatedContext>()};
    contextp->commandArgs(argc, argv);
    auto top {make_unique<Vrand_array>(contextp.get())};
    while(!contextp->gotFinish()){
        top->eval();
        contextp->timeInc(1000);
    }
    return 0;
}