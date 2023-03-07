`ifndef PYSV_RAND_ARRAY
`define PYSV_RAND_ARRAY
/* verilator lint_off TIMESCALEMOD */
package rand_array;
import "DPI-C" function chandle RandArray_pysv_init(input int unsigned len);
import "DPI-C" function void RandArray_destroy(input chandle self);
import "DPI-C" function byte unsigned RandArray_get(input chandle self,
                                                    input int unsigned i);
import "DPI-C" function int unsigned RandArray_len(input chandle self);
import "DPI-C" function void pysv_finalize();
class PySVObject;
chandle pysv_ptr;
endclass
class RandArray extends PySVObject;
  function new(input int unsigned len);
    pysv_ptr = RandArray_pysv_init(len);
  endfunction
  function void destroy();
    RandArray_destroy(pysv_ptr);
  endfunction
  function byte unsigned get(input int unsigned i);
    return RandArray_get(pysv_ptr, i);
  endfunction
  function int unsigned len();
    return RandArray_len(pysv_ptr);
  endfunction
endclass
endpackage
`endif // PYSV_RAND_ARRAY
