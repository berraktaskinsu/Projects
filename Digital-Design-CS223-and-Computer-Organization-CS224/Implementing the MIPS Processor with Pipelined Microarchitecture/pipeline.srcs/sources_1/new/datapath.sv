`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/13/2019 11:53:09 PM
// Design Name: 
// Module Name: datapath
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

module datapath (input  logic clk, reset,
		         input logic [31:0] PCF, instr,	
		         input logic RegWriteD, MemtoRegD, MemWriteD,
		         input logic [2:0] AluControlD,
		         input logic AluSrcD, RegDstD, BranchD,
		             output logic PCSrcM, StallD, StallF,
		             output logic[31:0] PCBranchM, PCPlus4F, instrD, ALUOutM, ResultW, WriteDataM,
		             output logic MemWriteM, RegWriteW ); 

	// ********************************************************************
	// Here, define the wires (logics) that are needed inside this pipelined datapath module
    // You are given the wires connecting the Hazard Unit.
    // Notice that StallD and StallF are given as output for debugging
	// ********************************************************************

	logic ForwardAD, ForwardBD,  FlushE;
	logic [1:0] ForwardAE, ForwardBE;		
	// Add necessary wires (logics).
	logic [31:0] PCPlus4D, RD1D, RD2D, SignImmD, PCPlus4E, RD1E, RD2E, SignImmE;
	logic [4:0] RsD, RtD, RdD, RsE, RtE, RdE, WriteRegE, WriteRegM, WriteRegW;
	logic RegWriteE, MemtoRegE, MemWriteE, RegWriteM, MemtoRegM, MemtoRegW;
	logic [2:0] AluControlE;
	logic AluSrcE, RegDstE, BranchE, BranchM;
	logic [31:0] PCBranchE, WriteDataE, ReadDataM, ReadDataW, SrcAE, SrcBE, ALUOut, ALUOutW, resShifter;
	logic Zero, ZeroM;
	//logic [31:0] instr;

	




	// ********************************************************************
	// Instantiate the required modules below in the order of the datapath flow.
	// ********************************************************************
	
	assign PCSrcM = BranchM & ZeroM;
	assign RsD = 	instrD[25:21];	
    assign RtD = 	instrD[20:16];	
    assign RdD = 	instrD[15:11];	
    //assign WriteDataE = 	32'd0; 
    
	// Below, PipeFtoD and regfile instantiations are given
    // Add other instantiations
    // BE CAREFUL ABOUT THE ORDER OF PARAMETERS!
	
	adder		addr1 ( PCF, 32'd4, PCPlus4F );

	PipeFtoD	ftd ( instr, PCPlus4F, ~StallD, clk, reset, instrD, PCPlus4D ); 

	regfile		rf ( clk, RegWriteW, instrD[25:21], instrD[20:16], WriteRegW, ResultW, RD1D, RD2D );     

	signext		se ( instrD[15:0], SignImmD );
	
	PipeDtoE	dte ( FlushE, clk, reset, RegWriteD, MemtoRegD, MemWriteD, AluControlD, AluSrcD, RegDstD, BranchD, RD1D, RD2D, RsD, RtD, RdD, SignImmD, PCPlus4D, 
RegWriteE, MemtoRegE, MemWriteE, AluControlE, AluSrcE, RegDstE, BranchE, RD1E, RD2E,  RsE, RtE, RdE, SignImmE, PCPlus4E );

	mux2 #(5)	mux2 ( RtE, RdE, RegDstE, WriteRegE );

	sl2		sl21 ( SignImmE, resShifter );
	
	adder		addr2 ( resShifter, PCPlus4E, PCBranchE );	

	mux4 #(32)	mux3 ( RD1E, ResultW, ALUOutM, ALUOutM, ForwardAE, SrcAE );

	mux4 #(32) 	mux4 ( RD2E, ResultW, ALUOutM, ALUOutM, ForwardBE, WriteDataE );

	mux2 #(32)	mux5 ( WriteDataE, SignImmE, AluSrcE, SrcBE );

	alu		alu1 ( SrcAE, SrcBE, AluControlE, ALUOut, Zero, reset );

	PipeEtoM	etm ( clk, reset, RegWriteE, MemtoRegE, MemWriteE, BranchE, Zero, ALUOut, WriteDataE, WriteRegE, PCBranchE, RegWriteM, MemtoRegM, MemWriteM, BranchM, ZeroM, ALUOutM, WriteDataM, WriteRegM, PCBranchM);

	//and 		and1 ( BranchM, ZeroM, PCSrcM );

	dmem		dmem1 ( clk, MemWriteM, ALUOutM, WriteDataM, ReadDataM );

	PipeMtoW	mtw ( clk, reset, RegWriteM, MemtoRegM, ReadDataM, ALUOutM, WriteRegM, RegWriteW, MemtoRegW, ReadDataW, ALUOutW, WriteRegW);
	
	mux2 #(32) 	mux6 ( ALUOutW, ReadDataW, MemtoRegW, ResultW );

	HazardUnit	hu (  RegWriteW, WriteRegW, RegWriteM, MemtoRegM, WriteRegM, RegWriteE, MemtoRegE, RsE, RtE, RsD, RtD, ForwardAE, ForwardBE, FlushE, StallD, StallF );

	
endmodule

