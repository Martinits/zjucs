<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="kintex7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="Ci" />
        <signal name="XLXN_3" />
        <signal name="P0" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="G0" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="P1" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <signal name="XLXN_17" />
        <signal name="XLXN_18" />
        <signal name="XLXN_19" />
        <signal name="G1" />
        <signal name="XLXN_21" />
        <signal name="XLXN_22" />
        <signal name="XLXN_24" />
        <signal name="P2" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_29" />
        <signal name="XLXN_30" />
        <signal name="XLXN_31" />
        <signal name="XLXN_32" />
        <signal name="XLXN_33" />
        <signal name="XLXN_34" />
        <signal name="XLXN_35" />
        <signal name="XLXN_37" />
        <signal name="XLXN_38" />
        <signal name="G3" />
        <signal name="G2" />
        <signal name="XLXN_41" />
        <signal name="P3" />
        <signal name="XLXN_43" />
        <signal name="XLXN_44" />
        <signal name="GP" />
        <signal name="C1" />
        <signal name="C2" />
        <signal name="C3" />
        <signal name="GG" />
        <port polarity="Input" name="Ci" />
        <port polarity="Input" name="P0" />
        <port polarity="Input" name="G0" />
        <port polarity="Input" name="P1" />
        <port polarity="Input" name="G1" />
        <port polarity="Input" name="P2" />
        <port polarity="Input" name="G3" />
        <port polarity="Input" name="G2" />
        <port polarity="Input" name="P3" />
        <port polarity="Output" name="GP" />
        <port polarity="Output" name="C1" />
        <port polarity="Output" name="C2" />
        <port polarity="Output" name="C3" />
        <port polarity="Output" name="GG" />
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
        <blockdef name="and3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
        </blockdef>
        <blockdef name="and4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-112" y2="-112" x1="144" />
            <arc ex="144" ey="-208" sx="144" sy="-112" r="48" cx="144" cy="-160" />
            <line x2="144" y1="-208" y2="-208" x1="64" />
            <line x2="64" y1="-64" y2="-256" x1="64" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-64" y2="-64" x1="0" />
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
        <blockdef name="or3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
        </blockdef>
        <blockdef name="or4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="48" y1="-256" y2="-256" x1="0" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <arc ex="112" ey="-208" sx="192" sy="-160" r="88" cx="116" cy="-120" />
            <line x2="48" y1="-208" y2="-208" x1="112" />
            <line x2="48" y1="-112" y2="-112" x1="112" />
            <line x2="48" y1="-256" y2="-208" x1="48" />
            <line x2="48" y1="-64" y2="-112" x1="48" />
            <arc ex="48" ey="-208" sx="48" sy="-112" r="56" cx="16" cy="-160" />
            <arc ex="192" ey="-160" sx="112" sy="-112" r="88" cx="116" cy="-200" />
        </blockdef>
        <block symbolname="and2" name="XLXI_1">
            <blockpin signalname="P0" name="I0" />
            <blockpin signalname="Ci" name="I1" />
            <blockpin signalname="XLXN_18" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_2">
            <blockpin signalname="G0" name="I0" />
            <blockpin signalname="P1" name="I1" />
            <blockpin signalname="XLXN_17" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_3">
            <blockpin signalname="P2" name="I0" />
            <blockpin signalname="G1" name="I1" />
            <blockpin signalname="XLXN_32" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_4">
            <blockpin signalname="P3" name="I0" />
            <blockpin signalname="G2" name="I1" />
            <blockpin signalname="XLXN_35" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_5">
            <blockpin signalname="P1" name="I0" />
            <blockpin signalname="P0" name="I1" />
            <blockpin signalname="Ci" name="I2" />
            <blockpin signalname="XLXN_19" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_8">
            <blockpin signalname="P2" name="I0" />
            <blockpin signalname="P1" name="I1" />
            <blockpin signalname="G0" name="I2" />
            <blockpin signalname="XLXN_33" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_9">
            <blockpin signalname="P3" name="I0" />
            <blockpin signalname="P2" name="I1" />
            <blockpin signalname="G1" name="I2" />
            <blockpin signalname="XLXN_38" name="O" />
        </block>
        <block symbolname="and4" name="XLXI_10">
            <blockpin signalname="P3" name="I0" />
            <blockpin signalname="P2" name="I1" />
            <blockpin signalname="P1" name="I2" />
            <blockpin signalname="G0" name="I3" />
            <blockpin signalname="XLXN_37" name="O" />
        </block>
        <block symbolname="and4" name="XLXI_11">
            <blockpin signalname="P3" name="I0" />
            <blockpin signalname="P2" name="I1" />
            <blockpin signalname="P1" name="I2" />
            <blockpin signalname="P0" name="I3" />
            <blockpin signalname="GP" name="O" />
        </block>
        <block symbolname="and4" name="XLXI_12">
            <blockpin signalname="P2" name="I0" />
            <blockpin signalname="P1" name="I1" />
            <blockpin signalname="P0" name="I2" />
            <blockpin signalname="Ci" name="I3" />
            <blockpin signalname="XLXN_34" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_13">
            <blockpin signalname="G0" name="I0" />
            <blockpin signalname="XLXN_18" name="I1" />
            <blockpin signalname="C1" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_14">
            <blockpin signalname="G1" name="I0" />
            <blockpin signalname="XLXN_17" name="I1" />
            <blockpin signalname="XLXN_19" name="I2" />
            <blockpin signalname="C2" name="O" />
        </block>
        <block symbolname="or4" name="XLXI_15">
            <blockpin signalname="G2" name="I0" />
            <blockpin signalname="XLXN_32" name="I1" />
            <blockpin signalname="XLXN_33" name="I2" />
            <blockpin signalname="XLXN_34" name="I3" />
            <blockpin signalname="C3" name="O" />
        </block>
        <block symbolname="or4" name="XLXI_16">
            <blockpin signalname="G3" name="I0" />
            <blockpin signalname="XLXN_35" name="I1" />
            <blockpin signalname="XLXN_38" name="I2" />
            <blockpin signalname="XLXN_37" name="I3" />
            <blockpin signalname="GG" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1408" y="304" name="XLXI_1" orien="R0" />
        <instance x="1408" y="736" name="XLXI_2" orien="R0" />
        <instance x="1408" y="544" name="XLXI_5" orien="R0" />
        <instance x="1424" y="1024" name="XLXI_12" orien="R0" />
        <instance x="1424" y="1264" name="XLXI_8" orien="R0" />
        <instance x="1424" y="1520" name="XLXI_3" orien="R0" />
        <instance x="1424" y="1872" name="XLXI_11" orien="R0" />
        <instance x="1424" y="2176" name="XLXI_10" orien="R0" />
        <instance x="1424" y="2416" name="XLXI_9" orien="R0" />
        <instance x="1424" y="2624" name="XLXI_4" orien="R0" />
        <instance x="1888" y="768" name="XLXI_14" orien="R0" />
        <instance x="1904" y="1552" name="XLXI_15" orien="R0" />
        <instance x="1920" y="2672" name="XLXI_16" orien="R0" />
        <branch name="Ci">
            <wire x2="1056" y1="176" y2="176" x1="352" />
            <wire x2="1408" y1="176" y2="176" x1="1056" />
            <wire x2="1056" y1="176" y2="352" x1="1056" />
            <wire x2="1056" y1="352" y2="768" x1="1056" />
            <wire x2="1424" y1="768" y2="768" x1="1056" />
            <wire x2="1408" y1="352" y2="352" x1="1056" />
        </branch>
        <branch name="P0">
            <wire x2="1008" y1="240" y2="240" x1="352" />
            <wire x2="1408" y1="240" y2="240" x1="1008" />
            <wire x2="1008" y1="240" y2="416" x1="1008" />
            <wire x2="1408" y1="416" y2="416" x1="1008" />
            <wire x2="1008" y1="416" y2="832" x1="1008" />
            <wire x2="1424" y1="832" y2="832" x1="1008" />
            <wire x2="1008" y1="832" y2="1616" x1="1008" />
            <wire x2="1424" y1="1616" y2="1616" x1="1008" />
        </branch>
        <instance x="1872" y="336" name="XLXI_13" orien="R0" />
        <branch name="G0">
            <wire x2="928" y1="320" y2="320" x1="352" />
            <wire x2="1872" y1="320" y2="320" x1="928" />
            <wire x2="928" y1="320" y2="672" x1="928" />
            <wire x2="1408" y1="672" y2="672" x1="928" />
            <wire x2="928" y1="672" y2="1072" x1="928" />
            <wire x2="1424" y1="1072" y2="1072" x1="928" />
            <wire x2="928" y1="1072" y2="1920" x1="928" />
            <wire x2="1424" y1="1920" y2="1920" x1="928" />
            <wire x2="1872" y1="272" y2="320" x1="1872" />
        </branch>
        <branch name="P1">
            <wire x2="848" y1="480" y2="480" x1="368" />
            <wire x2="1408" y1="480" y2="480" x1="848" />
            <wire x2="848" y1="480" y2="608" x1="848" />
            <wire x2="1408" y1="608" y2="608" x1="848" />
            <wire x2="848" y1="608" y2="896" x1="848" />
            <wire x2="1424" y1="896" y2="896" x1="848" />
            <wire x2="848" y1="896" y2="1136" x1="848" />
            <wire x2="1424" y1="1136" y2="1136" x1="848" />
            <wire x2="848" y1="1136" y2="1680" x1="848" />
            <wire x2="1424" y1="1680" y2="1680" x1="848" />
            <wire x2="848" y1="1680" y2="1984" x1="848" />
            <wire x2="1424" y1="1984" y2="1984" x1="848" />
        </branch>
        <branch name="XLXN_17">
            <wire x2="1888" y1="640" y2="640" x1="1664" />
        </branch>
        <branch name="XLXN_18">
            <wire x2="1872" y1="208" y2="208" x1="1664" />
        </branch>
        <branch name="XLXN_19">
            <wire x2="1888" y1="416" y2="416" x1="1664" />
            <wire x2="1888" y1="416" y2="576" x1="1888" />
        </branch>
        <branch name="G1">
            <wire x2="768" y1="736" y2="736" x1="368" />
            <wire x2="1888" y1="736" y2="736" x1="768" />
            <wire x2="768" y1="736" y2="1392" x1="768" />
            <wire x2="1424" y1="1392" y2="1392" x1="768" />
            <wire x2="768" y1="1392" y2="2224" x1="768" />
            <wire x2="1424" y1="2224" y2="2224" x1="768" />
            <wire x2="1888" y1="704" y2="736" x1="1888" />
        </branch>
        <branch name="P2">
            <wire x2="688" y1="960" y2="960" x1="352" />
            <wire x2="1424" y1="960" y2="960" x1="688" />
            <wire x2="688" y1="960" y2="1200" x1="688" />
            <wire x2="1424" y1="1200" y2="1200" x1="688" />
            <wire x2="688" y1="1200" y2="1456" x1="688" />
            <wire x2="1424" y1="1456" y2="1456" x1="688" />
            <wire x2="688" y1="1456" y2="1744" x1="688" />
            <wire x2="1424" y1="1744" y2="1744" x1="688" />
            <wire x2="688" y1="1744" y2="2048" x1="688" />
            <wire x2="1424" y1="2048" y2="2048" x1="688" />
            <wire x2="688" y1="2048" y2="2288" x1="688" />
            <wire x2="1424" y1="2288" y2="2288" x1="688" />
        </branch>
        <branch name="XLXN_32">
            <wire x2="1904" y1="1424" y2="1424" x1="1680" />
        </branch>
        <branch name="XLXN_33">
            <wire x2="1792" y1="1136" y2="1136" x1="1680" />
            <wire x2="1792" y1="1136" y2="1360" x1="1792" />
            <wire x2="1904" y1="1360" y2="1360" x1="1792" />
        </branch>
        <branch name="XLXN_34">
            <wire x2="1904" y1="864" y2="864" x1="1680" />
            <wire x2="1904" y1="864" y2="1296" x1="1904" />
        </branch>
        <branch name="XLXN_35">
            <wire x2="1792" y1="2528" y2="2528" x1="1680" />
            <wire x2="1792" y1="2528" y2="2544" x1="1792" />
            <wire x2="1920" y1="2544" y2="2544" x1="1792" />
        </branch>
        <branch name="XLXN_37">
            <wire x2="1920" y1="2016" y2="2016" x1="1680" />
            <wire x2="1920" y1="2016" y2="2416" x1="1920" />
        </branch>
        <branch name="XLXN_38">
            <wire x2="1792" y1="2288" y2="2288" x1="1680" />
            <wire x2="1792" y1="2288" y2="2480" x1="1792" />
            <wire x2="1920" y1="2480" y2="2480" x1="1792" />
        </branch>
        <branch name="G3">
            <wire x2="1920" y1="2624" y2="2624" x1="320" />
            <wire x2="1920" y1="2608" y2="2624" x1="1920" />
        </branch>
        <branch name="G2">
            <wire x2="608" y1="1536" y2="1536" x1="320" />
            <wire x2="1904" y1="1536" y2="1536" x1="608" />
            <wire x2="608" y1="1536" y2="2496" x1="608" />
            <wire x2="1424" y1="2496" y2="2496" x1="608" />
            <wire x2="1904" y1="1488" y2="1536" x1="1904" />
        </branch>
        <branch name="P3">
            <wire x2="528" y1="1808" y2="1808" x1="336" />
            <wire x2="1424" y1="1808" y2="1808" x1="528" />
            <wire x2="528" y1="1808" y2="2112" x1="528" />
            <wire x2="1424" y1="2112" y2="2112" x1="528" />
            <wire x2="528" y1="2112" y2="2352" x1="528" />
            <wire x2="1424" y1="2352" y2="2352" x1="528" />
            <wire x2="528" y1="2352" y2="2560" x1="528" />
            <wire x2="1424" y1="2560" y2="2560" x1="528" />
        </branch>
        <iomarker fontsize="64" x="320" y="1536" name="G2" orien="R180" />
        <iomarker fontsize="64" x="336" y="1808" name="P3" orien="R180" />
        <iomarker fontsize="64" x="320" y="2624" name="G3" orien="R180" />
        <iomarker fontsize="64" x="368" y="736" name="G1" orien="R180" />
        <iomarker fontsize="64" x="352" y="960" name="P2" orien="R180" />
        <iomarker fontsize="64" x="352" y="320" name="G0" orien="R180" />
        <iomarker fontsize="64" x="352" y="240" name="P0" orien="R180" />
        <iomarker fontsize="64" x="352" y="176" name="Ci" orien="R180" />
        <iomarker fontsize="64" x="368" y="480" name="P1" orien="R180" />
        <branch name="GP">
            <wire x2="2176" y1="1712" y2="1712" x1="1680" />
        </branch>
        <branch name="C1">
            <wire x2="2160" y1="240" y2="240" x1="2128" />
        </branch>
        <iomarker fontsize="64" x="2160" y="240" name="C1" orien="R0" />
        <branch name="C2">
            <wire x2="2176" y1="640" y2="640" x1="2144" />
        </branch>
        <iomarker fontsize="64" x="2176" y="640" name="C2" orien="R0" />
        <branch name="C3">
            <wire x2="2192" y1="1392" y2="1392" x1="2160" />
        </branch>
        <iomarker fontsize="64" x="2192" y="1392" name="C3" orien="R0" />
        <iomarker fontsize="64" x="2176" y="1712" name="GP" orien="R0" />
        <branch name="GG">
            <wire x2="2208" y1="2512" y2="2512" x1="2176" />
        </branch>
        <iomarker fontsize="64" x="2208" y="2512" name="GG" orien="R0" />
    </sheet>
</drawing>