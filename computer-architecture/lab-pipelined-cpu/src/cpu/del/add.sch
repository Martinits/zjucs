<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="kintex7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="bi" />
        <signal name="ai" />
        <signal name="XLXN_4" />
        <signal name="ci" />
        <signal name="XLXN_6" />
        <signal name="Pi" />
        <signal name="Gi" />
        <signal name="XLXN_9" />
        <signal name="co" />
        <signal name="si" />
        <signal name="XLXN_12" />
        <port polarity="Input" name="bi" />
        <port polarity="Input" name="ai" />
        <port polarity="Input" name="ci" />
        <port polarity="Output" name="Pi" />
        <port polarity="Output" name="Gi" />
        <port polarity="Output" name="co" />
        <port polarity="Output" name="si" />
        <blockdef name="xor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="60" y1="-128" y2="-128" x1="0" />
            <line x2="208" y1="-96" y2="-96" x1="256" />
            <arc ex="44" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <arc ex="64" ey="-144" sx="64" sy="-48" r="56" cx="32" cy="-96" />
            <line x2="64" y1="-144" y2="-144" x1="128" />
            <line x2="64" y1="-48" y2="-48" x1="128" />
            <arc ex="128" ey="-144" sx="208" sy="-96" r="88" cx="132" cy="-56" />
            <arc ex="208" ey="-96" sx="128" sy="-48" r="88" cx="132" cy="-136" />
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
        <block symbolname="xor2" name="XLXI_1">
            <blockpin signalname="bi" name="I0" />
            <blockpin signalname="ai" name="I1" />
            <blockpin signalname="Pi" name="O" />
        </block>
        <block symbolname="xor2" name="XLXI_2">
            <blockpin signalname="ci" name="I0" />
            <blockpin signalname="Pi" name="I1" />
            <blockpin signalname="si" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_3">
            <blockpin signalname="ai" name="I0" />
            <blockpin signalname="bi" name="I1" />
            <blockpin signalname="Gi" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_4">
            <blockpin signalname="Pi" name="I0" />
            <blockpin signalname="ci" name="I1" />
            <blockpin signalname="XLXN_9" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_5">
            <blockpin signalname="Gi" name="I0" />
            <blockpin signalname="XLXN_9" name="I1" />
            <blockpin signalname="co" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="912" y="656" name="XLXI_1" orien="R0" />
        <instance x="1424" y="688" name="XLXI_2" orien="R0" />
        <instance x="800" y="880" name="XLXI_3" orien="R0" />
        <instance x="1392" y="944" name="XLXI_4" orien="R0" />
        <instance x="1840" y="976" name="XLXI_5" orien="R0" />
        <branch name="bi">
            <wire x2="784" y1="592" y2="592" x1="496" />
            <wire x2="784" y1="592" y2="752" x1="784" />
            <wire x2="800" y1="752" y2="752" x1="784" />
            <wire x2="912" y1="592" y2="592" x1="784" />
        </branch>
        <branch name="ai">
            <wire x2="736" y1="528" y2="528" x1="496" />
            <wire x2="912" y1="528" y2="528" x1="736" />
            <wire x2="736" y1="528" y2="816" x1="736" />
            <wire x2="800" y1="816" y2="816" x1="736" />
        </branch>
        <branch name="ci">
            <wire x2="1280" y1="400" y2="400" x1="496" />
            <wire x2="1280" y1="400" y2="624" x1="1280" />
            <wire x2="1424" y1="624" y2="624" x1="1280" />
            <wire x2="1280" y1="624" y2="816" x1="1280" />
            <wire x2="1392" y1="816" y2="816" x1="1280" />
        </branch>
        <branch name="Pi">
            <wire x2="1216" y1="560" y2="560" x1="1168" />
            <wire x2="1424" y1="560" y2="560" x1="1216" />
            <wire x2="1216" y1="560" y2="880" x1="1216" />
            <wire x2="1392" y1="880" y2="880" x1="1216" />
            <wire x2="1216" y1="880" y2="1264" x1="1216" />
            <wire x2="2432" y1="1264" y2="1264" x1="1216" />
        </branch>
        <branch name="Gi">
            <wire x2="1056" y1="784" y2="1056" x1="1056" />
            <wire x2="1840" y1="1056" y2="1056" x1="1056" />
            <wire x2="2400" y1="1056" y2="1056" x1="1840" />
            <wire x2="1840" y1="912" y2="1056" x1="1840" />
        </branch>
        <branch name="XLXN_9">
            <wire x2="1840" y1="848" y2="848" x1="1648" />
        </branch>
        <branch name="co">
            <wire x2="2416" y1="880" y2="880" x1="2096" />
        </branch>
        <branch name="si">
            <wire x2="2416" y1="592" y2="592" x1="1680" />
        </branch>
        <iomarker fontsize="64" x="496" y="400" name="ci" orien="R180" />
        <iomarker fontsize="64" x="496" y="528" name="ai" orien="R180" />
        <iomarker fontsize="64" x="496" y="592" name="bi" orien="R180" />
        <iomarker fontsize="44" x="2416" y="592" name="si" orien="R0" />
        <iomarker fontsize="64" x="2416" y="880" name="co" orien="R0" />
        <iomarker fontsize="64" x="2400" y="1056" name="Gi" orien="R0" />
        <iomarker fontsize="64" x="2432" y="1264" name="Pi" orien="R0" />
    </sheet>
</drawing>