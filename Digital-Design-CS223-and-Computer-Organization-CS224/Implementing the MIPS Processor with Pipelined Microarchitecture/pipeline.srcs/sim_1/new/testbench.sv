`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/14/2019 12:13:01 AM
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

               
    logic clk_t, reset_t, memwrite, regwrite;
    logic[31:0] writedata, dataadr, instr, PCF, instrOut;
    toptop dut ( clk_t, reset_t, instr, instrOut, PCF, dataadr, writedata, memwrite, regwrite  );
    
    always
        begin
            clk_t = 1; #5; clk_t = 0; #5;
        end
    initial begin
        reset_t = 1; #10;
        reset_t = 0; 
    end
endmodule

