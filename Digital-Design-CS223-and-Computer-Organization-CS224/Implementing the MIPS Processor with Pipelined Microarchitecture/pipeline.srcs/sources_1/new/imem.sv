`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/13/2019 11:56:24 PM
// Design Name: 
// Module Name: imem
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
module imem ( input logic [5:0] addr, output logic [31:0] instr);

// imem is modeled as a lookup table, a stored-program byte-addressable ROM
	always_comb
	   case ({addr,2'b00})		   	// word-aligned fetch

//***************************************************************************
//	Here, you should paste the test cases that are given to you in lab document.
//  	You can write your own test cases and try it as well.
//	Below is the program from the single-cycle lab.
//***************************************************************************
//
//		address		instruction
////		-------		-----------
//		8'h00: instr = 32'h20080005;
//        8'h04: instr = 32'h20090006;
//        8'h08: instr = 32'h20040001;
//        8'h0c: instr = 32'h20050002;
//        8'h10: instr = 32'had280000;
//        8'h14: instr = 32'h8d090001;
//        8'h18: instr = 32'h01245020;
//        8'h1c: instr = 32'h01255022;
        8'h00: instr = 32'h20080007;
        8'h04: instr = 32'h20090005;
        8'h08: instr = 32'h200a0000;
        8'h0c: instr = 32'h210b0003;
        8'h10: instr = 32'h01095020;
        8'h14: instr = 32'h01095025;
        8'h18: instr = 32'h01095024;
        8'h1c: instr = 32'h01095022;
        8'h20: instr = 32'h0109502a;
        8'h24: instr = 32'had280002;
        8'h28: instr = 32'h8d090000;
        8'h2c: instr = 32'h1100fff5;
        8'h30: instr = 32'h200a000a;
        8'h34: instr = 32'h2009000c;
//8'h00: instr = 32'h20080005;
//8'h04: instr = 32'h21090006;
//8'h08: instr = 32'h01285020;

	
		// CODE: paste the test cases
	     default:  instr = {32{1'bx}};	// unknown address
	   endcase
endmodule