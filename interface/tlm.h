// C++17
#ifndef TLM_H
#define TLM_H

// This header contains data type and function definition for DPI
#include "svdpi.h"

#include <iostream>
#include <cstddef>
#include <memory>
#include <unordered_map>

// all definition is under tlm namespace
namespace tlm
{
    // definition exported to SystemVerilog
    extern "C" {
        // some test function
        void test();
        void transfer_arr(/** output */svOpenArrayHandle arr);
        void test_from_sv();

        // wrapper function for called by systemverilog

        // void* will be cast to a DataSource
        void* getDataSourceByName(const char* str);

        void put(void* dataSource, svOpenArrayHandle arr);
        void get(void* dataSource, const svOpenArrayHandle arr);
 
    }
    // tlm methods 
    /**
     * put
     * get
     * peek
     * try_put 
     * try_get
     * try_peek
     * can_put
     * can_get
     * can_peek
     * transport
     * nb_transport
     * write
     * put_req 
     * put_response
     * get_next_item
     * item_done
     * get_response
    */
    // 抽象类，数据源类
    class DataSource
    {
    public:
        DataSource(/* args */) {/** do nothing */};
        virtual ~DataSource() {/** do nothing */};

        // put data to the port/vector
        // in sv, you will call get to get the data
        virtual void put(uint8_t* data, size_t len) {/** do nothing */};

        // get data from the port/vector
        virtual void get(const uint8_t* data, size_t len) {/** do nothing*/};

        // peek data from the port/vector
        // if you instruct buffering the data
        // TODO: peek

    };

    // manage the data source
    class DataSourceMgr 
    {
    public:
        static DataSourceMgr* createMgr();

        // throws:
        // logic_error if you foget create a mgr first
        static DataSourceMgr* getMgr();

        // throws:
        // invalid_argument when there are not datasource named `name`
        DataSource* get(const std::string& name);

        // you should create data source by yourself, using unique_ptr to manage memory
        // using std::move to pass the argument
        // if you have added a data source with the same name, the new will override previous
        void add(const std::string& name, std::unique_ptr<DataSource> dataSource);
    private:
        // cannot create it youself
        DataSourceMgr(){
            //now do nothing
        } 
        static DataSourceMgr* mgr;
        std::unordered_map<std::string, std::unique_ptr<DataSource>> ds;
    };
        
}

#endif // !TLM_H