`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/13/2019 11:47:14 PM
// Design Name: 
// Module Name: PipeEtoM
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

// pipe from E to M
module PipeEtoM(input logic clk, reset, RegWriteE, MemtoRegE, MemWriteE, BranchE, Zero,
                input logic[31:0] ALUOut,
                input logic [31:0] WriteDataE,
                input logic[4:0] WriteRegE,
                input logic[31:0] PCBranchE,
                    output logic RegWriteM, MemtoRegM, MemWriteM, BranchM, ZeroM,
                    output logic[31:0] ALUOutM,
                    output logic [31:0] WriteDataM,
                    output logic[4:0] WriteRegM,
                    output logic[31:0] PCBranchM);
    
    always_ff @(posedge clk, posedge reset) begin
        //***************************************************************************
        // YOUR CODE HERE
        //***************************************************************************
        if ( reset  ) begin
            ZeroM <= 0;
            ALUOutM <= 3'b000;
            WriteDataM <= 32'h00000000;
            WriteRegM <= 5'b00000;
            PCBranchM <= 32'h00000000;
            RegWriteM <= 0;
            MemtoRegM <= 0;
            MemWriteM <= 0;
            BranchM <= 0;
        end
        else begin
            ZeroM <= Zero;
            ALUOutM <= ALUOut;
            WriteDataM <= WriteDataE;
            WriteRegM <= WriteRegE;
            PCBranchM <= PCBranchE;
            RegWriteM <= RegWriteE;
            MemtoRegM <= MemtoRegE;
            MemWriteM <= MemWriteE;
            BranchM <= BranchE;
         end
    end
endmodule

