`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:23:15 01/02/2021 
// Design Name: 
// Module Name:    data_cache 
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
module data_cache(  input clk,
                    input rst,
                    input en,
                    input r0w1,
                    input [31:0] addr, din,
                    output reg rdy,
                    output reg [31:0] dout,
                    output [255:0] cache0, cache1, cache2, cache3,
                    output [3:0] valid_out, dirty_out
                    );
    
    parameter   TAG_BIT = 25,
                INDEX_BIT = 2,
                BLOCK_OFFSET_BIT = 5;
                

    reg [255:0] cache[0:3];
    reg [24:0] tag[0:3];
    reg [3:0] valid, dirty;

    assign cache0 = cache[0];
    assign cache1 = cache[1];
    assign cache2 = cache[2];
    assign cache3 = cache[3];
    assign valid_out = valid;
    assign dirty_out = dirty;

    `define IDLE (2'b00)
    `define BACK (2'b01)
    `define FILL (2'b10)

    reg [1:0] state;

    wire [24:0] addr_tag;
    wire [1:0] addr_index;
    wire [4:0] addr_block_offset;
    assign addr_tag              = addr[31:7];
    assign addr_index            = addr[6:5];
    assign addr_block_offset     = addr[4:0];
    
    assign m0h1 = valid[addr_index] && (tag[addr_index]==addr_tag);
    
    reg [2:0] counter;
    wire [2:0] counter_rev;
    assign counter_rev = 7-counter;
    reg counter_set;

    reg ram_write;
    reg [31:0] ram_addr, ram_din;
    wire [31:0] ram_dout;

    always @ (posedge clk or posedge rst) begin
        if(rst || !en) state <= `IDLE;
        else if (state == `IDLE) state <= m0h1 ? `IDLE : (valid[addr_index] && dirty[addr_index] ? `BACK : `FILL);
        else if (state == `BACK) state <= (counter == 3'b000) ? `FILL : `BACK;
        else if (state == `FILL) state <= (counter == 3'b000) ? `IDLE : `FILL;
        else state <= `IDLE;
    end

    always @ (posedge clk or posedge rst) begin
        if(rst) counter <= 3'b000;
        else if(counter) counter <= counter-1;
        else if(counter_set) counter <= 3'b111;
        else counter <= counter;
    end

    always @ * begin
        if(en) begin
            case (state)
                `IDLE: begin
                    if(m0h1) begin
                        counter_set <= 0;
                        ram_write <= 0;
                        ram_addr <= 32'h00000000;
                        ram_din <= 32'h00000000;
                    end else if (valid[addr_index] && dirty[addr_index]) begin
                        counter_set <= 1;
                        ram_write <= 1;
                        ram_addr <= {tag[addr_index], addr_index, 3'b000, 2'b00};
                        ram_din <= cache[addr_index][31:0];
                    end else begin
                        counter_set <= 1;
                        ram_write <= 0;
                        ram_addr <= {addr_tag, addr_index, 3'b000, 2'b00};
                        ram_din <= 32'h00000000;
                    end
                end
                `BACK: begin
                    if(counter == 3'b000) begin
                        counter_set <= 1;
                        ram_write <= 0;
                        ram_addr <= {addr_tag, addr_index, 3'b000, 2'b00};
                        ram_din <= 32'h00000000;
                    end else begin
                        counter_set <= 0;
                        ram_write <= 1;
                        ram_addr <= {tag[addr_index], addr_index, counter_rev+1, 2'b00};
                        case(counter_rev+1)
                            // 3'b000: ram_din <= cache[addr_index][31:0];
                            3'b001: ram_din <= cache[addr_index][63:32];
                            3'b010: ram_din <= cache[addr_index][95:64];
                            3'b011: ram_din <= cache[addr_index][127:96];
                            3'b100: ram_din <= cache[addr_index][159:128];
                            3'b101: ram_din <= cache[addr_index][191:160];
                            3'b110: ram_din <= cache[addr_index][223:192];
                            3'b111: ram_din <= cache[addr_index][255:224];
                        endcase
                    end
                end
                `FILL: begin
                    if(counter == 3'b000) begin
                        counter_set <= 0;
                        ram_write <= 0;
                        ram_addr <= 32'h00000000;
                    end else begin
                        counter_set <= 0;
                        ram_write <= 0;
                        ram_addr <= {addr_tag, addr_index, counter_rev+1, 2'b00};
                        case(counter_rev+1)
                            // 3'b000: ram_din <= {addr_tag, addr_index, 3'b000, 2'b00};
                            3'b001: ram_addr <= {addr_tag, addr_index, 3'b001, 2'b00};
                            3'b010: ram_addr <= {addr_tag, addr_index, 3'b010, 2'b00};
                            3'b011: ram_addr <= {addr_tag, addr_index, 3'b011, 2'b00};
                            3'b100: ram_addr <= {addr_tag, addr_index, 3'b100, 2'b00};
                            3'b101: ram_addr <= {addr_tag, addr_index, 3'b101, 2'b00};
                            3'b110: ram_addr <= {addr_tag, addr_index, 3'b110, 2'b00};
                            3'b111: ram_addr <= {addr_tag, addr_index, 3'b111, 2'b00};
                        endcase
                    end
                    ram_din <= 32'h00000000;
                end
                default: begin
                    counter_set <= 0;
                    ram_write <= 0;
                    ram_addr <= 32'h00000000;
                    ram_din <= 32'h00000000;
                end
            endcase
        end else begin
            counter_set <= 0;
            ram_write <= 0;
            ram_addr <= 32'h00000000;
            ram_din <= 32'h00000000;
        end
    end

    wire [255:0] mask_ram = ~({{7{32'h00000000}}, 32'hffffffff}<<(counter_rev*32));
    wire [255:0] new_ram = ({{7{32'h00000000}}, ram_dout} << (counter_rev*32));
    wire [255:0] mask_write = ~({{7{32'h00000000}}, 32'hffffffff} << (addr_block_offset[4:2]*32));
    wire [255:0] new_write = ({{7{32'h00000000}}, din} << (addr_block_offset[4:2]*32));
	integer i;
    always @ (posedge clk or posedge rst) begin
        if(rst) begin
            for (i=0;i<4;i=i+1) begin
                cache[i] <= 0;
                tag[i] <= 0;
                dirty[i] <= 0;
                valid[i] <= 0;
            end
            rdy <= 0;
        end else if (en) begin
            if (state == `IDLE) begin
                if(m0h1 && r0w1) begin
                    cache[addr_index] <= (cache[addr_index] & mask_write) | new_write;
                    dirty[addr_index] <= 1;
                end
                rdy <= m0h1;
            end else if(state == `FILL) begin
                cache[addr_index] <= (cache[addr_index] & mask_ram) | ((r0w1 && counter_rev==addr_block_offset[4:2]) ? new_write : new_ram);
                if(counter == 3'b000) begin
                    valid[addr_index] <= 1;
                    dirty[addr_index] <= r0w1;
                    tag[addr_index] <= addr_tag;
                    rdy <= 1;
                end else rdy <= 0;
            end else rdy <= 0;
        end else rdy <= 0;
    end

    always @ * begin
        if(en && state == `IDLE && !r0w1 && rdy && m0h1)
            case(addr_block_offset[4:2])
                3'b000: dout <= cache[addr_index][31:0];
                3'b001: dout <= cache[addr_index][63:32];
                3'b010: dout <= cache[addr_index][95:64];
                3'b011: dout <= cache[addr_index][127:96];
                3'b100: dout <= cache[addr_index][159:128];
                3'b101: dout <= cache[addr_index][191:160];
                3'b110: dout <= cache[addr_index][223:192];
                3'b111: dout <= cache[addr_index][255:224];
            endcase
        else dout <= 32'h00000000;
    end

    data_ram DATA_RAM (
		.clk(clk),
		.we(ram_write),
		.addr({2'b0, ram_addr[31:2]}),
		.din(ram_din),
		.dout(ram_dout)
	);
    
endmodule
