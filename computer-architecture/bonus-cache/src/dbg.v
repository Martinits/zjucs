`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:37:56 01/03/2021 
// Design Name: 
// Module Name:    dbg 
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
module dbg(input [6:0] debug_addr,
            input [255:0] cache0, cache1, cache2, cache3,
            input [3:0] valid, dirty,
            input [31:0] datapath_debug_data,
            output [31:0] debug_data 
    );

    reg [31:0] data;

    always @ * begin
        case(debug_addr[5:0])
            6'h00: data <= cache0[31:0];
            6'h01: data <= cache0[63:32];
            6'h02: data <= cache0[95:64];
            6'h03: data <= cache0[127:96];
            6'h04: data <= cache0[159:128];
            6'h05: data <= cache0[191:160];
            6'h06: data <= cache0[223:192];
            6'h07: data <= cache0[255:224];
            6'h08: data <= cache1[31:0];
            6'h09: data <= cache1[63:32];
            6'h0a: data <= cache1[95:64];
            6'h0b: data <= cache1[127:96];
            6'h0c: data <= cache1[159:128];
            6'h0d: data <= cache1[191:160];
            6'h0e: data <= cache1[223:192];
            6'h0f: data <= cache1[255:224];
            6'h10: data <= cache2[31:0];
            6'h11: data <= cache2[63:32];
            6'h12: data <= cache2[95:64];
            6'h13: data <= cache2[127:96];
            6'h14: data <= cache2[159:128];
            6'h15: data <= cache2[191:160];
            6'h16: data <= cache2[223:192];
            6'h17: data <= cache2[255:224];
            6'h18: data <= cache3[31:0];
            6'h19: data <= cache3[63:32];
            6'h1a: data <= cache3[95:64];
            6'h1b: data <= cache3[127:96];
            6'h1c: data <= cache3[159:128];
            6'h1d: data <= cache3[191:160];
            6'h1e: data <= cache3[223:192];
            6'h1f: data <= cache3[255:224];
            6'h20: data <= valid[0];
            6'h21: data <= valid[1];
            6'h22: data <= valid[2];
            6'h23: data <= valid[3];
            6'h24: data <= dirty[0];
            6'h25: data <= dirty[1];
            6'h26: data <= dirty[2];
            6'h27: data <= dirty[3];
        endcase
    end

    assign debug_data = debug_addr[6] ? data : datapath_debug_data;

endmodule
