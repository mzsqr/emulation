module counter_8bit(
  input clk, // 时钟信号
  input rst, // 复位信号
  output reg [7:0] count // 输出计数值
);

  always @(posedge clk or posedge rst) begin
    if (rst) begin
      count <= 8'b0; // 复位计数器
    end
    else begin
      count <= count + 1; // 计数器加1
    end
  end

endmodule