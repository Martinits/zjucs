//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:45:10 10/19/2020 
// Design Name: 
// Module Name:    Controller 
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
module Controller(  input clk,
                    input rst,
                    input debug_en,  // debug enable
                    input debug_step,  // debug step clock
                    output cpu_en,
                    input beqbne_equal,
                    input [32:0] id_ins, ex_ins, mem_ins, wb_ins,
                    output reg pc_write,
                    output [35:0] signals,
                    output reg [3:0] pipereg_we, pipereg_zero
                    );
	//opcode
    parameter   lw=6'h23, sw=6'h2b,
				r_type=6'h00, beq=6'h04, bne=6'h05,
                lui=6'h0f, j=6'h02, jal=6'h03,
                addi=6'h08, andi=6'h0c, ori=6'h0d, xori=6'h0e, slti=6'h0a,
                addiu=6'h09, sltiu=6'h0b;
    //funct for r type
    parameter   jr=6'h08, jalr=6'h09, 
                sll=6'h00, srl=6'h02, sra=6'h03,
                add=6'h20, sub=6'h22,
                r_and=6'h24, r_or=6'h25, 
                r_xor=6'h26, r_nor=6'h27, slt=6'h2a,
                addu=6'h21, subu=6'h23, sltu=6'h2b, sllv=6'h04, srlv=6'h06, srav=6'h07;

    `define NULL 0
    `define OPCODE [31:26]
    `define RS     [25:21]
    `define RT     [20:16]
    `define RD     [15:11]
    `define FUNCT  [5:0]

    `define IF 0
    `define ID 1
    `define EX 2
    `define MEM 3
    `define WB 4
    `define IF_ID 0
    `define ID_EX 1
    `define EX_MEM 2
    `define MEM_WB 3

    reg mem_sw;
    reg ex_sw_src_ex, alu_a_bypass_ex, alu_b_bypass_ex;
    reg [2:0] id_beqbne_a;
    reg [2:0] id_beqbne_b;
    reg [2:0] ex_sw_src;
    reg [2:0] alu_a_bypass;
    reg [2:0] alu_b_bypass;
    // reg pc_write;
    reg [1:0] pc_src;
    reg [3:0] alu_ctrl;
    reg alu_a;
    reg alu_b;
    reg ext_sel;
    reg reg_write;
    reg [1:0] reg_dest;
    reg [1:0] data2reg;
    reg mem_read;
    reg mem_write;

    `define org_signals {pc_src, alu_ctrl, alu_a, alu_b, ext_sel, reg_write, reg_dest, data2reg, mem_write, mem_read}
    assign signals = {mem_sw, ex_sw_src_ex, alu_a_bypass_ex, alu_b_bypass_ex, id_beqbne_a, id_beqbne_b, ex_sw_src, alu_a_bypass, alu_b_bypass, pc_write, `org_signals};
    
    always @* begin
        if(rst) `org_signals <= 0;
        else case(id_ins`OPCODE)
            r_type: case(id_ins`FUNCT)
                jr:begin
                    pc_src <= 2'b11;
                    alu_ctrl <= `NULL;
                    alu_a <= `NULL;
                    alu_b <= `NULL;
                    ext_sel <= `NULL;
                    reg_write <= 0;
                    reg_dest <= `NULL;
                    data2reg <= `NULL;
                    mem_write <= 0;
                    mem_read <= 0;
                end
                jalr:begin
                    pc_src <= 2'b11;
                    alu_ctrl <= `NULL;
                    alu_a <= `NULL;
                    alu_b <= `NULL;
                    ext_sel <= `NULL;
                    reg_write <= 1;
                    reg_dest <= 2'b01;
                    data2reg <= 2'b10;
                    mem_write <= 0;
                    mem_read <= 0;
                end
                default: begin
                    pc_src <= 2'b00;
                    case(id_ins`FUNCT)
                        r_and:  alu_ctrl <= 4'b0000;
                        r_or:   alu_ctrl <= 4'b0001;
                        add:    alu_ctrl <= 4'b0010;
                        sra:    alu_ctrl <= 4'b0011;
                        sll:    alu_ctrl <= 4'b0100;
                        srl:    alu_ctrl <= 4'b0101;
                        sub:    alu_ctrl <= 4'b0110;
                        slt:    alu_ctrl <= 4'b0111;
                        addu:   alu_ctrl <= 4'b1000;
                        subu:   alu_ctrl <= 4'b1001;
                        sltu:   alu_ctrl <= 4'b1010;
                        r_xor:  alu_ctrl <= 4'b1011;
                        r_nor:  alu_ctrl <= 4'b1100;
                        srav:   alu_ctrl <= 4'b1101;
                        sllv:   alu_ctrl <= 4'b1110;
                        srlv:   alu_ctrl <= 4'b1111;
                        default: alu_ctrl <= `NULL;
                    endcase
                    alu_a <= (id_ins`FUNCT==sll||id_ins`FUNCT==srl||id_ins`FUNCT==sra);
                    alu_b <= 0;
                    ext_sel <= `NULL;
                    reg_write <= 1;
                    reg_dest <= 2'b01;
                    data2reg <= 2'b00;
                    mem_write <= 0;
                    mem_read <= 0;
                end
            endcase
            sw:begin
                pc_src <= 2'b00;
                alu_ctrl <= 4'b0010;
                alu_a <= 0;
                alu_b <= 1;
                ext_sel <= 0;
                reg_write <= 0;
                reg_dest <= `NULL;
                data2reg <= `NULL;
                mem_write <= 1;
                mem_read <= 0;
            end
            lw:begin
                pc_src <= 2'b00;
                alu_ctrl <= 4'b0010;
                alu_a <= 0;
                alu_b <= 1;
                ext_sel <= 0;
                reg_write <= 1;
                reg_dest <= 2'b00;
                data2reg <= 2'b01;
                mem_write <= 0;
                mem_read <= 1;
            end
            beq:begin
                pc_src <= (beqbne_equal ? 2'b01 : 2'b00);
                alu_ctrl <= 4'b0110;
                alu_a <= 0;
                alu_b <= 0;
                ext_sel <= `NULL;
                reg_write <= 0;
                reg_dest <= `NULL;
                data2reg <= `NULL;
                mem_write <= 0;
                mem_read <= 0;
            end
            bne:begin
                pc_src <= (beqbne_equal ? 2'b00 : 2'b01);
                alu_ctrl <= 4'b0110;
                alu_a <= 0;
                alu_b <= 0;
                ext_sel <= `NULL;
                reg_write <= 0;
                reg_dest <= `NULL;
                data2reg <= `NULL;
                mem_write <= 0;
                mem_read <= 0;
            end
            lui:begin
                pc_src <= 2'b00;
                alu_ctrl <= `NULL;
                alu_a <= `NULL;
                alu_b <= `NULL;
                ext_sel <= `NULL;
                reg_write <= 1;
                reg_dest <= 2'b00;
                data2reg <= 2'b11;
                mem_write <= 0;
                mem_read <= 0;
            end
            j:begin
                pc_src <= 2'b10;
                alu_ctrl <= `NULL;
                alu_a <= `NULL;
                alu_b <= `NULL;
                ext_sel <= `NULL;
                reg_write <= 0;
                reg_dest <= `NULL;
                data2reg <= `NULL;
                mem_write <= 0;
                mem_read <= 0;
            end
            jal:begin
                pc_src <= 2'b10;
                alu_ctrl <= `NULL;
                alu_a <= `NULL;
                alu_b <= `NULL;
                ext_sel <= `NULL;
                reg_write <= 1;
                reg_dest <= 2'b10;
                data2reg <= 2'b10;
                mem_write <= 0;
                mem_read <= 0;
            end
            addi:begin
                pc_src <= 2'b00;
                alu_ctrl <= 4'b0010;
                alu_a <= 0;
                alu_b <= 1;
                ext_sel <= 0;
                reg_write <= 1;
                reg_dest <= 2'b00;
                data2reg <= 2'b00;
                mem_write <= 0;
                mem_read <= 0;
            end
            andi:begin
                pc_src <= 2'b00;
                alu_ctrl <= 4'b0000;
                alu_a <= 0;
                alu_b <= 1;
                ext_sel <= 1;
                reg_write <= 1;
                reg_dest <= 2'b00;
                data2reg <= 2'b00;
                mem_write <= 0;
                mem_read <= 0;
            end
            ori:begin
                pc_src <= 2'b00;
                alu_ctrl <= 4'b0001;
                alu_a <= 0;
                alu_b <= 1;
                ext_sel <= 1;
                reg_write <= 1;
                reg_dest <= 2'b00;
                data2reg <= 2'b00;
                mem_write <= 0;
                mem_read <= 0;
            end
            xori:begin
                pc_src <= 2'b00;
                alu_ctrl <=4'b1011;
                alu_a <= 0;
                alu_b <= 1;
                ext_sel <= 1;
                reg_write <= 1;
                reg_dest <= 2'b00;
                data2reg <= 2'b00;
                mem_write <= 0;
                mem_read <= 0;
            end
            slti:begin
                pc_src <= 2'b00;
                alu_ctrl <= 4'b0111;
                alu_a <= 0;
                alu_b <= 1;
                ext_sel <= 0;
                reg_write <= 1;
                reg_dest <= 2'b00;
                data2reg <= 2'b00;
                mem_write <= 0;
                mem_read <= 0;
            end
            addiu:begin
                pc_src <= 2'b00;
                alu_ctrl <= 4'b1000;
                alu_a <= 0;
                alu_b <= 1;
                ext_sel <= 1;
                reg_write <= 1;
                reg_dest <= 2'b00;
                data2reg <= 2'b00;
                mem_write <= 0;
                mem_read <= 0;
            end
            sltiu:begin
                pc_src <= 2'b00;
                alu_ctrl <= 4'b1010;
                alu_a <= 0;
                alu_b <= 1;
                ext_sel <= 1;
                reg_write <= 1;
                reg_dest <= 2'b00;
                data2reg <= 2'b00;
                mem_write <= 0;
                mem_read <= 0;
            end
            default: `org_signals <= 0;
        endcase
    end

    reg [4:0] wreg[`EX:`WB];
    always @* begin
        if(rst)begin
            wreg[`EX] <= 0;
            wreg[`MEM] <= 0;
            wreg[`WB] <= 0;
        end else begin
            if(ex_ins[32]) begin
                case(ex_ins`OPCODE)
                    r_type, jalr: wreg[`EX] <= ex_ins`RD;
                    lw, addi, andi, ori, xori, slti, lui: wreg[`EX] <= ex_ins`RT;
                    default: wreg[`EX] <= 0;
                endcase
            end else wreg[`EX] <= 0;
            if(mem_ins[32]) begin
                case(mem_ins`OPCODE)
                    r_type, jalr: wreg[`MEM] <= mem_ins`RD;
                    lw, addi, andi, ori, xori, slti, lui: wreg[`MEM] <= mem_ins`RT;
                    default: wreg[`MEM] <= 0;
                endcase
            end else wreg[`WB] <= 0;
            if(wb_ins[32]) begin
                case(wb_ins`OPCODE)
                    r_type, jalr: wreg[`WB] <= wb_ins`RD;
                    lw, addi, andi, ori, xori, slti, lui: wreg[`WB] <= wb_ins`RT;
                    default: wreg[`WB] <= 0;
                endcase
            end else wreg[`WB] <= 0;
        end
    end

    wire wreg_valid[`EX:`WB];
    assign wreg_valid[`EX] = (wreg[`EX]!=0);
    assign wreg_valid[`MEM] = (wreg[`MEM]!=0);
    assign wreg_valid[`WB] = (wreg[`WB]!=0);

    reg stall_cnt; // stalls left to push
    always @ (posedge clk or posedge rst) begin
        if(rst) stall_cnt <= 0;
        else if(~cpu_en) stall_cnt <= stall_cnt;
        else if(stall_cnt) stall_cnt <= 0;
        else stall_cnt <= (stall_sign == 2'h2);
    end
    // if stall_cnt != 0, stall_sign MUST be 0 !!!!!

    reg [1:0] stall_sign;
    wire no_stall;
    assign no_stall = (stall_cnt == 1'b0 && stall_sign == 2'h0);

    always @* begin
        if(rst)begin
            pc_write     <= 1'b0;
            pipereg_we   <= 4'b0000;
            pipereg_zero <= 4'b0000;
        end else if(~cpu_en) begin
            pc_write     <= 1'b0;
            pipereg_we   <= 4'b0000;
            pipereg_zero <= 4'b1111;
        end else if(no_stall) begin
            pc_write     <= 1'b1;
            pipereg_we   <= 4'b1111;
            pipereg_zero <= (pc_src==2'b00 && no_stall ? 4'b0000 : 4'b0001);
        end else begin
            pc_write     <= 1'b0;
            pipereg_we   <= 4'b1110;
            pipereg_zero <= 4'b0010;
        end
    end

    always @* begin
        ex_sw_src_ex <= 1'b0;
        alu_a_bypass_ex <= 1'b0;
        alu_b_bypass_ex <= 1'b0;
        if(rst) begin
            mem_sw <= 1'b0;
            id_beqbne_a <= 3'h0;
            id_beqbne_b <= 3'h0;
            ex_sw_src <= 3'h0;
            alu_a_bypass <= 3'h0;
            alu_b_bypass <= 3'h0;
            stall_sign <= 2'h0;
        end else case(id_ins`OPCODE)
            beq, bne: begin
                mem_sw <= 1'b0;
                ex_sw_src <= 3'h0;
                alu_a_bypass <= 3'h0;
                alu_b_bypass <= 3'h0;
                if(ex_ins[32] && wreg_valid[`EX] && (wreg[`EX]==id_ins`RS || wreg[`EX]==id_ins`RT) && ex_ins`OPCODE==lw) stall_sign <= 2'h2;
                else if(mem_ins[32] && wreg_valid[`MEM] && (wreg[`MEM]==id_ins`RS || wreg[`MEM]==id_ins`RT) && mem_ins`OPCODE==lw) stall_sign <= 2'h1;
                else stall_sign <= 2'h0;
                if(ex_ins[32] && wreg_valid[`EX] && wreg[`EX]==id_ins`RS) begin
                    case(ex_ins`OPCODE)
                        r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                id_beqbne_a <= 3'h1;
                        jalr:   id_beqbne_a <= 3'h2;
                        lw:     id_beqbne_a <= 3'h0;
                        lui:    id_beqbne_a <= 3'h3;
                        default:id_beqbne_a <= 3'h0;
                    endcase
                end else if(mem_ins[32] && wreg_valid[`MEM] && wreg[`MEM]==id_ins`RS) begin
                    case(mem_ins`OPCODE)
                        r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                id_beqbne_a <= 3'h4;
                        jalr:   id_beqbne_a <= 3'h5;
                        lw:     id_beqbne_a <= 3'h0;
                        lui:    id_beqbne_a <= 3'h6;
                        default:id_beqbne_a <= 3'h0;
                    endcase
                end else id_beqbne_a <= 3'h0;
                if(ex_ins[32] && wreg_valid[`EX] && wreg[`EX]==id_ins`RT) begin
                    case(ex_ins`OPCODE)
                        r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                id_beqbne_b <= 3'h1;
                        jalr:   id_beqbne_b <= 3'h2;
                        lw:     id_beqbne_b <= 3'h0;
                        lui:    id_beqbne_b <= 3'h3;
                        default:id_beqbne_b <= 3'h0;
                    endcase
                end else if(mem_ins[32] && wreg_valid[`MEM] && wreg[`MEM]==id_ins`RT) begin
                    case(mem_ins`OPCODE)
                        r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                id_beqbne_b <= 3'h4;
                        jalr:   id_beqbne_b <= 3'h5;
                        lw:     id_beqbne_b <= 3'h0;
                        lui:    id_beqbne_b <= 3'h6;
                        default:id_beqbne_b <= 3'h0;
                    endcase
                end else id_beqbne_b <= 3'h0;
            end
            ////////////////////////////////////////
            r_type: begin
                mem_sw <= 1'b0;
                if(id_ins`OPCODE==jr || id_ins`OPCODE==jalr) begin
                    ex_sw_src <= 3'h0;
                    alu_a_bypass <= 3'h0;
                    alu_b_bypass <= 3'h0;
						  id_beqbne_b <= 3'h0;
                    if(ex_ins[32] && wreg_valid[`EX] && wreg[`EX]==id_ins`RS && ex_ins`OPCODE==lw) stall_sign <= 2'h2;
                    else if(mem_ins[32] && wreg_valid[`MEM] && wreg[`MEM]==id_ins`RS && mem_ins`OPCODE==lw) stall_sign <= 2'h1;
                    else stall_sign <= 2'h0;
                    if(ex_ins[32] && wreg_valid[`EX] && wreg[`EX]==id_ins`RS) begin
                        case(ex_ins`OPCODE)
                            r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                    id_beqbne_a <= 3'h1;
                            jalr:   id_beqbne_a <= 3'h2;
                            lw:     id_beqbne_a <= 3'h0;
                            lui:    id_beqbne_a <= 3'h3;
                            default:id_beqbne_a <= 3'h0;
                        endcase
                    end else if(mem_ins[32] && wreg_valid[`MEM] && wreg[`MEM]==id_ins`RS) begin
                        case(mem_ins`OPCODE)
                            r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                    id_beqbne_a <= 3'h4;
                            jalr:   id_beqbne_a <= 3'h5;
                            lw:     id_beqbne_a <= 3'h0;
                            lui:    id_beqbne_a <= 3'h6;
                            default:id_beqbne_a <= 3'h0;
                        endcase
                    end else id_beqbne_a <= 3'h0;
                end else begin
                    id_beqbne_a <= 3'h0;
                    id_beqbne_b <= 3'h0;
                    ex_sw_src <= 3'h0;
                    stall_sign <= (ex_ins[32] && wreg_valid[`EX] && (wreg[`EX]==id_ins`RS || wreg[`EX]==id_ins`RT) && ex_ins`OPCODE==lw) ? 2'h1 : 2'h0;
                    
                    if(ex_ins[32] && wreg_valid[`EX] && wreg[`EX]==id_ins`RS) begin
                        alu_a_bypass_ex <= 1'b0;
                        case(ex_ins`OPCODE)
                            r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                    alu_a_bypass <= 3'h1;
                            jalr:   alu_a_bypass <= 3'h2;
                            lw:     alu_a_bypass <= 3'h0;
                            lui:    alu_a_bypass <= 3'h3;
                            default:alu_a_bypass <= 3'h0;
                        endcase
                    end else if(mem_ins[32] && wreg_valid[`MEM] && wreg[`MEM]==id_ins`RS) begin
                        alu_a_bypass_ex <= 1'b0;
                        case(mem_ins`OPCODE)
                            r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                    alu_a_bypass <= 3'h4;
                            jalr:   alu_a_bypass <= 3'h5;
                            lw:     alu_a_bypass <= 3'h7;
                            lui:    alu_a_bypass <= 3'h6;
                            default:alu_a_bypass <= 3'h0;
                        endcase
                    end else alu_a_bypass <= 3'h0;

                    if(ex_ins[32] && wreg_valid[`EX] && wreg[`EX]==id_ins`RT) begin
                        alu_b_bypass_ex <= 1'b0;
                        case(ex_ins`OPCODE)
                            r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                    alu_b_bypass <= 3'h1;
                            jalr:   alu_b_bypass <= 3'h2;
                            lw:     alu_b_bypass <= 3'h0;
                            lui:    alu_b_bypass <= 3'h3;
                            default:alu_b_bypass <= 3'h0;
                        endcase
                    end else if(mem_ins[32] && wreg_valid[`MEM] && wreg[`MEM]==id_ins`RT) begin
                        alu_b_bypass_ex <= 1'b0;
                        case(mem_ins`OPCODE)
                            r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                    alu_b_bypass <= 3'h4;
                            jalr:   alu_b_bypass <= 3'h5;
                            lw:     alu_b_bypass <= 3'h7;
                            lui:    alu_b_bypass <= 3'h6;
                            default:alu_b_bypass <= 3'h0;
                        endcase
                    end else alu_b_bypass <= 3'h0;
                end
            end
            sw: begin
                id_beqbne_a <= 3'h0;
                id_beqbne_b <= 3'h0;
                alu_b_bypass <= 3'h0;
                stall_sign <= (ex_ins[32] && wreg_valid[`EX] && wreg[`EX]==id_ins`RS && ex_ins`OPCODE==lw) ? 2'h1 : 2'h0;
                mem_sw <= (ex_ins[32] && wreg_valid[`EX] && wreg[`EX]==id_ins`RT && ex_ins`OPCODE==lw);
                if(ex_ins[32] && wreg_valid[`EX] && wreg[`EX]==id_ins`RS) begin
                    case(ex_ins`OPCODE)
                        r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                alu_a_bypass <= 3'h1;
                        jalr:   alu_a_bypass <= 3'h2;
                        lw:     alu_a_bypass <= 3'h0;
                        lui:    alu_a_bypass <= 3'h3;
                        default:alu_a_bypass <= 3'h0;
                    endcase
                end else if(mem_ins[32] && wreg_valid[`MEM] && wreg[`MEM]==id_ins`RS) begin
                    case(mem_ins`OPCODE)
                        r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                alu_a_bypass <= 3'h4;
                        jalr:   alu_a_bypass <= 3'h5;
                        lw:     alu_a_bypass <= 3'h7;
                        lui:    alu_a_bypass <= 3'h6;
                        default:alu_a_bypass <= 3'h0;
                    endcase
                end else alu_a_bypass <= 3'h0;
                
                if(ex_ins[32] && wreg_valid[`EX] && wreg[`EX]==id_ins`RT) begin
                    case(ex_ins`OPCODE)
                        r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                ex_sw_src <= 3'h1;
                        jalr:   ex_sw_src <= 3'h2;
                        lw:     ex_sw_src <= 3'h0;
                        lui:    ex_sw_src <= 3'h3;
                        default:ex_sw_src <= 3'h0;
                    endcase
                end else if(mem_ins[32] && wreg_valid[`MEM] && wreg[`MEM]==id_ins`RT) begin
                    case(mem_ins`OPCODE)
                        r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                ex_sw_src <= 3'h4;
                        jalr:   ex_sw_src <= 3'h5;
                        lw:     ex_sw_src <= 3'h7;
                        lui:    ex_sw_src <= 3'h6;
                        default:ex_sw_src <= 3'h0;
                    endcase
                end else ex_sw_src <= 3'h0;
            end
            //////
            addi, andi, ori, xori, slti, lw, addiu, sltiu: begin
                mem_sw <= 1'b0;
                id_beqbne_a <= 3'h0;
                id_beqbne_b <= 3'h0;
                ex_sw_src <= 3'h0;
                alu_b_bypass <= 3'h0;
                stall_sign <= (ex_ins[32] && wreg_valid[`EX] && wreg[`EX]==id_ins`RS && ex_ins`OPCODE==lw) ? 2'h1 : 2'h0;
                if(ex_ins[32] && wreg_valid[`EX] && wreg[`EX]==id_ins`RS) begin
                    case(ex_ins`OPCODE)
                        r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                alu_a_bypass <= 3'h1;
                        jalr:   alu_a_bypass <= 3'h2;
                        lw:     alu_a_bypass <= 3'h0;
                        lui:    alu_a_bypass <= 3'h3;
                        default:alu_a_bypass <= 3'h0;
                    endcase
                end else if(mem_ins[32] && wreg_valid[`MEM] && wreg[`MEM]==id_ins`RS) begin
                    case(mem_ins`OPCODE)
                        r_type, addi, andi, ori, xori, slti, addiu, sltiu:
                                alu_a_bypass <= 3'h4;
                        jalr:   alu_a_bypass <= 3'h5;
                        lw:     alu_a_bypass <= 3'h7;
                        lui:    alu_a_bypass <= 3'h6;
                        default:alu_a_bypass <= 3'h0;
                    endcase
                end else alu_a_bypass <= 3'h0;
            end
            default: begin
                mem_sw <= 1'b0;
                ex_sw_src_ex <= 1'b0;
                alu_a_bypass_ex <= 1'b0;
                alu_b_bypass_ex <= 1'b0;
                id_beqbne_a <= 3'h0;
                id_beqbne_b <= 3'h0;
                ex_sw_src <= 3'h0;
                alu_a_bypass <= 3'h0;
                alu_b_bypass <= 3'h0;
                stall_sign <= 2'h0;
            end
        endcase
    end

    // debug control
	reg debug_step_prev;
	always @(posedge clk) begin
		debug_step_prev <= debug_step;
	end
	
	assign cpu_en = ~((debug_en) && ~(~debug_step_prev && debug_step));

endmodule
