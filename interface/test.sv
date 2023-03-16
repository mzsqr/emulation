import tlm::*;

module test(
    
);
    // 目前这个长度不能太大,可能是我电脑有问题
    parameter int LENGTH = 2000000;
    bit[7:0] arr [LENGTH];
    initial begin
        chandle ds = getDataSourceByName("base");
        get(ds, arr);
        put(ds, arr);

        $finish;
    end
endmodule