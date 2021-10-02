`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   14:21:44 01/03/2021
// Design Name:   data_cache
// Module Name:   E:/ZJU/CS/CA/Labs/Bonus/Cache/src/data_cache_sim.v
// Project Name:  Cache
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: data_cache
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module data_cache_sim;

	// Inputs
	reg clk;
	reg rst;
	reg en;
	reg r0w1;
	reg [31:0] addr;
	reg [31:0] din;

	// Outputs
	wire rdy;
	wire [31:0] dout;

	// Instantiate the Unit Under Test (UUT)
	data_cache uut (
		.clk(clk), 
		.rst(rst), 
		.en(en), 
		.r0w1(r0w1), 
		.addr(addr), 
		.din(din), 
		.rdy(rdy), 
		.dout(dout)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		rst = 0;
		en = 1;
		r0w1 = 0;
		addr = 32'h00000004;
		din = 32'h5a5a5a5a;

		// Wait 100 ns for global reset to finish
		#100;
		rst = 1;
		#100;
		rst = 0;
		#180
		r0w1=1;
		#20
		r0w1=0;
		addr = 32'h00000084;
		
      
		// Add stimulus here

	end
	initial forever #10 clk = ~clk;
      
endmodule

