// TODO: ADD cons
package tlm;
// 一方面需要设置上下文
import "DPI-C" context function void test();
import "DPI-C" function void transfer_arr(output bit [7:0] arr []);

export "DPI-C" function test_from_sv;

function void test_from_sv();
    $display("Function in sv: Hello");
endfunction


import "DPI-C" function chandle getDataSourceByName(input string name);
import "DPI-C" put = function void get(input chandle dataSouce, output bit[7:0] arr []);
import "DPI-C" get = function void put(input chandle dataSouce, input bit[7:0] arr[]);

endpackage
