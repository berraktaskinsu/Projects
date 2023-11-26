`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/13/2019 11:54:51 PM
// Design Name: 
// Module Name: mips
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

module mips (input  logic        clk, reset,
             output logic[31:0]  PCF,
             input  logic[31:0]  instr,
             output logic[31:0]  aluout, resultW,
             output logic[31:0]  instrOut, WriteDataM,
             output logic StallD, StallF,
             output logic MemWriteM, RegWriteW );

    // ********************************************************************
    // You can change the logics below but if you didn't change the signitures of 
    // above modules you will need these.
    // ********************************************************************

    logic memtoreg, zero, alusrc, regdst, regwrite, jump, PCSrcM, branch, memwrite;
    logic [31:0] PCPlus4F, PCm, PCBranchM, instrD;
    logic [2:0] alucontrol;
    assign instrOut = instrD;
    
    // ********************************************************************
    // Below, instantiate a controller and a datapath with their new (if modified) 
    // signatures and corresponding connections.
    // Also, you might want to instantiate PipeWtoF and pcsrcmux here.
    // Note that this is not the only solution.
    // You can do it in your way as long as it works.
    // ********************************************************************
    mux2 #(32)	mux1 ( PCPlus4F, PCBranchM, PCSrcM, PCm );

    PipeWtoF	wtf ( PCm, ~StallF, clk, reset, PCF);
    
    datapath 	dp ( clk, reset, PCF, instr, regwrite, memtoreg, memwrite, alucontrol, alusrc, regdst, branch, PCSrcM, StallD, StallF, PCBranchM, PCPlus4F, instrD, aluout, resultW, WriteDataM, MemWriteM, RegWriteW ); 

    controller 	c ( instr[31:26], instr[5:0], memtoreg, memwrite, alusrc, regdst, regwrite, jump, alucontrol, branch);

endmodule