<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="kintex7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="clk" />
        <signal name="rst" />
        <signal name="ins_in(31:0)" />
        <signal name="data_in(31:0)" />
        <signal name="ins_addr_out(31:0)" />
        <signal name="data_addr_out(31:0)" />
        <signal name="data_out(31:0)" />
        <signal name="mem_write" />
        <signal name="mem_read" />
        <signal name="ins_read" />
        <signal name="debug_data(31:0)" />
        <signal name="debug_addr(5:0)" />
        <signal name="XLXN_36(32:0)" />
        <signal name="XLXN_37(32:0)" />
        <signal name="XLXN_38(32:0)" />
        <signal name="XLXN_39" />
        <signal name="XLXN_40" />
        <signal name="XLXN_41(35:0)" />
        <signal name="XLXN_42(3:0)" />
        <signal name="XLXN_43(3:0)" />
        <signal name="XLXN_44" />
        <signal name="debug_en" />
        <signal name="debug_step" />
        <signal name="XLXN_47(32:0)" />
        <port polarity="Input" name="clk" />
        <port polarity="Input" name="rst" />
        <port polarity="Input" name="ins_in(31:0)" />
        <port polarity="Input" name="data_in(31:0)" />
        <port polarity="Output" name="ins_addr_out(31:0)" />
        <port polarity="Output" name="data_addr_out(31:0)" />
        <port polarity="Output" name="data_out(31:0)" />
        <port polarity="Output" name="mem_write" />
        <port polarity="Output" name="mem_read" />
        <port polarity="Output" name="ins_read" />
        <port polarity="Output" name="debug_data(31:0)" />
        <port polarity="Input" name="debug_addr(5:0)" />
        <port polarity="Input" name="debug_en" />
        <port polarity="Input" name="debug_step" />
        <blockdef name="Datapath">
            <timestamp>2020-11-27T4:51:48</timestamp>
            <line x2="512" y1="-544" y2="-544" style="linewidth:W" x1="448" />
            <line x2="0" y1="-544" y2="-544" x1="64" />
            <line x2="0" y1="-480" y2="-480" x1="64" />
            <line x2="0" y1="-416" y2="-416" style="linewidth:W" x1="64" />
            <line x2="512" y1="-480" y2="-480" style="linewidth:W" x1="448" />
            <line x2="512" y1="-416" y2="-416" x1="448" />
            <line x2="512" y1="-352" y2="-352" style="linewidth:W" x1="448" />
            <line x2="512" y1="-288" y2="-288" x1="448" />
            <line x2="512" y1="-224" y2="-224" x1="448" />
            <line x2="512" y1="-160" y2="-160" x1="448" />
            <line x2="448" y1="-96" y2="-96" style="linewidth:W" x1="512" />
            <line x2="512" y1="-32" y2="-32" x1="448" />
            <rect width="384" x="64" y="-584" height="984" />
            <line x2="0" y1="32" y2="32" x1="64" />
            <line x2="0" y1="96" y2="96" style="linewidth:W" x1="64" />
            <line x2="0" y1="160" y2="160" style="linewidth:W" x1="64" />
            <line x2="0" y1="224" y2="224" style="linewidth:W" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="0" y1="288" y2="288" x1="64" />
            <line x2="0" y1="352" y2="352" style="linewidth:W" x1="64" />
            <line x2="0" y1="-352" y2="-352" style="linewidth:W" x1="64" />
            <line x2="0" y1="-224" y2="-224" style="linewidth:W" x1="64" />
            <line x2="0" y1="-160" y2="-160" style="linewidth:W" x1="64" />
            <line x2="0" y1="-96" y2="-96" style="linewidth:W" x1="64" />
            <line x2="64" y1="-288" y2="-288" style="linewidth:W" x1="0" />
        </blockdef>
        <blockdef name="Controller">
            <timestamp>2020-11-27T4:51:30</timestamp>
            <rect width="336" x="64" y="-320" height="648" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="400" y1="-288" y2="-288" style="linewidth:W" x1="464" />
            <line x2="464" y1="32" y2="32" x1="400" />
            <line x2="400" y1="-32" y2="-32" x1="464" />
            <line x2="464" y1="96" y2="96" style="linewidth:W" x1="400" />
            <line x2="464" y1="160" y2="160" style="linewidth:W" x1="400" />
            <line x2="464" y1="224" y2="224" style="linewidth:W" x1="400" />
            <line x2="464" y1="288" y2="288" x1="400" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="0" y1="32" y2="32" x1="64" />
            <line x2="400" y1="-224" y2="-224" style="linewidth:W" x1="464" />
            <line x2="400" y1="-160" y2="-160" style="linewidth:W" x1="464" />
            <line x2="400" y1="-96" y2="-96" style="linewidth:W" x1="464" />
        </blockdef>
        <block symbolname="Datapath" name="XLXI_2">
            <blockpin signalname="ins_addr_out(31:0)" name="ins_addr_out(31:0)" />
            <blockpin signalname="clk" name="clk" />
            <blockpin signalname="rst" name="rst" />
            <blockpin signalname="ins_in(31:0)" name="ins_in(31:0)" />
            <blockpin signalname="data_addr_out(31:0)" name="data_addr_out(31:0)" />
            <blockpin name="overflow" />
            <blockpin signalname="data_out(31:0)" name="data_out(31:0)" />
            <blockpin signalname="mem_write" name="mem_write" />
            <blockpin signalname="mem_read" name="mem_read" />
            <blockpin signalname="ins_read" name="ins_read" />
            <blockpin signalname="debug_data(31:0)" name="debug_data(31:0)" />
            <blockpin name="zero" />
            <blockpin signalname="XLXN_40" name="pc_write" />
            <blockpin signalname="XLXN_41(35:0)" name="ctrl_sig_in(35:0)" />
            <blockpin signalname="XLXN_42(3:0)" name="pipereg_we(3:0)" />
            <blockpin signalname="XLXN_43(3:0)" name="pipereg_zero(3:0)" />
            <blockpin signalname="XLXN_39" name="beqbne_equal" />
            <blockpin signalname="XLXN_44" name="cpu_en" />
            <blockpin signalname="debug_addr(5:0)" name="debug_addr(5:0)" />
            <blockpin signalname="data_in(31:0)" name="data_in(31:0)" />
            <blockpin signalname="XLXN_36(32:0)" name="ex_ins(32:0)" />
            <blockpin signalname="XLXN_37(32:0)" name="mem_ins(32:0)" />
            <blockpin signalname="XLXN_38(32:0)" name="wb_ins(32:0)" />
            <blockpin signalname="XLXN_47(32:0)" name="id_ins(32:0)" />
        </block>
        <block symbolname="Controller" name="XLXI_3">
            <blockpin signalname="clk" name="clk" />
            <blockpin signalname="rst" name="rst" />
            <blockpin signalname="XLXN_47(32:0)" name="id_ins(32:0)" />
            <blockpin signalname="XLXN_40" name="pc_write" />
            <blockpin signalname="XLXN_39" name="beqbne_equal" />
            <blockpin signalname="XLXN_41(35:0)" name="signals(35:0)" />
            <blockpin signalname="XLXN_42(3:0)" name="pipereg_we(3:0)" />
            <blockpin signalname="XLXN_43(3:0)" name="pipereg_zero(3:0)" />
            <blockpin signalname="XLXN_44" name="cpu_en" />
            <blockpin signalname="debug_en" name="debug_en" />
            <blockpin signalname="debug_step" name="debug_step" />
            <blockpin signalname="XLXN_36(32:0)" name="ex_ins(32:0)" />
            <blockpin signalname="XLXN_37(32:0)" name="mem_ins(32:0)" />
            <blockpin signalname="XLXN_38(32:0)" name="wb_ins(32:0)" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <iomarker fontsize="28" x="608" y="560" name="clk" orien="R180" />
        <iomarker fontsize="28" x="608" y="624" name="rst" orien="R180" />
        <branch name="data_in(31:0)">
            <wire x2="1632" y1="752" y2="752" x1="608" />
        </branch>
        <iomarker fontsize="28" x="608" y="688" name="ins_in(31:0)" orien="R180" />
        <iomarker fontsize="28" x="608" y="752" name="data_in(31:0)" orien="R180" />
        <branch name="ins_addr_out(31:0)">
            <wire x2="2176" y1="560" y2="560" x1="2144" />
        </branch>
        <iomarker fontsize="28" x="2176" y="560" name="ins_addr_out(31:0)" orien="R0" />
        <branch name="data_addr_out(31:0)">
            <wire x2="2176" y1="624" y2="624" x1="2144" />
        </branch>
        <iomarker fontsize="28" x="2176" y="624" name="data_addr_out(31:0)" orien="R0" />
        <branch name="data_out(31:0)">
            <wire x2="2176" y1="752" y2="752" x1="2144" />
        </branch>
        <iomarker fontsize="28" x="2176" y="752" name="data_out(31:0)" orien="R0" />
        <branch name="mem_write">
            <wire x2="2176" y1="816" y2="816" x1="2144" />
        </branch>
        <iomarker fontsize="28" x="2176" y="816" name="mem_write" orien="R0" />
        <branch name="mem_read">
            <wire x2="2176" y1="880" y2="880" x1="2144" />
        </branch>
        <iomarker fontsize="28" x="2176" y="880" name="mem_read" orien="R0" />
        <branch name="ins_read">
            <wire x2="2176" y1="944" y2="944" x1="2144" />
        </branch>
        <iomarker fontsize="28" x="2176" y="944" name="ins_read" orien="R0" />
        <branch name="debug_data(31:0)">
            <wire x2="2176" y1="1008" y2="1008" x1="2144" />
        </branch>
        <iomarker fontsize="28" x="2176" y="1008" name="debug_data(31:0)" orien="R0" />
        <instance x="912" y="1104" name="XLXI_3" orien="R0">
        </instance>
        <branch name="ins_in(31:0)">
            <wire x2="1632" y1="688" y2="688" x1="608" />
        </branch>
        <branch name="rst">
            <wire x2="752" y1="624" y2="624" x1="608" />
            <wire x2="752" y1="624" y2="880" x1="752" />
            <wire x2="912" y1="880" y2="880" x1="752" />
            <wire x2="1632" y1="624" y2="624" x1="752" />
        </branch>
        <branch name="clk">
            <wire x2="832" y1="560" y2="560" x1="608" />
            <wire x2="832" y1="560" y2="816" x1="832" />
            <wire x2="912" y1="816" y2="816" x1="832" />
            <wire x2="1632" y1="560" y2="560" x1="832" />
        </branch>
        <instance x="1632" y="1104" name="XLXI_2" orien="R0">
        </instance>
        <branch name="debug_addr(5:0)">
            <wire x2="1632" y1="1456" y2="1456" x1="1584" />
        </branch>
        <iomarker fontsize="28" x="1584" y="1456" name="debug_addr(5:0)" orien="R180" />
        <branch name="XLXN_36(32:0)">
            <wire x2="1632" y1="880" y2="880" x1="1376" />
        </branch>
        <branch name="XLXN_37(32:0)">
            <wire x2="1632" y1="944" y2="944" x1="1376" />
        </branch>
        <branch name="XLXN_38(32:0)">
            <wire x2="1632" y1="1008" y2="1008" x1="1376" />
        </branch>
        <branch name="XLXN_39">
            <wire x2="1632" y1="1072" y2="1072" x1="1376" />
        </branch>
        <branch name="XLXN_40">
            <wire x2="1632" y1="1136" y2="1136" x1="1376" />
        </branch>
        <branch name="XLXN_41(35:0)">
            <wire x2="1632" y1="1200" y2="1200" x1="1376" />
        </branch>
        <branch name="XLXN_42(3:0)">
            <wire x2="1632" y1="1264" y2="1264" x1="1376" />
        </branch>
        <branch name="XLXN_43(3:0)">
            <wire x2="1632" y1="1328" y2="1328" x1="1376" />
        </branch>
        <branch name="XLXN_44">
            <wire x2="1632" y1="1392" y2="1392" x1="1376" />
        </branch>
        <branch name="debug_en">
            <wire x2="912" y1="1072" y2="1072" x1="880" />
        </branch>
        <branch name="debug_step">
            <wire x2="912" y1="1136" y2="1136" x1="880" />
        </branch>
        <iomarker fontsize="28" x="880" y="1072" name="debug_en" orien="R180" />
        <iomarker fontsize="28" x="880" y="1136" name="debug_step" orien="R180" />
        <branch name="XLXN_47(32:0)">
            <wire x2="1632" y1="816" y2="816" x1="1376" />
        </branch>
    </sheet>
</drawing>