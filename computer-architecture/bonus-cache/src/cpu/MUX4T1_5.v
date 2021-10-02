`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:42:41 05/05/2020 
// Design Name: 
// Module Name:    MUX4T1_5 
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
module MUX4T1_5(input [4:0] I0, I1, I2, I3,
					 input [1:0] SEL,
					 output reg [4:0] O
					);
	always @* begin
		case(SEL)
			2'b00: O<=I0;
			2'b01: O<=I1;
			2'b10: O<=I2;
			2'b11: O<=I3;
		endcase
	end
endmodule
