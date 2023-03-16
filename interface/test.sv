import tlm::*;

module test(
    
);
    parameter int LENGTH = 100000000;
    bit[7:0] arr [LENGTH];
    initial begin
        chandle ds = getDataSourceByName("base");
        get(ds, arr);
        put(ds, arr);

        $finish;
    end
endmodule