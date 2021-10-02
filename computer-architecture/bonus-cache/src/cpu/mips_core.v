`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:28:56 11/16/2020 
// Design Name: 
// Module Name:    mips_core 
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
module mips_core (
	input wire clk,  // main clock
	input wire rst,  // synchronous reset
	// debug
	//`ifdef DEBUG
	input wire debug_en,  // debug enable
	input wire debug_step,  // debug step clock
	input wire [6:0] debug_addr,  // debug address
	output wire [31:0] debug_data,  // debug data
	//`endif
	// instruction interfaces
	output wire inst_ren,  // instruction read enable signal
	output wire [31:0] inst_addr,  // address of instruction needed
	input wire [31:0] inst_data,  // instruction fetched
	// memory interfaces
	output wire mem_ren,  // memory read enable signal
	output wire mem_wen,  // memory write enable signal
	output wire [31:0] mem_addr,  // address of memory
	output wire [31:0] mem_dout,  // data writing to memory
	input wire [31:0] mem_din,  // data read from memory
	input wire cache_rdy
	);
	
	pipelined_cpu CPU_CORE(
        .clk(clk),
        .rst(rst),
        //`ifdef DEBUG
        .debug_en(debug_en),
        .debug_step(debug_step),
        .debug_addr(debug_addr[5:0]),
        .debug_data(debug_data),
        //`endif
        .ins_in(inst_data),
        .data_in(mem_din),
        .ins_addr_out(inst_addr),
        .data_addr_out(mem_addr),
        .data_out(mem_dout),
        .mem_write(mem_wen),
        .mem_read(mem_ren),
        .ins_read(ins_ren),
		  .cache_rdy(cache_rdy)
    );
	
endmodule
