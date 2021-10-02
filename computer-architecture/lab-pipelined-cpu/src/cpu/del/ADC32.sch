<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="kintex7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="a(31:0)" />
        <signal name="b(31:0)" />
        <signal name="a(31:28)" />
        <signal name="a(27:24)" />
        <signal name="a(23:20)" />
        <signal name="a(19:16)" />
        <signal name="a(15:12)" />
        <signal name="a(11:8)" />
        <signal name="a(7:4)" />
        <signal name="a(3:0)" />
        <signal name="b(31:28)" />
        <signal name="b(27:24)" />
        <signal name="b(23:20)" />
        <signal name="b(19:16)" />
        <signal name="b(15:12)" />
        <signal name="b(11:8)" />
        <signal name="b(7:4)" />
        <signal name="b(3:0)" />
        <signal name="XLXN_22" />
        <signal name="XLXN_23" />
        <signal name="XLXN_24" />
        <signal name="XLXN_30" />
        <signal name="XLXN_31" />
        <signal name="XLXN_32" />
        <signal name="XLXN_33" />
        <signal name="XLXN_34" />
        <signal name="XLXN_35" />
        <signal name="XLXN_36" />
        <signal name="XLXN_37" />
        <signal name="XLXN_38" />
        <signal name="XLXN_39" />
        <signal name="XLXN_40" />
        <signal name="XLXN_41" />
        <signal name="XLXN_42" />
        <signal name="XLXN_44" />
        <signal name="XLXN_45" />
        <signal name="XLXN_46" />
        <signal name="C0" />
        <signal name="XLXN_48" />
        <signal name="XLXN_49" />
        <signal name="XLXN_50" />
        <signal name="XLXN_51" />
        <signal name="XLXN_52" />
        <signal name="XLXN_53" />
        <signal name="XLXN_55" />
        <signal name="XLXN_56" />
        <signal name="XLXN_57" />
        <signal name="XLXN_58" />
        <signal name="XLXN_59" />
        <signal name="Co" />
        <signal name="s(31:28)" />
        <signal name="s(27:24)" />
        <signal name="s(23:20)" />
        <signal name="s(19:16)" />
        <signal name="s(15:12)" />
        <signal name="s(11:8)" />
        <signal name="s(7:4)" />
        <signal name="s(3:0)" />
        <signal name="s(31:0)" />
        <port polarity="Input" name="a(31:0)" />
        <port polarity="Input" name="b(31:0)" />
        <port polarity="Input" name="C0" />
        <port polarity="Output" name="Co" />
        <port polarity="Output" name="s(31:0)" />
        <blockdef name="add4b">
            <timestamp>2019-11-12T3:28:49</timestamp>
            <line x2="80" y1="-312" y2="-216" x1="80" />
            <line x2="144" y1="-216" y2="-184" x1="80" />
            <line x2="80" y1="-184" y2="-152" x1="144" />
            <line x2="80" y1="-152" y2="-72" x1="80" />
            <line x2="360" y1="-312" y2="-248" x1="80" />
            <line x2="80" y1="-72" y2="-56" x1="80" />
            <line x2="360" y1="-248" y2="-120" x1="360" />
            <line x2="16" y1="-112" y2="-112" style="linewidth:W" x1="80" />
            <line x2="16" y1="-256" y2="-256" style="linewidth:W" x1="80" />
            <line x2="208" y1="-336" y2="-280" x1="208" />
            <line x2="428" y1="-224" y2="-224" style="linewidth:W" x1="360" />
            <line x2="360" y1="-56" y2="-120" x1="80" />
            <line x2="252" y1="-96" y2="-96" x1="384" />
            <line x2="176" y1="-64" y2="-64" x1="380" />
            <line x2="176" y1="-64" y2="-76" x1="176" />
            <line x2="428" y1="-96" y2="-96" x1="384" />
            <line x2="432" y1="-64" y2="-64" x1="380" />
        </blockdef>
        <blockdef name="CLA">
            <timestamp>2019-11-12T3:18:31</timestamp>
            <rect width="256" x="64" y="-576" height="576" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <line x2="384" y1="-544" y2="-544" x1="320" />
            <line x2="384" y1="-416" y2="-416" x1="320" />
            <line x2="384" y1="-288" y2="-288" x1="320" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
            <line x2="0" y1="-544" y2="-544" x1="64" />
            <line x2="4" y1="-352" y2="-352" x1="68" />
            <line x2="4" y1="-416" y2="-416" x1="68" />
            <line x2="4" y1="-480" y2="-480" x1="68" />
            <line x2="4" y1="-224" y2="-224" x1="68" />
            <line x2="4" y1="-156" y2="-156" x1="68" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="4" y1="-96" y2="-96" x1="68" />
        </blockdef>
        <blockdef name="and2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="or2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
        </blockdef>
        <block symbolname="add4b" name="ADD7">
            <blockpin signalname="b(31:28)" name="bi(3:0)" />
            <blockpin signalname="a(31:28)" name="ai(3:0)" />
            <blockpin signalname="XLXN_22" name="C0" />
            <blockpin signalname="s(31:28)" name="s(3:0)" />
            <blockpin signalname="XLXN_30" name="GG" />
            <blockpin signalname="XLXN_31" name="GP" />
        </block>
        <block symbolname="add4b" name="ADD6">
            <blockpin signalname="b(27:24)" name="bi(3:0)" />
            <blockpin signalname="a(27:24)" name="ai(3:0)" />
            <blockpin signalname="XLXN_23" name="C0" />
            <blockpin signalname="s(27:24)" name="s(3:0)" />
            <blockpin signalname="XLXN_32" name="GG" />
            <blockpin signalname="XLXN_33" name="GP" />
        </block>
        <block symbolname="add4b" name="ADD5">
            <blockpin signalname="b(23:20)" name="bi(3:0)" />
            <blockpin signalname="a(23:20)" name="ai(3:0)" />
            <blockpin signalname="XLXN_24" name="C0" />
            <blockpin signalname="s(23:20)" name="s(3:0)" />
            <blockpin signalname="XLXN_34" name="GG" />
            <blockpin signalname="XLXN_35" name="GP" />
        </block>
        <block symbolname="add4b" name="ADD4">
            <blockpin signalname="b(19:16)" name="bi(3:0)" />
            <blockpin signalname="a(19:16)" name="ai(3:0)" />
            <blockpin signalname="XLXN_38" name="C0" />
            <blockpin signalname="s(19:16)" name="s(3:0)" />
            <blockpin signalname="XLXN_36" name="GG" />
            <blockpin signalname="XLXN_37" name="GP" />
        </block>
        <block symbolname="add4b" name="ADD1">
            <blockpin signalname="b(7:4)" name="bi(3:0)" />
            <blockpin signalname="a(7:4)" name="ai(3:0)" />
            <blockpin signalname="XLXN_50" name="C0" />
            <blockpin signalname="s(7:4)" name="s(3:0)" />
            <blockpin signalname="XLXN_56" name="GG" />
            <blockpin signalname="XLXN_57" name="GP" />
        </block>
        <block symbolname="add4b" name="ADD3">
            <blockpin signalname="b(15:12)" name="bi(3:0)" />
            <blockpin signalname="a(15:12)" name="ai(3:0)" />
            <blockpin signalname="XLXN_48" name="C0" />
            <blockpin signalname="s(15:12)" name="s(3:0)" />
            <blockpin signalname="XLXN_51" name="GG" />
            <blockpin signalname="XLXN_52" name="GP" />
        </block>
        <block symbolname="add4b" name="ADD2">
            <blockpin signalname="b(11:8)" name="bi(3:0)" />
            <blockpin signalname="a(11:8)" name="ai(3:0)" />
            <blockpin signalname="XLXN_49" name="C0" />
            <blockpin signalname="s(11:8)" name="s(3:0)" />
            <blockpin signalname="XLXN_53" name="GG" />
            <blockpin signalname="XLXN_55" name="GP" />
        </block>
        <block symbolname="add4b" name="ADD0">
            <blockpin signalname="b(3:0)" name="bi(3:0)" />
            <blockpin signalname="a(3:0)" name="ai(3:0)" />
            <blockpin signalname="C0" name="C0" />
            <blockpin signalname="s(3:0)" name="s(3:0)" />
            <blockpin signalname="XLXN_58" name="GG" />
            <blockpin signalname="XLXN_59" name="GP" />
        </block>
        <block symbolname="CLA" name="XLXI_10">
            <blockpin signalname="XLXN_56" name="G1" />
            <blockpin signalname="XLXN_51" name="G3" />
            <blockpin signalname="XLXN_55" name="P2" />
            <blockpin signalname="XLXN_53" name="G2" />
            <blockpin signalname="XLXN_52" name="P3" />
            <blockpin signalname="XLXN_57" name="P1" />
            <blockpin signalname="XLXN_58" name="G0" />
            <blockpin signalname="C0" name="Ci" />
            <blockpin signalname="XLXN_59" name="P0" />
            <blockpin signalname="XLXN_48" name="C3" />
            <blockpin signalname="XLXN_49" name="C2" />
            <blockpin signalname="XLXN_50" name="C1" />
            <blockpin signalname="XLXN_44" name="GG" />
            <blockpin signalname="XLXN_46" name="GP" />
        </block>
        <block symbolname="CLA" name="XLXI_11">
            <blockpin signalname="XLXN_34" name="G1" />
            <blockpin signalname="XLXN_30" name="G3" />
            <blockpin signalname="XLXN_33" name="P2" />
            <blockpin signalname="XLXN_32" name="G2" />
            <blockpin signalname="XLXN_31" name="P3" />
            <blockpin signalname="XLXN_35" name="P1" />
            <blockpin signalname="XLXN_36" name="G0" />
            <blockpin signalname="XLXN_38" name="Ci" />
            <blockpin signalname="XLXN_37" name="P0" />
            <blockpin signalname="XLXN_22" name="C3" />
            <blockpin signalname="XLXN_23" name="C2" />
            <blockpin signalname="XLXN_24" name="C1" />
            <blockpin signalname="XLXN_41" name="GG" />
            <blockpin signalname="XLXN_40" name="GP" />
        </block>
        <block symbolname="and2" name="XLXI_12">
            <blockpin signalname="XLXN_38" name="I0" />
            <blockpin signalname="XLXN_40" name="I1" />
            <blockpin signalname="XLXN_42" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_13">
            <blockpin signalname="XLXN_42" name="I0" />
            <blockpin signalname="XLXN_41" name="I1" />
            <blockpin signalname="Co" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_14">
            <blockpin signalname="C0" name="I0" />
            <blockpin signalname="XLXN_46" name="I1" />
            <blockpin signalname="XLXN_45" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_15">
            <blockpin signalname="XLXN_45" name="I0" />
            <blockpin signalname="XLXN_44" name="I1" />
            <blockpin signalname="XLXN_38" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="5440" height="7040">
        <instance x="1584" y="1072" name="ADD6" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial" attrname="InstName" x="272" y="-304" type="instance" />
        </instance>
        <instance x="1584" y="1568" name="ADD5" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial" attrname="InstName" x="288" y="-304" type="instance" />
        </instance>
        <instance x="1584" y="2128" name="ADD4" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial" attrname="InstName" x="288" y="-304" type="instance" />
        </instance>
        <instance x="1584" y="2736" name="ADD3" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial" attrname="InstName" x="272" y="-304" type="instance" />
        </instance>
        <instance x="1584" y="3360" name="ADD2" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial" attrname="InstName" x="272" y="-304" type="instance" />
        </instance>
        <instance x="1584" y="3888" name="ADD1" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial" attrname="InstName" x="288" y="-304" type="instance" />
        </instance>
        <instance x="1584" y="4528" name="ADD0" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial" attrname="InstName" x="304" y="-304" type="instance" />
        </instance>
        <instance x="3008" y="3744" name="XLXI_10" orien="R0">
        </instance>
        <instance x="2992" y="1520" name="XLXI_11" orien="R0">
        </instance>
        <branch name="a(31:0)">
            <wire x2="1424" y1="176" y2="176" x1="1024" />
            <wire x2="1424" y1="176" y2="288" x1="1424" />
            <wire x2="1424" y1="288" y2="816" x1="1424" />
            <wire x2="1424" y1="816" y2="1312" x1="1424" />
            <wire x2="1424" y1="1312" y2="1872" x1="1424" />
            <wire x2="1424" y1="1872" y2="2480" x1="1424" />
            <wire x2="1424" y1="2480" y2="3104" x1="1424" />
            <wire x2="1424" y1="3104" y2="3632" x1="1424" />
            <wire x2="1424" y1="3632" y2="4272" x1="1424" />
        </branch>
        <branch name="b(31:0)">
            <wire x2="1232" y1="272" y2="272" x1="1024" />
            <wire x2="1232" y1="272" y2="432" x1="1232" />
            <wire x2="1232" y1="432" y2="960" x1="1232" />
            <wire x2="1232" y1="960" y2="1456" x1="1232" />
            <wire x2="1232" y1="1456" y2="2016" x1="1232" />
            <wire x2="1232" y1="2016" y2="2624" x1="1232" />
            <wire x2="1232" y1="2624" y2="3248" x1="1232" />
            <wire x2="1232" y1="3248" y2="3776" x1="1232" />
            <wire x2="1232" y1="3776" y2="4416" x1="1232" />
        </branch>
        <iomarker fontsize="64" x="1024" y="176" name="a(31:0)" orien="R180" />
        <iomarker fontsize="64" x="1024" y="272" name="b(31:0)" orien="R180" />
        <bustap x2="1520" y1="288" y2="288" x1="1424" />
        <bustap x2="1520" y1="816" y2="816" x1="1424" />
        <branch name="a(27:24)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1560" y="816" type="branch" />
            <wire x2="1560" y1="816" y2="816" x1="1520" />
            <wire x2="1600" y1="816" y2="816" x1="1560" />
        </branch>
        <bustap x2="1520" y1="1312" y2="1312" x1="1424" />
        <branch name="a(23:20)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1560" y="1312" type="branch" />
            <wire x2="1560" y1="1312" y2="1312" x1="1520" />
            <wire x2="1600" y1="1312" y2="1312" x1="1560" />
        </branch>
        <bustap x2="1520" y1="1872" y2="1872" x1="1424" />
        <branch name="a(19:16)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1560" y="1872" type="branch" />
            <wire x2="1560" y1="1872" y2="1872" x1="1520" />
            <wire x2="1600" y1="1872" y2="1872" x1="1560" />
        </branch>
        <bustap x2="1520" y1="2480" y2="2480" x1="1424" />
        <branch name="a(15:12)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1560" y="2480" type="branch" />
            <wire x2="1560" y1="2480" y2="2480" x1="1520" />
            <wire x2="1600" y1="2480" y2="2480" x1="1560" />
        </branch>
        <bustap x2="1520" y1="3104" y2="3104" x1="1424" />
        <branch name="a(11:8)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1560" y="3104" type="branch" />
            <wire x2="1560" y1="3104" y2="3104" x1="1520" />
            <wire x2="1600" y1="3104" y2="3104" x1="1560" />
        </branch>
        <bustap x2="1520" y1="3632" y2="3632" x1="1424" />
        <branch name="a(7:4)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1560" y="3632" type="branch" />
            <wire x2="1560" y1="3632" y2="3632" x1="1520" />
            <wire x2="1600" y1="3632" y2="3632" x1="1560" />
        </branch>
        <bustap x2="1520" y1="4272" y2="4272" x1="1424" />
        <branch name="a(3:0)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1560" y="4272" type="branch" />
            <wire x2="1560" y1="4272" y2="4272" x1="1520" />
            <wire x2="1600" y1="4272" y2="4272" x1="1560" />
        </branch>
        <bustap x2="1328" y1="432" y2="432" x1="1232" />
        <bustap x2="1328" y1="960" y2="960" x1="1232" />
        <branch name="b(27:24)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1464" y="960" type="branch" />
            <wire x2="1464" y1="960" y2="960" x1="1328" />
            <wire x2="1600" y1="960" y2="960" x1="1464" />
        </branch>
        <bustap x2="1328" y1="1456" y2="1456" x1="1232" />
        <branch name="b(23:20)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1464" y="1456" type="branch" />
            <wire x2="1464" y1="1456" y2="1456" x1="1328" />
            <wire x2="1600" y1="1456" y2="1456" x1="1464" />
        </branch>
        <bustap x2="1328" y1="2016" y2="2016" x1="1232" />
        <branch name="b(19:16)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1464" y="2016" type="branch" />
            <wire x2="1464" y1="2016" y2="2016" x1="1328" />
            <wire x2="1600" y1="2016" y2="2016" x1="1464" />
        </branch>
        <bustap x2="1328" y1="2624" y2="2624" x1="1232" />
        <branch name="b(15:12)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1464" y="2624" type="branch" />
            <wire x2="1464" y1="2624" y2="2624" x1="1328" />
            <wire x2="1600" y1="2624" y2="2624" x1="1464" />
        </branch>
        <bustap x2="1328" y1="3248" y2="3248" x1="1232" />
        <branch name="b(11:8)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1464" y="3248" type="branch" />
            <wire x2="1464" y1="3248" y2="3248" x1="1328" />
            <wire x2="1600" y1="3248" y2="3248" x1="1464" />
        </branch>
        <bustap x2="1328" y1="3776" y2="3776" x1="1232" />
        <branch name="b(7:4)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1464" y="3776" type="branch" />
            <wire x2="1464" y1="3776" y2="3776" x1="1328" />
            <wire x2="1600" y1="3776" y2="3776" x1="1464" />
        </branch>
        <bustap x2="1328" y1="4416" y2="4416" x1="1232" />
        <branch name="b(3:0)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1464" y="4416" type="branch" />
            <wire x2="1464" y1="4416" y2="4416" x1="1328" />
            <wire x2="1600" y1="4416" y2="4416" x1="1464" />
        </branch>
        <branch name="XLXN_23">
            <wire x2="1792" y1="688" y2="736" x1="1792" />
            <wire x2="3424" y1="688" y2="688" x1="1792" />
            <wire x2="3424" y1="688" y2="1104" x1="3424" />
            <wire x2="3424" y1="1104" y2="1104" x1="3376" />
        </branch>
        <branch name="XLXN_24">
            <wire x2="1792" y1="1168" y2="1232" x1="1792" />
            <wire x2="2080" y1="1168" y2="1168" x1="1792" />
            <wire x2="2080" y1="880" y2="1168" x1="2080" />
            <wire x2="3408" y1="880" y2="880" x1="2080" />
            <wire x2="3408" y1="880" y2="1232" x1="3408" />
            <wire x2="3408" y1="1232" y2="1232" x1="3376" />
        </branch>
        <branch name="XLXN_22">
            <wire x2="3440" y1="128" y2="128" x1="1792" />
            <wire x2="3440" y1="128" y2="976" x1="3440" />
            <wire x2="1792" y1="128" y2="208" x1="1792" />
            <wire x2="3440" y1="976" y2="976" x1="3376" />
        </branch>
        <branch name="b(31:28)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1464" y="432" type="branch" />
            <wire x2="1464" y1="432" y2="432" x1="1328" />
            <wire x2="1600" y1="432" y2="432" x1="1464" />
        </branch>
        <branch name="a(31:28)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1560" y="288" type="branch" />
            <wire x2="1560" y1="288" y2="288" x1="1520" />
            <wire x2="1600" y1="288" y2="288" x1="1560" />
        </branch>
        <instance x="1584" y="544" name="ADD7" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial" attrname="InstName" x="288" y="-304" type="instance" />
        </instance>
        <branch name="XLXN_30">
            <wire x2="2496" y1="448" y2="448" x1="2016" />
            <wire x2="2496" y1="448" y2="976" x1="2496" />
            <wire x2="2992" y1="976" y2="976" x1="2496" />
        </branch>
        <branch name="XLXN_31">
            <wire x2="2480" y1="480" y2="480" x1="2016" />
            <wire x2="2480" y1="480" y2="1040" x1="2480" />
            <wire x2="2992" y1="1040" y2="1040" x1="2480" />
        </branch>
        <branch name="XLXN_32">
            <wire x2="2464" y1="976" y2="976" x1="2016" />
            <wire x2="2464" y1="976" y2="1104" x1="2464" />
            <wire x2="2992" y1="1104" y2="1104" x1="2464" />
        </branch>
        <branch name="XLXN_33">
            <wire x2="2448" y1="1008" y2="1008" x1="2016" />
            <wire x2="2448" y1="1008" y2="1168" x1="2448" />
            <wire x2="2992" y1="1168" y2="1168" x1="2448" />
        </branch>
        <branch name="XLXN_34">
            <wire x2="2496" y1="1472" y2="1472" x1="2016" />
            <wire x2="2496" y1="1232" y2="1472" x1="2496" />
            <wire x2="2992" y1="1232" y2="1232" x1="2496" />
        </branch>
        <branch name="XLXN_35">
            <wire x2="2512" y1="1504" y2="1504" x1="2016" />
            <wire x2="2512" y1="1296" y2="1504" x1="2512" />
            <wire x2="2992" y1="1296" y2="1296" x1="2512" />
        </branch>
        <branch name="XLXN_36">
            <wire x2="2528" y1="2032" y2="2032" x1="2016" />
            <wire x2="2528" y1="1360" y2="2032" x1="2528" />
            <wire x2="2992" y1="1360" y2="1360" x1="2528" />
        </branch>
        <branch name="XLXN_37">
            <wire x2="2544" y1="2064" y2="2064" x1="2016" />
            <wire x2="2544" y1="1424" y2="2064" x1="2544" />
            <wire x2="2992" y1="1424" y2="1424" x1="2544" />
        </branch>
        <branch name="XLXN_38">
            <wire x2="1792" y1="1712" y2="1792" x1="1792" />
            <wire x2="2992" y1="1712" y2="1712" x1="1792" />
            <wire x2="3520" y1="1712" y2="1712" x1="2992" />
            <wire x2="2992" y1="1712" y2="3040" x1="2992" />
            <wire x2="4048" y1="3040" y2="3040" x1="2992" />
            <wire x2="4048" y1="3040" y2="3616" x1="4048" />
            <wire x2="2992" y1="1488" y2="1712" x1="2992" />
            <wire x2="4048" y1="3616" y2="3616" x1="3984" />
        </branch>
        <instance x="3888" y="1488" name="XLXI_13" orien="R0" />
        <branch name="XLXN_41">
            <wire x2="3888" y1="1360" y2="1360" x1="3376" />
        </branch>
        <branch name="XLXN_42">
            <wire x2="3872" y1="1680" y2="1680" x1="3776" />
            <wire x2="3888" y1="1424" y2="1424" x1="3872" />
            <wire x2="3872" y1="1424" y2="1680" x1="3872" />
        </branch>
        <instance x="3520" y="1776" name="XLXI_12" orien="R0" />
        <branch name="XLXN_40">
            <wire x2="3392" y1="1488" y2="1488" x1="3376" />
            <wire x2="3392" y1="1488" y2="1648" x1="3392" />
            <wire x2="3520" y1="1648" y2="1648" x1="3392" />
        </branch>
        <instance x="3584" y="3984" name="XLXI_14" orien="R0" />
        <instance x="3728" y="3712" name="XLXI_15" orien="R0" />
        <branch name="XLXN_44">
            <wire x2="3728" y1="3584" y2="3584" x1="3392" />
        </branch>
        <branch name="XLXN_45">
            <wire x2="3728" y1="3648" y2="3648" x1="3664" />
            <wire x2="3664" y1="3648" y2="3744" x1="3664" />
            <wire x2="3904" y1="3744" y2="3744" x1="3664" />
            <wire x2="3904" y1="3744" y2="3888" x1="3904" />
            <wire x2="3904" y1="3888" y2="3888" x1="3840" />
        </branch>
        <branch name="XLXN_46">
            <wire x2="3488" y1="3712" y2="3712" x1="3392" />
            <wire x2="3488" y1="3712" y2="3856" x1="3488" />
            <wire x2="3584" y1="3856" y2="3856" x1="3488" />
        </branch>
        <branch name="C0">
            <wire x2="1792" y1="3920" y2="3920" x1="1040" />
            <wire x2="2928" y1="3920" y2="3920" x1="1792" />
            <wire x2="3584" y1="3920" y2="3920" x1="2928" />
            <wire x2="1792" y1="3920" y2="4192" x1="1792" />
            <wire x2="3008" y1="3712" y2="3712" x1="2928" />
            <wire x2="2928" y1="3712" y2="3920" x1="2928" />
        </branch>
        <branch name="XLXN_48">
            <wire x2="1792" y1="2320" y2="2400" x1="1792" />
            <wire x2="3504" y1="2320" y2="2320" x1="1792" />
            <wire x2="3504" y1="2320" y2="3200" x1="3504" />
            <wire x2="3504" y1="3200" y2="3200" x1="3392" />
        </branch>
        <branch name="XLXN_49">
            <wire x2="1792" y1="2944" y2="3024" x1="1792" />
            <wire x2="3440" y1="2944" y2="2944" x1="1792" />
            <wire x2="3440" y1="2944" y2="3328" x1="3440" />
            <wire x2="3440" y1="3328" y2="3328" x1="3392" />
        </branch>
        <branch name="XLXN_50">
            <wire x2="1792" y1="3488" y2="3552" x1="1792" />
            <wire x2="2160" y1="3488" y2="3488" x1="1792" />
            <wire x2="3472" y1="2896" y2="2896" x1="2160" />
            <wire x2="3472" y1="2896" y2="3456" x1="3472" />
            <wire x2="2160" y1="2896" y2="3488" x1="2160" />
            <wire x2="3472" y1="3456" y2="3456" x1="3392" />
        </branch>
        <branch name="XLXN_51">
            <wire x2="2512" y1="2640" y2="2640" x1="2016" />
            <wire x2="2512" y1="2640" y2="3200" x1="2512" />
            <wire x2="3008" y1="3200" y2="3200" x1="2512" />
        </branch>
        <branch name="XLXN_52">
            <wire x2="2496" y1="2672" y2="2672" x1="2016" />
            <wire x2="2496" y1="2672" y2="3264" x1="2496" />
            <wire x2="3008" y1="3264" y2="3264" x1="2496" />
        </branch>
        <branch name="XLXN_53">
            <wire x2="2480" y1="3264" y2="3264" x1="2016" />
            <wire x2="2480" y1="3264" y2="3328" x1="2480" />
            <wire x2="3008" y1="3328" y2="3328" x1="2480" />
        </branch>
        <branch name="XLXN_55">
            <wire x2="2016" y1="3296" y2="3392" x1="2016" />
            <wire x2="3008" y1="3392" y2="3392" x1="2016" />
        </branch>
        <branch name="XLXN_56">
            <wire x2="2512" y1="3792" y2="3792" x1="2016" />
            <wire x2="2512" y1="3456" y2="3792" x1="2512" />
            <wire x2="3008" y1="3456" y2="3456" x1="2512" />
        </branch>
        <branch name="XLXN_57">
            <wire x2="2528" y1="3824" y2="3824" x1="2016" />
            <wire x2="2528" y1="3520" y2="3824" x1="2528" />
            <wire x2="3008" y1="3520" y2="3520" x1="2528" />
        </branch>
        <branch name="XLXN_58">
            <wire x2="2544" y1="4432" y2="4432" x1="2016" />
            <wire x2="2544" y1="3584" y2="4432" x1="2544" />
            <wire x2="3008" y1="3584" y2="3584" x1="2544" />
        </branch>
        <branch name="XLXN_59">
            <wire x2="2560" y1="4464" y2="4464" x1="2016" />
            <wire x2="2560" y1="3648" y2="4464" x1="2560" />
            <wire x2="3008" y1="3648" y2="3648" x1="2560" />
        </branch>
        <iomarker fontsize="64" x="1040" y="3920" name="C0" orien="R180" />
        <branch name="Co">
            <wire x2="4176" y1="1392" y2="1392" x1="4144" />
        </branch>
        <iomarker fontsize="60" x="4176" y="1392" name="Co" orien="R0" />
        <branch name="s(31:28)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="4256" y="1840" type="branch" />
            <wire x2="2784" y1="320" y2="320" x1="2016" />
            <wire x2="2784" y1="320" y2="1840" x1="2784" />
            <wire x2="4256" y1="1840" y2="1840" x1="2784" />
            <wire x2="4384" y1="1840" y2="1840" x1="4256" />
        </branch>
        <branch name="s(27:24)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="4256" y="1904" type="branch" />
            <wire x2="2768" y1="848" y2="848" x1="2016" />
            <wire x2="2768" y1="848" y2="1904" x1="2768" />
            <wire x2="4128" y1="1904" y2="1904" x1="2768" />
            <wire x2="4256" y1="1904" y2="1904" x1="4128" />
            <wire x2="4384" y1="1904" y2="1904" x1="4256" />
        </branch>
        <branch name="s(23:20)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="4256" y="1968" type="branch" />
            <wire x2="2752" y1="1344" y2="1344" x1="2016" />
            <wire x2="2752" y1="1344" y2="1968" x1="2752" />
            <wire x2="4128" y1="1968" y2="1968" x1="2752" />
            <wire x2="4256" y1="1968" y2="1968" x1="4128" />
            <wire x2="4384" y1="1968" y2="1968" x1="4256" />
        </branch>
        <branch name="s(19:16)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="4256" y="2032" type="branch" />
            <wire x2="2576" y1="1904" y2="1904" x1="2016" />
            <wire x2="2576" y1="1904" y2="2032" x1="2576" />
            <wire x2="4128" y1="2032" y2="2032" x1="2576" />
            <wire x2="4256" y1="2032" y2="2032" x1="4128" />
            <wire x2="4384" y1="2032" y2="2032" x1="4256" />
        </branch>
        <branch name="s(15:12)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="4256" y="2096" type="branch" />
            <wire x2="4128" y1="2096" y2="2096" x1="2016" />
            <wire x2="4256" y1="2096" y2="2096" x1="4128" />
            <wire x2="4384" y1="2096" y2="2096" x1="4256" />
            <wire x2="2016" y1="2096" y2="2512" x1="2016" />
        </branch>
        <branch name="s(11:8)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="4256" y="2160" type="branch" />
            <wire x2="2096" y1="3136" y2="3136" x1="2016" />
            <wire x2="2096" y1="2160" y2="3136" x1="2096" />
            <wire x2="4128" y1="2160" y2="2160" x1="2096" />
            <wire x2="4256" y1="2160" y2="2160" x1="4128" />
            <wire x2="4384" y1="2160" y2="2160" x1="4256" />
        </branch>
        <branch name="s(7:4)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="4256" y="2224" type="branch" />
            <wire x2="2208" y1="3664" y2="3664" x1="2016" />
            <wire x2="2208" y1="2224" y2="3664" x1="2208" />
            <wire x2="4128" y1="2224" y2="2224" x1="2208" />
            <wire x2="4256" y1="2224" y2="2224" x1="4128" />
            <wire x2="4384" y1="2224" y2="2224" x1="4256" />
        </branch>
        <branch name="s(3:0)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="4256" y="2288" type="branch" />
            <wire x2="2336" y1="4304" y2="4304" x1="2016" />
            <wire x2="2336" y1="2288" y2="4304" x1="2336" />
            <wire x2="4128" y1="2288" y2="2288" x1="2336" />
            <wire x2="4256" y1="2288" y2="2288" x1="4128" />
            <wire x2="4384" y1="2288" y2="2288" x1="4256" />
        </branch>
        <branch name="s(31:0)">
            <wire x2="4480" y1="1840" y2="1904" x1="4480" />
            <wire x2="4480" y1="1904" y2="1968" x1="4480" />
            <wire x2="4480" y1="1968" y2="2032" x1="4480" />
            <wire x2="4576" y1="2032" y2="2032" x1="4480" />
            <wire x2="4480" y1="2032" y2="2096" x1="4480" />
            <wire x2="4480" y1="2096" y2="2160" x1="4480" />
            <wire x2="4480" y1="2160" y2="2224" x1="4480" />
            <wire x2="4480" y1="2224" y2="2288" x1="4480" />
        </branch>
        <iomarker fontsize="64" x="4576" y="2032" name="s(31:0)" orien="R0" />
        <bustap x2="4384" y1="1840" y2="1840" x1="4480" />
        <bustap x2="4384" y1="1904" y2="1904" x1="4480" />
        <bustap x2="4384" y1="1968" y2="1968" x1="4480" />
        <bustap x2="4384" y1="2032" y2="2032" x1="4480" />
        <bustap x2="4384" y1="2096" y2="2096" x1="4480" />
        <bustap x2="4384" y1="2160" y2="2160" x1="4480" />
        <bustap x2="4384" y1="2224" y2="2224" x1="4480" />
        <bustap x2="4384" y1="2288" y2="2288" x1="4480" />
    </sheet>
</drawing>