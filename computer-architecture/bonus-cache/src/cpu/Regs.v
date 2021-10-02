`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:21:44 05/04/2020 
// Design Name: 
// Module Name:    Regs 
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
module Regs(input wire clk, rst, we,
				input wire [4:0] R_addr_A, R_addr_B, W_addr,
				input wire [31:0] W_data,
				output wire [31:0] R_data_A, R_data_B,
				input [4:0] debug_reg_addr,
				output [31:0] debug_reg_data
    );
	reg [31:0] regs[1:31];
	integer i;
	assign R_data_A=(R_addr_A==0)?0:((W_addr==R_addr_A)?W_data:regs[R_addr_A]);
	assign R_data_B=(R_addr_B==0)?0:((W_addr==R_addr_B)?W_data:regs[R_addr_B]);
	always @(posedge clk or posedge rst) begin
		if(rst) for(i=1;i<32;i=i+1) regs[i]<=0;
		else if(W_addr&&we)regs[W_addr]<=W_data;
	end
	assign debug_reg_data = (debug_reg_addr ? regs[debug_reg_addr] : 0);
	
endmodule
