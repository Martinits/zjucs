<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="kintex7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="bi(3:0)" />
        <signal name="ai(3:0)" />
        <signal name="bi(3)" />
        <signal name="bi(2)" />
        <signal name="bi(1)" />
        <signal name="bi(0)" />
        <signal name="ai(3)" />
        <signal name="ai(2)" />
        <signal name="ai(1)" />
        <signal name="ai(0)" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <signal name="XLXN_17" />
        <signal name="GP" />
        <signal name="GG" />
        <signal name="XLXN_22" />
        <signal name="XLXN_23" />
        <signal name="XLXN_24" />
        <signal name="XLXN_25" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_30" />
        <signal name="C0" />
        <signal name="s(3:0)" />
        <signal name="s(3)" />
        <signal name="s(1)" />
        <signal name="s(2)" />
        <signal name="s(0)" />
        <port polarity="Input" name="bi(3:0)" />
        <port polarity="Input" name="ai(3:0)" />
        <port polarity="Output" name="GP" />
        <port polarity="Output" name="GG" />
        <port polarity="Input" name="C0" />
        <port polarity="Output" name="s(3:0)" />
        <blockdef name="add">
            <timestamp>2019-11-12T2:48:42</timestamp>
            <rect width="256" x="64" y="-256" height="256" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-128" y2="-128" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
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
        <block symbolname="add" name="A3">
            <blockpin signalname="bi(3)" name="bi" />
            <blockpin signalname="ai(3)" name="ai" />
            <blockpin signalname="XLXN_15" name="ci" />
            <blockpin name="co" />
            <blockpin signalname="s(3)" name="si" />
            <blockpin signalname="XLXN_22" name="Gi" />
            <blockpin signalname="XLXN_23" name="Pi" />
        </block>
        <block symbolname="add" name="A2">
            <blockpin signalname="bi(2)" name="bi" />
            <blockpin signalname="ai(2)" name="ai" />
            <blockpin signalname="XLXN_16" name="ci" />
            <blockpin name="co" />
            <blockpin signalname="s(2)" name="si" />
            <blockpin signalname="XLXN_24" name="Gi" />
            <blockpin signalname="XLXN_25" name="Pi" />
        </block>
        <block symbolname="add" name="A1">
            <blockpin signalname="bi(1)" name="bi" />
            <blockpin signalname="ai(1)" name="ai" />
            <blockpin signalname="XLXN_17" name="ci" />
            <blockpin name="co" />
            <blockpin signalname="s(1)" name="si" />
            <blockpin signalname="XLXN_26" name="Gi" />
            <blockpin signalname="XLXN_27" name="Pi" />
        </block>
        <block symbolname="CLA" name="XLXI_5">
            <blockpin signalname="XLXN_26" name="G1" />
            <blockpin signalname="XLXN_22" name="G3" />
            <blockpin signalname="XLXN_25" name="P2" />
            <blockpin signalname="XLXN_24" name="G2" />
            <blockpin signalname="XLXN_23" name="P3" />
            <blockpin signalname="XLXN_27" name="P1" />
            <blockpin signalname="XLXN_28" name="G0" />
            <blockpin signalname="C0" name="Ci" />
            <blockpin signalname="XLXN_30" name="P0" />
            <blockpin signalname="XLXN_15" name="C3" />
            <blockpin signalname="XLXN_16" name="C2" />
            <blockpin signalname="XLXN_17" name="C1" />
            <blockpin signalname="GG" name="GG" />
            <blockpin signalname="GP" name="GP" />
        </block>
        <block symbolname="add" name="A0">
            <blockpin signalname="bi(0)" name="bi" />
            <blockpin signalname="ai(0)" name="ai" />
            <blockpin signalname="C0" name="ci" />
            <blockpin name="co" />
            <blockpin signalname="s(0)" name="si" />
            <blockpin signalname="XLXN_28" name="Gi" />
            <blockpin signalname="XLXN_30" name="Pi" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="912" y="592" name="A3" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial" attrname="InstName" x="144" y="-128" type="instance" />
        </instance>
        <instance x="912" y="1008" name="A2" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial" attrname="InstName" x="160" y="-128" type="instance" />
        </instance>
        <instance x="912" y="1392" name="A1" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial" attrname="InstName" x="160" y="-128" type="instance" />
        </instance>
        <branch name="bi(3:0)">
            <wire x2="752" y1="192" y2="192" x1="352" />
            <wire x2="752" y1="192" y2="368" x1="752" />
            <wire x2="752" y1="368" y2="784" x1="752" />
            <wire x2="752" y1="784" y2="1168" x1="752" />
            <wire x2="752" y1="1168" y2="1568" x1="752" />
        </branch>
        <branch name="ai(3:0)">
            <wire x2="592" y1="256" y2="256" x1="256" />
            <wire x2="592" y1="256" y2="464" x1="592" />
            <wire x2="592" y1="464" y2="880" x1="592" />
            <wire x2="592" y1="880" y2="1264" x1="592" />
            <wire x2="592" y1="1264" y2="1664" x1="592" />
        </branch>
        <iomarker fontsize="64" x="256" y="256" name="ai(3:0)" orien="R180" />
        <iomarker fontsize="64" x="352" y="192" name="bi(3:0)" orien="R180" />
        <bustap x2="848" y1="368" y2="368" x1="752" />
        <branch name="bi(3)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="880" y="368" type="branch" />
            <wire x2="880" y1="368" y2="368" x1="848" />
            <wire x2="912" y1="368" y2="368" x1="880" />
        </branch>
        <bustap x2="848" y1="784" y2="784" x1="752" />
        <branch name="bi(2)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="880" y="784" type="branch" />
            <wire x2="880" y1="784" y2="784" x1="848" />
            <wire x2="912" y1="784" y2="784" x1="880" />
        </branch>
        <bustap x2="848" y1="1168" y2="1168" x1="752" />
        <branch name="bi(1)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="880" y="1168" type="branch" />
            <wire x2="880" y1="1168" y2="1168" x1="848" />
            <wire x2="912" y1="1168" y2="1168" x1="880" />
        </branch>
        <bustap x2="848" y1="1568" y2="1568" x1="752" />
        <branch name="bi(0)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="872" y="1568" type="branch" />
            <wire x2="896" y1="1568" y2="1568" x1="848" />
        </branch>
        <bustap x2="688" y1="464" y2="464" x1="592" />
        <branch name="ai(3)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="800" y="464" type="branch" />
            <wire x2="800" y1="464" y2="464" x1="688" />
            <wire x2="912" y1="464" y2="464" x1="800" />
        </branch>
        <bustap x2="688" y1="880" y2="880" x1="592" />
        <branch name="ai(2)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="800" y="880" type="branch" />
            <wire x2="800" y1="880" y2="880" x1="688" />
            <wire x2="912" y1="880" y2="880" x1="800" />
        </branch>
        <bustap x2="688" y1="1264" y2="1264" x1="592" />
        <branch name="ai(1)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="800" y="1264" type="branch" />
            <wire x2="800" y1="1264" y2="1264" x1="688" />
            <wire x2="912" y1="1264" y2="1264" x1="800" />
        </branch>
        <bustap x2="688" y1="1664" y2="1664" x1="592" />
        <branch name="ai(0)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="792" y="1664" type="branch" />
            <wire x2="896" y1="1664" y2="1664" x1="688" />
        </branch>
        <instance x="1744" y="1088" name="XLXI_5" orien="R0">
        </instance>
        <branch name="XLXN_22">
            <wire x2="1520" y1="368" y2="368" x1="1296" />
            <wire x2="1520" y1="368" y2="544" x1="1520" />
            <wire x2="1744" y1="544" y2="544" x1="1520" />
        </branch>
        <branch name="XLXN_23">
            <wire x2="1504" y1="432" y2="432" x1="1296" />
            <wire x2="1504" y1="432" y2="608" x1="1504" />
            <wire x2="1744" y1="608" y2="608" x1="1504" />
        </branch>
        <branch name="XLXN_24">
            <wire x2="1520" y1="784" y2="784" x1="1296" />
            <wire x2="1520" y1="672" y2="784" x1="1520" />
            <wire x2="1744" y1="672" y2="672" x1="1520" />
        </branch>
        <branch name="XLXN_25">
            <wire x2="1536" y1="848" y2="848" x1="1296" />
            <wire x2="1536" y1="736" y2="848" x1="1536" />
            <wire x2="1744" y1="736" y2="736" x1="1536" />
        </branch>
        <branch name="XLXN_26">
            <wire x2="1552" y1="1168" y2="1168" x1="1296" />
            <wire x2="1552" y1="800" y2="1168" x1="1552" />
            <wire x2="1744" y1="800" y2="800" x1="1552" />
        </branch>
        <branch name="XLXN_27">
            <wire x2="1568" y1="1232" y2="1232" x1="1296" />
            <wire x2="1568" y1="864" y2="1232" x1="1568" />
            <wire x2="1744" y1="864" y2="864" x1="1568" />
        </branch>
        <branch name="XLXN_28">
            <wire x2="1584" y1="1568" y2="1568" x1="1280" />
            <wire x2="1584" y1="928" y2="1568" x1="1584" />
            <wire x2="1744" y1="928" y2="928" x1="1584" />
        </branch>
        <branch name="XLXN_30">
            <wire x2="1600" y1="1632" y2="1632" x1="1280" />
            <wire x2="1600" y1="992" y2="1632" x1="1600" />
            <wire x2="1744" y1="992" y2="992" x1="1600" />
        </branch>
        <branch name="C0">
            <wire x2="720" y1="1760" y2="1760" x1="656" />
            <wire x2="896" y1="1760" y2="1760" x1="720" />
            <wire x2="720" y1="1760" y2="1840" x1="720" />
            <wire x2="1744" y1="1840" y2="1840" x1="720" />
            <wire x2="1744" y1="1056" y2="1840" x1="1744" />
        </branch>
        <iomarker fontsize="64" x="656" y="1760" name="C0" orien="R180" />
        <iomarker fontsize="64" x="2832" y="1520" name="s(3:0)" orien="R0" />
        <branch name="s(1)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2376" y="1488" type="branch" />
            <wire x2="1296" y1="1360" y2="1488" x1="1296" />
            <wire x2="2528" y1="1488" y2="1488" x1="1296" />
        </branch>
        <branch name="s(3)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2376" y="1248" type="branch" />
            <wire x2="1456" y1="560" y2="560" x1="1296" />
            <wire x2="1456" y1="560" y2="1248" x1="1456" />
            <wire x2="2528" y1="1248" y2="1248" x1="1456" />
        </branch>
        <branch name="s(2)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2376" y="1376" type="branch" />
            <wire x2="1408" y1="976" y2="976" x1="1296" />
            <wire x2="1408" y1="976" y2="1376" x1="1408" />
            <wire x2="2528" y1="1376" y2="1376" x1="1408" />
        </branch>
        <instance x="896" y="1792" name="A0" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial" attrname="InstName" x="160" y="-128" type="instance" />
        </instance>
        <branch name="s(0)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2376" y="1584" type="branch" />
            <wire x2="1920" y1="1760" y2="1760" x1="1280" />
            <wire x2="1920" y1="1584" y2="1760" x1="1920" />
            <wire x2="2528" y1="1584" y2="1584" x1="1920" />
        </branch>
        <bustap x2="2528" y1="1248" y2="1248" x1="2624" />
        <bustap x2="2528" y1="1376" y2="1376" x1="2624" />
        <bustap x2="2528" y1="1488" y2="1488" x1="2624" />
        <bustap x2="2528" y1="1584" y2="1584" x1="2624" />
        <branch name="s(3:0)">
            <wire x2="2624" y1="1248" y2="1376" x1="2624" />
            <wire x2="2624" y1="1376" y2="1488" x1="2624" />
            <wire x2="2624" y1="1488" y2="1520" x1="2624" />
            <wire x2="2832" y1="1520" y2="1520" x1="2624" />
            <wire x2="2624" y1="1520" y2="1584" x1="2624" />
        </branch>
        <iomarker fontsize="64" x="2576" y="928" name="GG" orien="R0" />
        <branch name="GG">
            <wire x2="2576" y1="928" y2="928" x1="2128" />
        </branch>
        <branch name="GP">
            <wire x2="2576" y1="1056" y2="1056" x1="2128" />
        </branch>
        <iomarker fontsize="64" x="2576" y="1056" name="GP" orien="R0" />
        <branch name="XLXN_15">
            <wire x2="704" y1="64" y2="560" x1="704" />
            <wire x2="912" y1="560" y2="560" x1="704" />
            <wire x2="2288" y1="64" y2="64" x1="704" />
            <wire x2="2288" y1="64" y2="544" x1="2288" />
            <wire x2="2288" y1="544" y2="544" x1="2128" />
        </branch>
        <branch name="XLXN_16">
            <wire x2="864" y1="112" y2="976" x1="864" />
            <wire x2="912" y1="976" y2="976" x1="864" />
            <wire x2="2240" y1="112" y2="112" x1="864" />
            <wire x2="2240" y1="112" y2="672" x1="2240" />
            <wire x2="2240" y1="672" y2="672" x1="2128" />
        </branch>
        <branch name="XLXN_17">
            <wire x2="896" y1="208" y2="1360" x1="896" />
            <wire x2="912" y1="1360" y2="1360" x1="896" />
            <wire x2="2192" y1="208" y2="208" x1="896" />
            <wire x2="2192" y1="208" y2="800" x1="2192" />
            <wire x2="2192" y1="800" y2="800" x1="2128" />
        </branch>
    </sheet>
</drawing>