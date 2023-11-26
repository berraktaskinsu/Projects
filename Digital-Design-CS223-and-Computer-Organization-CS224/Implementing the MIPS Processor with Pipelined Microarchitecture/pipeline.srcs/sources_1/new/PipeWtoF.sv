`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/13/2019 11:45:33 PM
// Design Name: 
// Module Name: PipeWtoF
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

module PipeWtoF(input logic[31:0] PC,
                input logic EN, clk, reset,		// StallF will be connected as this EN
                output logic[31:0] PCF);
    
    always_ff @(posedge clk, posedge reset)begin
        if (reset)
            PCF <= 0;
        else if(EN)
            begin
            PCF<=PC;
            end
        else 
            PCF <= PCF;
    end
endmodule
