`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:31:48 05/05/2020 
// Design Name: 
// Module Name:    shamt_ext 
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
module shamt_ext(input [4:0] shamt,
						output [31:0] O
    );
	assign O={27'b0, shamt};

endmodule
