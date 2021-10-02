`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:00:20 05/04/2020 
// Design Name: 
// Module Name:    MUX_add_sub 
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
module MUX_add_sub(input S,
						 output [31:0] O
    );
	assign O=(S)?32'hffffffff:32'h00000000;

endmodule
