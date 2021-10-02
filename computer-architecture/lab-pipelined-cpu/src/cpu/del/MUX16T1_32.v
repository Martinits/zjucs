`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:38:45 11/16/2020 
// Design Name: 
// Module Name:    MUX16T1_32 
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
module MUX16T1_32(input [3:0] SEL,
						input [31:0] I0,
						input [31:0] I1,
						input [31:0] I2,
						input [31:0] I3,
						input [31:0] I4,
						input [31:0] I5,
						input [31:0] I6,
						input [31:0] I7,
						input [31:0] I8,
						input [31:0] I9,
						input [31:0] I10,
						input [31:0] I11,
						input [31:0] I12,
						input [31:0] I13,
						input [31:0] I14,
						input [31:0] I15,
						output reg [31:0] O
    );

	always @* begin
		case(SEL)
			0: O <= I0;
			1: O <= I1;
			2: O <= I2;
			3: O <= I3;
			4: O <= I4;
			5: O <= I5;
			6: O <= I6;
			7: O <= I7;
			8: O <= I8;
			9: O <= I9;
			10: O <= I10;
			11: O <= I11;
			12: O <= I12;
			13: O <= I13;
			14: O <= I14;
			15: O <= I15;
		endcase
	end

endmodule
