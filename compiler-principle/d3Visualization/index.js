  //define a boundary
  var marge = {top:50, bottom:0, left:10, right:0};
    
  var svg = d3.select("svg");
  var width = svg.attr("width");
  var height = svg.attr("height");
  
  var g = svg.append("g")
      .attr("transform","translate("+marge.top+","+marge.left+")");
  
  var scale = svg.append("g")
      .attr("transform","translate("+marge.top+","+marge.left+")");
  //data
  var dataset = { "name" : "Program: hello", "children" : [ { "name" : "Routine", "children" : [ { "name" : "constListChildren", "children" : [  ] }, { "name" : "typeListChildren", "children" : [  ] }, { "name" : "varListChildren", "children" : [ { "name" : "VarDeclaration", "children" : [ { "name" : "idListChildren", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "ans" } ] } ] }, { "name" : "SysTypes", "children" : [ { "name" : "Integer" } ] } ] } ] }, { "name" : "routineListChildren", "children" : [ { "name" : "FuncDeclaration", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "gcd" } ] }, { "name" : "paraListChildren", "children" : [ { "name" : "Parameter", "children" : [ { "name" : "Boolean", "children" : [ { "name" : "false" } ] }, { "name" : "idListChildren", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "a" } ] }, { "name" : "Identifier", "children" : [ { "name" : "b" } ] } ] }, { "name" : "SysTypes", "children" : [ { "name" : "Integer" } ] } ] } ] }, { "name" : "SysTypes", "children" : [ { "name" : "Integer" } ] }, { "name" : "Routine", "children" : [ { "name" : "constListChildren", "children" : [  ] }, { "name" : "typeListChildren", "children" : [  ] }, { "name" : "varListChildren", "children" : [  ] }, { "name" : "routineListChildren", "children" : [  ] }, { "name" : "CompoundStmt", "children" : [ { "name" : "IfStmt", "children" : [ { "name" : "MathExpr", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "b" } ] }, { "name" : "=" }, { "name" : "Integer", "children" : [ { "name" : "0" } ] } ] }, { "name" : "CompoundStmt", "children" : [ { "name" : "AssignStmt", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "gcd" } ] }, { "name" : "Identifier", "children" : [ { "name" : "a" } ] } ] } ] }, { "name" : "CompoundStmt", "children" : [ { "name" : "AssignStmt", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "gcd" } ] }, { "name" : "FuncCall", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "gcd" } ] },{ "name" : "args", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "b" } ] }, { "name" : "MathExpr", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "a" } ] }, { "name" : "%" }, { "name" : "Identifier", "children" : [ { "name" : "b" } ] } ] } ] } ] } ] } ] } ] } ] } ] } ] } ] }, { "name" : "CompoundStmt", "children" : [ { "name" : "AssignStmt", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "ans" } ] }, { "name" : "MathExpr", "children" : [ { "name" : "FuncCall", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "gcd" } ] },{ "name" : "args", "children" : [ { "name" : "Integer", "children" : [ { "name" : "9" } ] }, { "name" : "Integer", "children" : [ { "name" : "36" } ] } ] } ] }, { "name" : "*" }, { "name" : "FuncCall", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "gcd" } ] },{ "name" : "args", "children" : [ { "name" : "Integer", "children" : [ { "name" : "3" } ] }, { "name" : "Integer", "children" : [ { "name" : "6" } ] } ] } ] } ] } ] }, { "name" : "SysProcCall", "children" : [ { "name" : "writeln" },{ "name" : "args", "children" : [ { "name" : "Identifier", "children" : [ { "name" : "ans" } ] } ] }, { "name" : "SYS_PROC_WRITELN" } ] } ] } ] } ] }

  
  //create a hierarchy layout
  var hierarchyData = d3.hierarchy(dataset)
      .sum(function(d){
          return d.value;
      });
      
  //create a tree
  var tree = d3.tree()
      .size([width-400,height-200])
      .separation(function(a,b){
          return (a.parent==b.parent?1:2)/a.depth;
      })
  
  //init tree
  var treeData = tree(hierarchyData);
  console.log(treeData);
  //get node
  var nodes = treeData.descendants();
  var links = treeData.links();
  
  //output nodes and edges
  console.log(nodes);
  console.log(links);
  
  //create a Bezier curve generator
  // var Bezier_curve_generator = d3.linkVertical()
  //     .x(function(d) { return d.x; })
  //     .y(function(d) { return d.y; });

  var Bézier_curve_generator = d3.linkHorizontal()
      .x(function(d) { return d.y; })
      .y(function(d) { return d.x; });
      
  //draw begins
  //draw edges
  g.append("g")
      .selectAll("path")
      .data(links)
      .enter()
      .append("path")
      .attr("d",function(d){
          var start = {x:d.source.x,y:d.source.y};
          var end = {x:d.target.x,y:d.target.y};
          return Bézier_curve_generator({source:start,target:end});
      })
      .attr("fill","none")
      .attr("stroke","yellow")
      .attr("stroke-width",1);
      
  //draw nodes and words
  //create groups
  var gs = g.append("g")
      .selectAll("g")
      .data(nodes)
      .enter()
      .append("g")
      .attr("transform",function(d){
          var cx = d.x;
          var cy= d.y;
          return "translate("+cy+","+cx+")";
      });
  //draw nodes
  gs.append("circle")
      .attr("r",1)
      .attr("fill","white")
      .attr("stroke","blue")
      .attr("stroke-width",1);
      
  //draw words
  gs.append("text")
      // .attr("x",function(d){
      //     return d.children?-40:8;
      // })
      // .attr("x",-5)
      .attr("y",8)
      // .attr("dy",10)
      .style("font-size", "6px")
      .text(function(d){
          return d.data.name;
      });