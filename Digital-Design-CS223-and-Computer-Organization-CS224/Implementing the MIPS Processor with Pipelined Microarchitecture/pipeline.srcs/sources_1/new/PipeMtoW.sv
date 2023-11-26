`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/13/2019 11:48:01 PM
// Design Name: 
// Module Name: PipeMtoW
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

// pipe from M to WB
module PipeMtoW(input logic clk, reset, RegWriteM, MemtoRegM,
                input logic[31:0] ReadDataM, ALUOutM,
                input logic[4:0] WriteRegM,
                    output logic RegWriteW, MemtoRegW,
                    output logic[31:0] ReadDataW, ALUOutW,
                    output logic[4:0] WriteRegW);

    always_ff @(posedge clk, posedge reset) begin
           //*************************************************************************
           // YOUR CODE HERE
           //*************************************************************************
        if ( reset ) begin
            ReadDataW <= 32'h00000000;
            ALUOutW <= 32'h00000000;
            WriteRegW <= 5'b00000;
            RegWriteW <= 0;
            MemtoRegW <= 0;
        end
        else begin
            ReadDataW <= ReadDataM;
            ALUOutW <= ALUOutM;
            WriteRegW <= WriteRegM;
            RegWriteW <= RegWriteM;
            MemtoRegW <= MemtoRegM;
        end	
    end
endmodule