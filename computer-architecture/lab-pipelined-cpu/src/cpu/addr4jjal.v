`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:19:39 11/03/2020 
// Design Name: 
// Module Name:    addr4jjal 
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
module addr4jjal(input [31:0] pc_4, ins,
						output [31:0] dest
    );
	wire [31:0] pc;
	assign pc = pc_4 - 4;
	assign dest = {pc[31:28], ins[25:0], 2'b0};

endmodule
