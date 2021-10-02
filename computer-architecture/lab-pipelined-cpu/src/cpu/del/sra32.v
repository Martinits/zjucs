`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:09:25 05/05/2020 
// Design Name: 
// Module Name:    sra32 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module sra32(input [31:0] A, B,
					output [31:0] O
    );
	 assign O=(A>>B)|(32'hffffffff<<(32-B));
	 


endmodule
