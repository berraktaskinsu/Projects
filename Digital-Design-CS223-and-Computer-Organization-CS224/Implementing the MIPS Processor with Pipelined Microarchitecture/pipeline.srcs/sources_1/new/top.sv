`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/14/2019 12:07:59 AM
// Design Name: 
// Module Name: top
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


module top  (input  clk, clk_input, reset,
             output dp, 
             output [3:0] an,
             output [6:0] C,   
             output memwrite, regwrite
	         ) ;  
   logic [31:0] instrOut, instr, PCF;
   logic clk_pulse, reset_pulse;
   logic [31:0] writedata, dataadr;
   logic [3:0] enables, digit3, digit2, digit1, digit0;
    
   assign enables = 4'b1111;
   
   assign digit0 = writedata[7:4];
   assign digit1 = writedata[3:0];
   assign digit2 = dataadr[7:4];
   assign digit3 = dataadr[3:0];

   pulse_controller pcClock( clk, clk_input, reset_pulse, clk_pulse );
   pulse_controller pcReset( clk ,reset, 1'b0, reset_pulse );
   display_controller dc( clk, reset_pulse, enables, digit3, digit2, digit1, digit0, an, C, dp );
//    logic StallD, StallF;
//    logic[31:0] resultW;
//    mips mips (clk_pulse, reset_pulse, PCF, instr, dataadr, resultW, instrOut, writedata, StallD, StallF, memwrite, regwrite ); 
//    imem imem ( PCF[7:2], instr );  
   toptop toptop ( clk_pulse, reset_pulse, instr, instrOut, PCF, dataadr, writedata, memwrite, regwrite );

endmodule