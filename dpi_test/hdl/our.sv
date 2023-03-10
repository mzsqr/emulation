import rand_array::*;

`timescale 1ns/1ps
module our ();

parameter int LENGTH = 2000000;

bit clk_i, reset_i;
int index = 0; // 当前索引

always #1 clk_i = ~clk_i;

bit [7:0] a_arr[LENGTH], b_arr[LENGTH];

initial begin
    
    string s = get_rand_array(LENGTH*2);
    for(int i = 0;i<LENGTH;i=i+1)begin
        a_arr[i] = s[i*2];
        b_arr[i] = s[i*2+1];
    end
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
        a <= a_arr[index];
        b <= b_arr[index];
        index <= index + 1;
    end else if(index == LENGTH) begin
        $finish;
    end
end

always @(posedge clk_i) begin
    if(index == LENGTH-1) begin
        $display("%d %d", a, b);
        #1 $display("%d ", res);
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