`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:39:54 11/16/2020 
// Design Name: 
// Module Name:    debug_datapath 
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
module debug_datapath(  input [5:0] debug_addr,
                        output [31:0] debug_data,
                        input [31:0] if_addr, if_ins,
                        input [31:0] id_addr, ex_addr, mem_addr, wb_addr,
								input [32:0] id_ins, ex_ins, mem_ins, wb_ins,
                        input [31:0] data_rs, data_rt,
                        input [31:0] data_imm,
                        input [31:0] alu_a, alu_b, alu_res,
                        input [3:0] pipereg_we, pipereg_zero,
                        input [31:0] data_out, data_addr_out, data_in,
                        input [4:0] regwrite_addr, 
                        input [31:0] regwrite_data,
                        input [31:0] debug_reg_data,
                        input ins_read, mem_write, mem_read
    );

	reg [31:0] debug_data_signal;
	
	always @* begin
		case (debug_addr[4:0])
			0: debug_data_signal <= if_addr;
			1: debug_data_signal <= if_ins;
			2: debug_data_signal <= id_addr-4;
			3: debug_data_signal <= id_ins;
			4: debug_data_signal <= ex_addr-4;
			5: debug_data_signal <= ex_ins;
			6: debug_data_signal <= mem_addr-4;
			7: debug_data_signal <= mem_ins;
			8: debug_data_signal <= {27'b0, id_ins[25:21]};
			9: debug_data_signal <= data_rs;
			10: debug_data_signal <= {27'b0, id_ins[20:16]};
			11: debug_data_signal <= data_rt;
			12: debug_data_signal <= data_imm;
			13: debug_data_signal <= alu_a;
			14: debug_data_signal <= alu_b;
			15: debug_data_signal <= alu_res;
			16: debug_data_signal <= 0;
			17: debug_data_signal <= 0;
			18: debug_data_signal <= {19'b0, ins_read, 7'b0, mem_read, 3'b0, mem_write};
			19: debug_data_signal <= data_addr_out;
			20: debug_data_signal <= data_in;
			21: debug_data_signal <= data_out;
			22: debug_data_signal <= {27'b0, regwrite_addr};
			23: debug_data_signal <= regwrite_data;
			default: debug_data_signal <= 32'hFFFF_FFFF;
		endcase
	end
	
	assign debug_data = debug_addr[5] ? debug_data_signal : debug_reg_data;


endmodule
