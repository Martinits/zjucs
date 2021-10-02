`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:12:56 11/03/2020 
// Design Name: 
// Module Name:    add4beqbne 
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
module add4beqbne(input [31:0] pc_4,
						input [15:0] offset,
						output [31:0] dest
    );
	assign dest = pc_4 + {{14{offset[15]}}, offset, 2'b0};

endmodule
