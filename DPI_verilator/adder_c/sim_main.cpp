#include <memory>
#include "verilated.h"
#include "Vtrans.h"

using namespace std;

int main(int argc, char** argv)
{
    auto contextp {make_unique<VerilatedContext>()};
    contextp->commandArgs(argc, argv);
    auto top {make_unique<Vtrans>(contextp.get())};
    while(!contextp->gotFinish()){
        top->eval();
    }
    return 0;
}