`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/13/2019 11:46:45 PM
// Design Name: 
// Module Name: PipeDtoE
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

module PipeDtoE(input logic clr, clk, reset, RegWriteD, MemtoRegD, MemWriteD,
                input logic[2:0] AluControlD,
                input logic AluSrcD, RegDstD, BranchD,
                input logic[31:0] RD1D, RD2D,
                input logic[4:0] RsD, RtD, RdD,
                input logic[31:0] SignImmD,
                input logic[31:0] PCPlus4D,
                    output logic RegWriteE, MemtoRegE, MemWriteE,
                    output logic[2:0] AluControlE,
                    output logic AluSrcE, RegDstE, BranchE,
                    output logic[31:0] RD1E, RD2E,
                    output logic[4:0] RsE, RtE, RdE,
                    output logic[31:0] SignImmE,
                    output logic[31:0] PCPlus4E);

    always_ff @(posedge clk, posedge reset)begin
        //***************************************************************************
        // YOUR CODE HERE
        //***************************************************************************
        if ( reset || clr ) begin
            RD1E <= 0;
            RD2E <= 0;
            RsE <= 0;
            RtE <= 0;
            RdE <= 0;
            SignImmE <= 0;
            PCPlus4E <= 0;
            RegWriteE <= 0;
            MemtoRegE <= 0;
            MemWriteE <= 0;
            AluControlE <= 3'b000;
            AluSrcE <= 0;
            RegDstE <= 0;
            BranchE <= 0;
        end	
        else begin
            RD1E <= RD1D;
            RD2E <= RD2D;
            RsE <= RsD;
            RtE <= RtD;
            RdE <= RdD;
            SignImmE <= SignImmD;
            PCPlus4E <= PCPlus4D;
            RegWriteE <= RegWriteD;
            MemtoRegE <= MemtoRegD;
            MemWriteE <= MemWriteD;
            AluControlE <= AluControlD;
            AluSrcE <= AluSrcD;
            RegDstE <= RegDstD;
            BranchE <= BranchD;
         end
    end
endmodule

