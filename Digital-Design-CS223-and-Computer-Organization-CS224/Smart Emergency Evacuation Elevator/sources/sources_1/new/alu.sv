`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/31/2019 09:51:05 PM
// Design Name: 
// Module Name: alu
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


module alu(input  logic [31:0] a, b, 
           input  logic [2:0]  alucont, 
           output logic [31:0] aluRes,
           output logic zero);

	logic [31:0] diff;
	assign diff = a - b;
	always_comb
	case (alucont)
		3'b000: aluRes = a & b;
		3'b001: aluRes = a | b;
		3'b010: aluRes = a + b;
		3'b110: aluRes = diff;
		3'b111: aluRes = diff[31];
	endcase
	assign zero = aluRes ? 0 : 1;

  // details of the model need to be 
  // filled in by you, the designer !
endmodule