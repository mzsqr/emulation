import rand_array::*;

`timescale 1ns/1ps
module our ();

parameter int LENGTH = 200000;

bit clk_i, reset_i;
int index = 0; // 当前索引

always #1 clk_i = ~clk_i;

// LENGTH 个随机数
RandArray a_arr = new(LENGTH);
RandArray b_arr = new(LENGTH);

initial begin
    clk_i = 0;
    reset_i = 1;
end

reg [7:0] a, b;
wire [7:0] res;

always @(posedge clk_i)
begin
    if(!reset_i) begin
        a <= 8'b0;
        b <= 8'b0;
        
    end
    else if(index < LENGTH) begin
        a <= a_arr.get(index);
        b <= b_arr.get(index);
        index <= index + 1;
    end else if(index == LENGTH) begin
        $finish;
    end
end

adder adder_inst(
    .clk_i(clk_i),
    .reset_i(reset_i),
    .a(a),
    .b(b),
    .res(res)
);

initial begin
    $dumpfile("dump.vcd");
    $dumpvars;
end

endmodule