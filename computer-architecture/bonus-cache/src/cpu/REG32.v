`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:28:53 06/18/2020 
// Design Name: 
// Module Name:    REG32 
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
module REG32(input clk,
				input [31:0] Di,
				input rst,
				input EN,
				output [31:0] Do
						);
	reg [31:0] Q;
	assign Do = Q;
	always @ (posedge clk or posedge rst)begin
		if(rst) Q <= 0;
		else if(EN) Q <= Di;
		else Q <= Q;
	end
endmodule
