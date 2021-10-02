// Verilog test fixture created from schematic E:\ZJU\CS\CA\Labs\Lab2\Lab2_mixup\src\cpu\pipelined_cpu.sch - Wed Nov 25 21:49:32 2020

`timescale 1ns / 1ps

module pipelined_cpu_pipelined_cpu_sch_tb();

// Inputs
   reg clk;
   reg rst;
   reg [31:0] ins_in;
   reg [31:0] data_in;
   reg [5:0] debug_addr;
   reg debug_en;
   reg debug_step;

// Output
   wire [31:0] ins_addr_out;
   wire [31:0] data_addr_out;
   wire [31:0] data_out;
   wire mem_write;
   wire mem_read;
   wire ins_read;
   wire [31:0] debug_data;

// Bidirs

// Instantiate the UUT
   pipelined_cpu UUT (
		.clk(clk), 
		.rst(rst), 
		.ins_in(ins_in), 
		.data_in(data_in), 
		.ins_addr_out(ins_addr_out), 
		.data_addr_out(data_addr_out), 
		.data_out(data_out), 
		.mem_write(mem_write), 
		.mem_read(mem_read), 
		.ins_read(ins_read), 
		.debug_data(debug_data), 
		.debug_addr(debug_addr), 
		.debug_en(debug_en), 
		.debug_step(debug_step)
   );
// Initialize Inputs
      initial begin
			clk = 0;
			rst = 1;
			ins_in = 0;
			data_in = 0;
			debug_addr = 0;
			debug_en = 0;
			debug_step = 0;
			
			#100;
			rst=0;
		end
		
		initial forever #10 clk <= ~clk;
endmodule
