#include "maliput/drake/systems/framework/system_html.h"

#include "maliput/drake/systems/framework/system.h"
#include "maliput/drake/systems/framework/system_visitor.h"

namespace maliput::drake {
namespace systems {

namespace {

// Writes the descriptions of each system as nodes in the block diagram graph.
class NodeWriter : public SystemVisitor<double> {
 public:
  NodeWriter(const std::string parent, std::stringstream* html, int depth)
      : parent_(parent), html_(html), depth_(depth) {}

  void VisitSystem(const System<double>& system) final {
    *html_ << "{ ";
    *html_ << "key: \"" << system.get_name() << "\", ";
    *html_ << "group: \"" << parent_ << "\", ";
    *html_ << "input_ports: [ ";
    for (int i = 0; i < system.num_input_ports(); ++i) {
      *html_ << "{ name: \"" << system.get_input_port(i).get_name()
             << "\", id: \"u" << i << "\" }, ";
    }
    *html_ << "],\n";
    *html_ << "output_ports: [ ";
    for (int i = 0; i < system.num_output_ports(); ++i) {
      *html_ << "{ name: \"" << system.get_output_port(i).get_name()
             << "\", id: \"y" << i << "\" }, ";
    }
    *html_ << "],\n";
    *html_ << "},\n";
  }

 private:
  const std::string parent_;
  std::stringstream* html_;
  const int depth_;
};

// Extra visitor class to handle connections *from* either diagram input ports
// or the output of a subsystem.
class FromPortTokenWriter : public SystemVisitor<double> {
 public:
  FromPortTokenWriter(int port_index, std::stringstream* html)
      : port_index_(port_index), html_(html) {}

  void VisitSystem(const System<double>& system) final {
    *html_ << "from: \"" << system.get_name() << "\", ";
    *html_ << "fromPort: \"y" << port_index_ << "\", ";
  }

  // void VisitDiagram(const Diagram<double>& diagram) final {
  //   *html_ << "from: \"" << diagram.get_name() << "_y" << port_index_ << "\", ";
  // }

 private:
  const int port_index_;
  std::stringstream* html_;
};

// Extra visitor class to handle connections *to* either diagram output ports or
// the input of a subsystem.
class ToPortTokenWriter : public SystemVisitor<double> {
 public:
  ToPortTokenWriter(int port_index, std::stringstream* html)
      : port_index_(port_index), html_(html) {}

  void VisitSystem(const System<double>& system) final {
    *html_ << "to: \"" << system.get_name() << "\", ";
    *html_ << "toPort: \"u" << port_index_ << "\", ";
  }

  // void VisitDiagram(const Diagram<double>& diagram) final {
  //   *html_ << "to: \"" << diagram.get_name() << "_u" << port_index_ << "\", ";
  // }

 private:
  const int port_index_;
  std::stringstream* html_;
};

// Writes the connections between systems as edges in the block diagram graph.
class LinkWriter : public SystemVisitor<double> {
 public:
  explicit LinkWriter(std::stringstream* html) : html_(html) {}

  void VisitSystem(const System<double>& system) final {
    // No links to write.
    unused(system);
  }

 private:
  std::stringstream* html_;
};

}  // namespace

std::string GenerateHtml(const System<double>& system, int initial_depth) {
  std::stringstream html;
  html << R"""(
<div style='height:400px;' id='myDiagramDiv'>
The implementation of GenerateHtml has been temporarily removed from Drake due
to licensing restrictions.
</div>
<script>
  $ = go.GraphObject.make
  var diagram = $(go.Diagram, "myDiagramDiv", {
    "undoManager.isEnabled": true,
    initialAutoScale: go.Diagram.Uniform
  });
  diagram.layout = $(go.LayeredDigraphLayout, {
    layerSpacing: 20,
    columnSpacing: 20,
    isRealtime: false
  });

  diagram.groupTemplate = $(
    go.Group,
    "Auto",
    { layout: $(go.LayeredDigraphLayout, { direction: 0, columnSpacing: 10 }) },
    new go.Binding("isSubGraphExpanded", "expanded"),
    $(
      go.Shape,
      "RoundedRectangle", // surrounds everything
      { parameter1: 10, fill: "rgba(128,128,128,0.33)" }
    ),
    $(
      go.Panel,
      "Vertical", // position header above the subgraph
      { defaultAlignment: go.Spot.Left },
      $(
        go.Panel,
        "Horizontal", // the header
        { defaultAlignment: go.Spot.Top },
        $("SubGraphExpanderButton"), // this Panel acts as a Button
        $(
          go.TextBlock, // group title near top, next to button
          { font: "Bold 12pt Sans-Serif" },
          new go.Binding("text", "name")
        )
      ),
      $(
        go.Placeholder, // represents area for all member parts
        { padding: new go.Margin(0, 10), background: "white" }
      )
    )
  );
  var systemTemplate = $(
    go.Node,
    "Auto",
    $(go.Shape, "RoundedRectangle", {
      parameter1: 10,
      fill: "rgba(128,128,228,0.33)"
    }),
    $(
      go.Panel,
      "Table",
      { margin: 10 },
      $(
        go.TextBlock,
        { row: 0, column: 0, columnSpan: 2, alignment: go.Spot.Center },
        { font: "bold 12pt sans-serif" },
        new go.Binding("text", "key")
      ),
      $(go.RowColumnDefinition, {
        row: 1,
        separatorStrokeWidth: 1.5,
        separatorStroke: "black"
      }),
      $(go.TextBlock, {
        // add a spacer
        row: 1,
        column: 0,
        columnSpan: 2,
        height: 10
      }),
      $(
        go.Panel,
        "Vertical",
        { name: "INPUT_PORTS" },
        new go.Binding("itemArray", "input_ports"),
        {
          row: 2,
          column: 0,
          alignment: go.Spot.Left,
          itemTemplate: $(
            go.Panel,
            "Auto",
            { margin: 2 },
            $(go.Shape, "RoundedRectangle", { fill: "lightcyan" }),
            $(go.TextBlock, new go.Binding("text", "name"), {
              margin: 2
            }),
            new go.Binding("portId", "id")
          ) // end of itemTemplate
        }
      ),
      $(
        go.Panel,
        "Vertical",
        { name: "OUTPUT_PORTS" },
        new go.Binding("itemArray", "output_ports"),
        {
          row: 2,
          column: 1,
          alignment: go.Spot.Right,
          itemTemplate: $(
            go.Panel,
            "Auto",
            { margin: 2 },
            $(go.Shape, "RoundedRectangle", { fill: "lightcyan" }),
            $(go.TextBlock, new go.Binding("text", "name"), {
              margin: 2
            }),
            new go.Binding("portId", "id")
          ) // end of itemTemplate
        }
      )
    )
  );

  var portTemplate = $(
    go.Node,
    "Auto",
    $(go.Shape, "RoundedRectangle", {
      parameter1: 10,
      fill: "honeydew"
    }),
    $(
      go.TextBlock,
      { row: 0, column: 0, columnSpan: 2, alignment: go.Spot.Right },
      new go.Binding("text", "name")
    )
  );

  var templmap = new go.Map();
  templmap.add("", systemTemplate);
  templmap.add("input_port", portTemplate);
  templmap.add("output_port", portTemplate);
  diagram.nodeTemplateMap = templmap;

  diagram.model = $(go.GraphLinksModel, {
    linkFromPortIdProperty: "fromPort", // required information:
    linkToPortIdProperty: "toPort", // identifies data property names
    nodeDataArray: [
)""";

  NodeWriter node_writer("", &html, initial_depth);
  system.Accept(&node_writer);

  html << R"""(
    ],
    linkDataArray: [
)""";

  LinkWriter link_writer(&html);
  system.Accept(&link_writer);

  html << R"""(
    ]
  });
</script>
)""";
  return html.str();
}

}  // namespace systems
}  // namespace maliput::drake
