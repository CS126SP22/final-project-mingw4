#include <cell_automata_visualizer.h>
#include <cell_automata_app.h>

using cellautomata::visualizer::CellAutomataApp;

void prepareSettings(CellAutomataApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(CellAutomataApp, ci::app::RendererGl, prepareSettings)
