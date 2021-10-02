`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:42:09 10/28/2020 
// Design Name: 
// Module Name:    MEM_WB 
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
module MEM_WB(input [31:0] pc_4, mem_data, alu_res, lui32,
					input [32:0] ins,
					input [35:0] ctrl_sig,
					input clk, rst, we, zero,
					output reg [31:0] pc_4_out, mem_data_out, alu_res_out, lui32_out,
					output reg [32:0] ins_out,
					output reg [35:0] ctrl_sig_out
    );
	`define regs_MEM_WB {pc_4_out, ins_out, ctrl_sig_out, mem_data_out, alu_res_out, lui32_out}

	always@(posedge clk or posedge rst) begin
		if(rst) `regs_MEM_WB <=0;
		else if(we) `regs_MEM_WB <= zero ? 0 : {pc_4, ins, ctrl_sig, mem_data, alu_res, lui32};
	end

endmodule
