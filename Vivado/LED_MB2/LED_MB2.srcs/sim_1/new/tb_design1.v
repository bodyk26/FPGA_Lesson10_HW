`timescale 1ns / 1ps

module tb_design_1;

localparam MS = 1000;           // 1 ms of firmware time with SIM_FAST
localparam RST_ACTIVE_LOW = 1;  // POLARITY of reset_rtl_0 in block design

reg clk = 0;
always #5 clk = ~clk;           // 100 MHz, must match clk_wiz output

reg rst = 1;
reg  [3:0] btn = 0;
wire [3:0] BTN_tri_io = btn;
wire [3:0] LED_tri_io;

design_1_wrapper dut (
    .diff_clock_rtl_0_clk_p(1'b0),
    .diff_clock_rtl_0_clk_n(1'b1),
    .reset_rtl_0(RST_ACTIVE_LOW ? ~rst : rst),
    .BTN_tri_io(BTN_tri_io),
    .LED_tri_io(LED_tri_io)
);

initial begin
    force dut.design_1_i.clk_wiz_1.clk_out1 = clk;
    force dut.design_1_i.clk_wiz_1.locked   = 1'b1;
    #200 rst = 0;
end

always @(LED_tri_io)
    $display("%0d ms  LED = %b", $time / MS, LED_tri_io);

task press(input integer b);
begin
    @(LED_tri_io);
    #(5*MS)   btn[b] = 1;
    #(120*MS) btn[b] = 0;
    #(60*MS);
end
endtask

initial begin
    #(1000*MS);
    $display("DIR");    press(1);           #(1000*MS);
    $display("FASTER"); press(2); press(2); #(1000*MS);
    $display("SLOWER"); press(3);           #(1000*MS);
    $display("PAUSE");  press(0);           #(1000*MS);
    $display("RESUME"); btn[0] = 1; #(120*MS) btn[0] = 0;
    #(1000*MS);
    $finish;
end

endmodule