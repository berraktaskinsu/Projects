`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/03/2019 10:10:12 AM
// Design Name: 
// Module Name: toptop
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


module toptop(
                input clk, clk_input, reset_input,
                output memwrite, dp,
                output [3:0]an,
                output [6:0]C
                );
    
    logic clear = 0;
    logic [31:0] writedata, dataadr, pc, instr;
    logic [3:0] enables, digit3, digit2, digit1, digit0;

    assign enables = 4'b1111;
    
    assign digit0 = dataadr[3:0];
    assign digit1 = writedata[3:0];
    assign digit2 = pc[7:4];
    assign digit3 = pc[3:0];
    
    reg clk_pulse, reset_pulse;
    //top top( clk_pulse, reset_input, writedata, dataadr, memwrite, instr, pc );
    pulse_controller pcClock( clk, clk_input, reset_pulse, clk_pulse );
    pulse_controller pcReset( clk ,reset_input, clear, reset_pulse );
    display_controller dc( clk_pulse, reset_pulse, enables, digit3, digit2, digit1, digit0, an, C, dp );
    
    
    
    logic [31:0] readdata;    

   // instantiate processor and memories  
   mips mips (clk_pulse, reset_input, pc, instr, memwrite, dataadr, writedata, readdata);  
   imem imem (pc[7:2], instr);  
   dmem dmem (clk_pulse, memwrite, dataadr, writedata, readdata);
endmodule
