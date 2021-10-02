`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   17:48:49 11/26/2020
// Design Name:   inst_rom
// Module Name:   E:/ZJU/CS/CA/Labs/Lab2/Lab2_mixup/src/inst_rom_sim.v
// Project Name:  Lab2_mixup
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: inst_rom
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module inst_rom_sim;

	// Inputs
	reg clk;
	reg [31:0] addr;

	// Outputs
	wire [31:0] dout;

	// Instantiate the Unit Under Test (UUT)
	inst_rom uut (
		.clk(clk), 
		.addr(addr), 
		.dout(dout)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		addr = 0;

		// Wait 100 ns for global reset to finish
		forever #100 addr=addr+1;
        
		// Add stimulus here

	end
      
endmodule

