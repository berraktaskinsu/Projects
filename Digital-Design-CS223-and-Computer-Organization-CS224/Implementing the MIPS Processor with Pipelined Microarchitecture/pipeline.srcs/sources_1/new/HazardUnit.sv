`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/13/2019 11:53:59 PM
// Design Name: 
// Module Name: HazardUnit
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

module HazardUnit( input logic RegWriteW,
                input logic [4:0] WriteRegW,
                input logic RegWriteM,MemToRegM,
                input logic [4:0] WriteRegM,
                input logic RegWriteE,MemtoRegE,
                input logic [4:0] rsE,rtE,
                input logic [4:0] rsD,rtD,
                output logic [1:0] ForwardAE,ForwardBE,
                output logic FlushE,StallD,StallF);
   
    logic lwstall;
    always_comb begin
    	lwstall <= ( ( rsD == rtE ) || ( rtD == rtE ) ) & MemtoRegE;
        StallF <= lwstall;
        StallD <= lwstall;
        FlushE <= lwstall;
    
        if ( ( rsE != 5'b00000 ) & ( rsE == WriteRegM ) & RegWriteM )       ForwardAE <= 2'b10; 
        else if ( ( rsE != 5'b00000 ) & ( rsE == WriteRegW ) & RegWriteW )  ForwardAE <= 2'b01;  	
        else                                                                ForwardAE <= 2'b00;
        
        if ( ( rtE != 5'b00000 ) & ( rtE == WriteRegM ) & RegWriteM )       ForwardBE <= 2'b10; 
        else if ( ( rtE != 5'b00000 ) & ( rtE == WriteRegW ) & RegWriteW )  ForwardBE <= 2'b01;  	
        else                                                                ForwardBE <= 2'b00;

        // ********************************************************************
        // Here, write equations for the Hazard Logic.
        // If you have troubles, please study pages ~420-430 in your book.
        // ********************************************************************
    
    end

endmodule