`timescale 1ps/1ps

module wrapper (
    
);

parameter PACKAGE_WIDTH=1600;
// 每个时钟向下传递32bit
parameter NUM=50;

bit clk_i, reset_i;
int clk_num = 0;
reg [PACKAGE_WIDTH-1:0] data;

int num = 0;
reg xmit_en = 0;

always #5 clk_i = ~clk_i;

initial begin
    clk_i = 0;
    reset_i = 1;    
end

// Width of S_AXI data bus
parameter integer C_S_AXI_DATA_WIDTH	= 32;
// Width of S_AXI address bus
parameter integer C_S_AXI_ADDR_WIDTH	= 4;
		
// AXI4Stream sink: Data Width
parameter integer C_S_AXIS_TDATA_WIDTH	= 32;
		
// Width of S_AXIS address bus. The slave accepts the read and write addresses of width C_M_AXIS_TDATA_WIDTH.
parameter integer C_M_AXIS_TDATA_WIDTH	= 32;
// Start count is the number of clock cycles the master will wait before initiating/issuing any transaction.
parameter integer C_M_START_COUNT	= 1;

// AXI4Stream slave
wire s_tready;
reg [C_S_AXIS_TDATA_WIDTH-1:0]s_tdata;
wire s_tlast, s_tvalid;
reg s_tlast_delay, s_tvalid_delay;
wire write_en;

// AXI4Stream master
wire m_tvalid;
wire [C_S_AXIS_TDATA_WIDTH-1:0] m_tdata;
wire [C_S_AXIS_TDATA_WIDTH/8-1:0] m_tstrb;
wire m_tlast;
reg m_tready;

// 注意复位信号
bfm  #(
    .C_S_AXI_ADDR_WIDTH(C_S_AXI_ADDR_WIDTH),
    .C_S_AXI_DATA_WIDTH(C_S_AXI_DATA_WIDTH),
    .C_S_AXIS_TDATA_WIDTH(C_S_AXIS_TDATA_WIDTH),
    .C_M_AXIS_TDATA_WIDTH(C_S_AXIS_TDATA_WIDTH),
    .C_M_START_COUNT(C_M_START_COUNT)
)inst_bfm
(
    .S_AXIS_ACLK(clk_i),
    .S_AXIS_ARESETN(~reset_i),
    .S_AXIS_TREADY(s_tready),
    .S_AXIS_TDATA(s_tdata),
    .S_AXIS_TSTRB({(C_S_AXIS_TDATA_WIDTH/8){1'b1}}),
    .S_AXIS_TLAST(s_tlast),
    .S_AXIS_TVALID(s_tvalid),

    .M_AXIS_ACLK(clk_i),
    .M_AXIS_ARESETN(~reset_i),
    .M_AXIS_TVALID(m_tvalid),
    .M_AXIS_TDATA(m_tdata),
    .M_AXIS_TSTRB(m_tstrb),
    .M_AXIS_TLAST(m_tlast),
    .M_AXIS_TREADY(m_tready)
);

assign write_en = s_tvalid && s_tready && xmit_en;

// s_tdata
always @( posedge clk_i )
begin
    if(reset_i)
    begin
        s_tdata <= 0;
        num <= 0;
    end
    else begin
        if(write_en) begin
            s_tdata <= data[C_S_AXI_DATA_WIDTH*num 
            +: C_S_AXIS_TDATA_WIDTH];
            num <= num + 1;
        end
        if(num >= NUM) begin
            num <= 0;
            xmit_en <= xmit_en-1;
        end
    end 
end

assign s_tlast = xmit_en && num==NUM-1;
assign s_valid = xmit_en && num < NUM;

// delay one cycle
always @( posedge clk_i )
begin
    if(reset_i) begin
        s_tlast_delay <= 0;
        s_tvalid_delay <= 0;
    end
    else begin
        s_tlast_delay <= s_tlast;
        s_tvalid_delay <= s_tvalid;
    end
end

initial begin
    $dumpfile("dump.vcd");
    $dumpvars;
end
    
endmodule