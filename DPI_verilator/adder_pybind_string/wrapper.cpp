#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <dlfcn.h>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <sys/time.h>
#include "svdpi.h"

namespace py=pybind11;

std::unique_ptr<py::scoped_interpreter> guard = nullptr;
std::string res = "";

extern "C" __attribute__((visibility("default")))
 const char* gen_rand_arr(/* input */ uint32_t len)
{
        timeval t1, t2;
        gettimeofday(&t1, NULL);
        guard = std::unique_ptr<py::scoped_interpreter> {new py::scoped_interpreter()};

        auto np = py::module::import("numpy");

        // or change to be exec
        auto from_arr = np.attr("random")
        // 必须多分配一个
                        .attr("randint")(1, 127, len+1, "byte");
        from_arr.attr("__setitem__")(len, 0);

        res = from_arr.attr("tobytes")().cast<std::string>();

        gettimeofday(&t2, NULL);

        double timeuse  = (t2.tv_sec-t1.tv_sec) + (double)(t2.tv_usec-t1.tv_usec)/1000000.0;
        std::cout << "data transfer time used: "<< timeuse << "s" << std::endl;

        return res.c_str();
}