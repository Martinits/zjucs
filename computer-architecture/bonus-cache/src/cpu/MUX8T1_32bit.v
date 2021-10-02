`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:48:58 11/03/2020 
// Design Name: 
// Module Name:    MUX8T1_32bit 
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
module MUX8T1_32bit(input [31:0] I0, I1, I2, I3, I4, I5, I6, I7, 
					 input [2:0] SEL,
					 output reg [31:0] O
    );
	 always @* begin
	 case(SEL)
		3'b000: O<=I0;
		3'b001: O<=I1;
		3'b010: O<=I2;
		3'b011: O<=I3;
		3'b100: O<=I4;
		3'b101: O<=I5;
		3'b110: O<=I6;
		3'b111: O<=I7;
	 endcase
	end
endmodule
