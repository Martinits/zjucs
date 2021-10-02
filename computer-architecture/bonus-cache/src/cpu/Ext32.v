
`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:12:28 05/04/2020 
// Design Name: 
// Module Name:    Ext32 
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
module Ext32(input [15:0] I,
				input Ext_sel,
				output [31:0] O
    );
	 assign O = Ext_sel ? {16'b0, I} : {{16{I[15]}},I} ;


endmodule
