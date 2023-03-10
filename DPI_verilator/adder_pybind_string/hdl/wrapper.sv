import "DPI-C" function string gen_rand_arr(input int unsigned len);

`timescale 1ns/1ps


module wrapper(
//input   clk_i,
//input   reset_i,
output  reg [7:0] res_o
);

// 最高不能超过十亿bit
parameter int LENGTH = 10000000; // byte

bit clk_i, reset_i;
bit [7:0] data_a[LENGTH], data_b[LENGTH]; 


initial begin
    string s = gen_rand_arr(LENGTH*2);
    for(int i = 0;i<LENGTH;i=i+1)begin
        data_a[i] = s[i*2];
        data_b[i] = s[i*2+1];
    end
end

reg [7:0] A_s;
reg [7:0] B_s;

always #1 clk_i = ~clk_i;

initial begin
    clk_i = 0;
    reset_i = 0;
end

bfm inst_bfm(
    .clk_i(clk_i),
    .reset_i(reset_i),
    .A_s(A_s),
    .B_s(B_s),
    .res_o(res_o)
);

int pointer = 0;

always @(posedge clk_i) begin
    if(reset_i)begin
        A_s <= 0;
        B_s <= 0;
    end
    else if(pointer < LENGTH) begin 
        A_s <= data_a[pointer];
        B_s <= data_b[pointer];
        pointer <= pointer + 1;
    end
end

always @(posedge clk_i) begin
    if(pointer == LENGTH-1)begin
        $display("%d + %d = ", A_s, B_s);
        #1 $display("%d ", res_o);
    end
    if(pointer==LENGTH) begin
        #2 $finish;
    end
end

initial begin
    $dumpfile("dump.vcd");
    $dumpvars;
end

endmodule