`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   18:36:39 11/26/2020
// Design Name:   IF_ID
// Module Name:   E:/ZJU/CS/CA/Labs/Lab2/Lab2_mixup/src/IF_ID_sim.v
// Project Name:  Lab2_mixup
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: IF_ID
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module IF_ID_sim;

	// Inputs
	reg [31:0] pc_4;
	reg [31:0] ins;
	reg clk;
	reg rst;
	reg we;
	reg zero;

	// Outputs
	wire [31:0] pc_4_out;
	wire [31:0] ins_out;

	// Instantiate the Unit Under Test (UUT)
	IF_ID uut (
		.pc_4(pc_4), 
		.ins(ins), 
		.clk(clk), 
		.rst(rst), 
		.we(we), 
		.zero(zero), 
		.pc_4_out(pc_4_out), 
		.ins_out(ins_out)
	);

	initial begin
		// Initialize Inputs
		pc_4 = 0;
		ins = 0;
		clk = 0;
		rst = 1;
		we = 1;
		zero = 0;

		// Wait 100 ns for global reset to finish
		#100;
		rst=0;
		ins=32'h00000824;
		pc_4=pc_4+4;
        
		// Add stimulus here

	end
	
	initial forever #10 clk <= ~clk;
      
endmodule

