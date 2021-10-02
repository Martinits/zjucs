`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:37:07 10/28/2020 
// Design Name: 
// Module Name:    ID_EX
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
module ID_EX(input [31:0] pc_4, alu_a, alu_b, sw_data,
					input [32:0] ins,
					input [35:0] ctrl_sig,
					input clk, rst, we, zero,
					output reg [31:0] pc_4_out, alu_a_out, alu_b_out, sw_data_out,
					output reg [32:0] ins_out,
					output reg [35:0] ctrl_sig_out
    );
	 `define regs_ID_EX {pc_4_out, ins_out, ctrl_sig_out, alu_a_out, alu_b_out, sw_data_out}
	 
	always@(posedge clk or posedge rst) begin
		if(rst) `regs_ID_EX <=0;
		else if(we) `regs_ID_EX <= zero ? 0 : {pc_4, ins, ctrl_sig, alu_a, alu_b, sw_data};
	end

endmodule
