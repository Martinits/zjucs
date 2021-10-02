`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:06:46 10/27/2020 
// Design Name: 
// Module Name:    IF_ID 
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
module IF_ID(input [31:0] pc_4, ins,
				input clk, rst, we, zero,
				output reg [31:0] pc_4_out,
				output reg [32:0] ins_out
    );

	`define regs_IF_ID {pc_4_out, ins_out}
	always@(posedge clk or posedge rst)begin
		if(rst) `regs_IF_ID <=0;
		else if(we) `regs_IF_ID <= zero ? 0 : {pc_4, 1'b1, ins};
	end

endmodule
