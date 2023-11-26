`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/13/2019 11:43:50 PM
// Design Name: 
// Module Name: PipeFtoD
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

module PipeFtoD(input logic[31:0] instr, PcPlus4F,
                input logic EN, clk, reset,		// StallD will be connected as this EN
                output logic[31:0] instrD, PcPlus4D);
    
    always_ff @(posedge clk, posedge reset)begin
        if (reset)begin
            instrD <= 0;
            PcPlus4D <= 0;
        end
        else if(EN)
            begin
            instrD<=instr;
            PcPlus4D<=PcPlus4F;
            end
        else begin
            instrD <= instrD;
            PcPlus4D <= PcPlus4D;
        end
    end
endmodule