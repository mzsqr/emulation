#include "tlm.h"
#include "svdpi.h"

#include <random>

using namespace std;

tlm::DataSourceMgr* tlm::DataSourceMgr::mgr {nullptr};

namespace tlm {
    // 另一方面需要设置函数所在作用域
    void test()
    {
        svSetScope(svGetScopeFromName("TOP.tlm"));
        std::cout << "Funciont in CPP: " << __func__ << ", Hello World" << std::endl;
        test_from_sv();
    }

    void data_gen(void* ptr, size_t len)
    {
        auto arr = reinterpret_cast<uint8_t*>(ptr);
        random_device seeder;
        const auto seed {seeder.entropy()?seeder():time(nullptr)};
        mt19937 engine {static_cast<mt19937::result_type>(seed)};
        uniform_int_distribution<int> dist {0, 127};
        for(auto it{arr}; it!=arr+len;++it){
            *it = dist(engine);
        }
    }

    void transfer_arr(svOpenArrayHandle arr)
    {
        size_t len = svSize(arr, 1);
        data_gen(svGetArrayPtr(arr), len);
    }

    DataSourceMgr* DataSourceMgr::createMgr()
    {
        if(!mgr){
            mgr = new DataSourceMgr;
        }
        return mgr;
    }

    DataSourceMgr* DataSourceMgr::getMgr()
    {
        if(!mgr){
            throw logic_error {"You should initial a DataSourceMgr first."};
        }
        return mgr;
    }

    DataSource* DataSourceMgr::get(const string& name)
    {
        if(ds.find(name)==end(ds)){
            throw invalid_argument {"There are not data source named " + name};
        }
        return ds[name].get();
    }

    void DataSourceMgr::add(const string& name, unique_ptr<DataSource> dataSource)
    {
        ds[name] = move(dataSource);
    }

    void* getDataSourceByName(const char* str)
    {
        auto mgr = DataSourceMgr::getMgr();
        return reinterpret_cast<void*>(mgr->get(str));
    }

    //TODO: help method for process sv type

    void put(void* dataSource, svOpenArrayHandle arr)
    {
        auto ds = reinterpret_cast<DataSource*>(dataSource);
        size_t len = svSizeOfArray(arr);
        uint8_t* ptr = reinterpret_cast<uint8_t*>(svGetArrayPtr(arr));
        ds->put(ptr, len);
    }

    void get(void* dataSource, const svOpenArrayHandle arr)
    {
        auto ds = reinterpret_cast<DataSource*>(dataSource);
        size_t len = svSizeOfArray(arr);
        const uint8_t* ptr = reinterpret_cast<uint8_t*>(svGetArrayPtr(arr));
        ds->get(ptr, len);
    }
}