`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/17/2019 02:02:30 PM
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


module toptop( input logic clk_pulse, reset_pulse,
               output logic [31:0] instr, instrOut, PCF, dataadr, writedata,
               output logic memwrite, regwrite  );
               
 
    logic StallD, StallF;
    logic[31:0] resultW;
    mips mips (clk_pulse, reset_pulse, PCF, instr, dataadr, resultW, instrOut, writedata, StallD, StallF, memwrite, regwrite ); 
    imem imem ( PCF[7:2], instr );  
    
endmodule
