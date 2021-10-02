`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:48:42 11/27/2020 
// Design Name: 
// Module Name:    ALU 
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
module ALU(input [31:0] A, B,
            input [3:0] ctrl,
            output reg [31:0] res,
            output zero, overflow
    );

    wire [63:0] sra_tmp;
    assign sra_tmp = {{32{B[31]}}, B} >> A;

    always @* begin
        case(ctrl)
            /*and*/  4'b0000: res <= A & B;
            /*or*/   4'b0001: res <= A | B;
            /*add*/  4'b0010: res <= $signed(A) + $signed(B);
            /*sra*/  4'b0011: res <= sra_tmp[31:0];
            /*sll*/  4'b0100: res <= B << A;
            /*srl*/  4'b0101: res <= B >> A;
            /*sub*/  4'b0110: res <= $signed(A) - $signed(B);
            /*slt*/  4'b0111: res <= ($signed(A) < $signed(B)) ? 32'h00000001 : 32'h00000000;
            /*addu*/ 4'b1000: res <= $unsigned(A) + $unsigned(B);
            /*subu*/ 4'b1001: res <= $unsigned(A) - $unsigned(B);
            /*sltu*/ 4'b1010: res <= ($unsigned(A) < $unsigned(B)) ? 32'h00000001 : 32'h00000000;
            /*xor*/  4'b1011: res <= A ^ B;
            /*nor*/  4'b1100: res <= ~(A | B);
            /*srav*/ 4'b1101: res <= (A<32) ? sra_tmp[31:0] : {32{B[31]}};
            /*sllv*/ 4'b1110: res <= B << A;
            /*srlv*/ 4'b1111: res <= B >> A;
        endcase
    end

    assign zero = (res==32'h00000000);

endmodule
