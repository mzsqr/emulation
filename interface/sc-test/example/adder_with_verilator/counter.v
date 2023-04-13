module counter(
    input wire rst_n, clk,
    output reg [7:0] count
);

always @(posedge clk) begin
    if (!rst_n) begin
        count <= 8'b0;
    end 
    else begin
        count <= count +1;
    end
end

endmodule