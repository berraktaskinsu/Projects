`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/31/2019 10:00:18 PM
// Design Name: 
// Module Name: testbench
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
module testbench();
    
    logic clk, reset;
    logic[31:0] writedata, dataadr, instr, pc;
    logic memwrite;
    top dut( clk, reset, writedata, dataadr, memwrite, instr, pc );
    
    always
        begin
            clk = 1; #5; clk = 0; #5;
        end
    initial begin
        reset = 1; #10;
        reset = 0; 
    end
endmodule
