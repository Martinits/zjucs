`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   16:03:15 11/30/2020
// Design Name:   Controller
// Module Name:   E:/ZJU/CS/CA/Labs/Lab2/Lab2_mixup/src/controller_sim.v
// Project Name:  Lab2_mixup
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Controller
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module controller_sim;

	// Inputs
	reg clk;
	reg rst;
	reg debug_en;
	reg debug_step;
	reg beqbne_equal;
	reg [32:0] id_ins;
	reg [32:0] ex_ins;
	reg [32:0] mem_ins;
	reg [32:0] wb_ins;

	// Outputs
	wire cpu_en;
	wire pc_write;
	wire [35:0] signals;
	wire [3:0] pipereg_we;
	wire [3:0] pipereg_zero;

	// Instantiate the Unit Under Test (UUT)
	Controller uut (
		.clk(clk), 
		.rst(rst), 
		.debug_en(debug_en), 
		.debug_step(debug_step), 
		.cpu_en(cpu_en), 
		.beqbne_equal(beqbne_equal), 
		.id_ins(id_ins), 
		.ex_ins(ex_ins), 
		.mem_ins(mem_ins), 
		.wb_ins(wb_ins), 
		.pc_write(pc_write), 
		.signals(signals), 
		.pipereg_we(pipereg_we), 
		.pipereg_zero(pipereg_zero)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		rst = 0;
		debug_en = 0;
		debug_step = 0;
		beqbne_equal = 0;
		id_ins = 33'h120a68000;
		ex_ins = 33'h13c051111;
		mem_ins = 33'h100012882;
		wb_ins = 0;

		// Wait 100 ns for global reset to finish
		#100;
		rst = 1;
		#100;
		rst=0;
        
		// Add stimulus here

	end
	initial forever #10 clk<=~clk;
	
      
endmodule

