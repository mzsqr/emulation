`ifndef PYSV_RAND_ARRAY
`define PYSV_RAND_ARRAY
`timescale 1ns/1ps
package rand_array;
import "DPI-C" function string get_rand_array(input int unsigned len);
import "DPI-C" function void pysv_finalize();
endpackage
`endif // PYSV_RAND_ARRAY
