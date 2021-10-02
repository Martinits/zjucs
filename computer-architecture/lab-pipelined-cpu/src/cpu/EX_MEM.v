`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:41:59 10/28/2020 
// Design Name: 
// Module Name:    EX_MEM
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
module EX_MEM(input [31:0] pc_4, alu_res, sw_data, lui32,
					input [32:0] ins,
					input [35:0] ctrl_sig,
					input clk, rst, we, zero,
					output reg [31:0] pc_4_out,  alu_res_out, sw_data_out, lui32_out,
					output reg [32:0] ins_out,
					output reg [35:0] ctrl_sig_out
    );
	`define regs_EX_MEM {pc_4_out, ins_out, ctrl_sig_out, alu_res_out, sw_data_out, lui32_out}
	
	always@(posedge clk or posedge rst) begin
		if(rst) `regs_EX_MEM <=0;
		else if(we) `regs_EX_MEM <= zero ? 0 : {pc_4, ins, ctrl_sig, alu_res, sw_data, lui32};
	end

endmodule
