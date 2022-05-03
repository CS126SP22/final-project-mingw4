#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cell_automata_visualizer.h"

namespace cellautomata {

namespace visualizer {

/**
 * Allows a user to control the cellautomata application
 */
class CellAutomataApp : public ci::app::App {
 public:
  CellAutomataApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void mouseMove(ci::app::MouseEvent event) override;
  void mouseWheel(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  // provided that you can see the entire UI on your screen.
  const double WindowHeight = 900;
  const double Margin = 50;
  const int CellNumRow = 40;

 private:
  // app mode and cell mode
  app_t app_mode_;
  cell_t cell_mode_;

  // app flags and properties
  bool is_runing_;
  bool is_paused_;
  bool show_brush_radius_;
  unsigned char brush_color_;
  int runing_step_counter_;
  int brush_radius_;

  // the visualizer
  CellAutomataVisualizer visualizer_;
};

}  // namespace visualizer

}  // namespace cellautomata
