`timescale 1ns/1ps
module adder(
    input wire clk_i,
    input wire reset_i,
    input wire [7:0] a,
    input wire [7:0] b,
    output wire [7:0] res
);

    reg [7:0] A, B;
    always @(posedge clk_i) begin
        if(~reset_i) begin
            A <= 8'b0;
            B <= 8'b0;
        end
        else begin
            A <= a;
            B <= b;
        end
      
    end

    assign res = A+B;

endmodule