#include "verilated.h"
#include "verilated_dpi.h"
#include "Vtlm.h"
#include "tlm.h"

#include <memory>

using namespace std;

class MyDataSource: public tlm::DataSource
{
public:
    void put(uint8_t* data, size_t len)override
    {
        cout << "array size: " << len << endl;
        for(auto it {data};it<data+len;++it){
            *it = 10;
        }
    }

    void get(const uint8_t* data, size_t len)override
    {
        cout << "array size: "<<len<<endl;
        cout << (int)*(data+len-1) << endl;
        cout << endl;
    }
};

int main(int argc, const char** argv) {
    // init you mgr here or sv
    auto mgr = tlm::DataSourceMgr::createMgr();
    mgr->add("base", make_unique<MyDataSource>());

    auto contextp {make_unique<VerilatedContext>()};
    contextp->commandArgs(argc, argv);
    auto top {make_unique<Vtlm>(contextp.get())};
    while(!contextp->gotFinish()){top->eval();}

    return 0;
}