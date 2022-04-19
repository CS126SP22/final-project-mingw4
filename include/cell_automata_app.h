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
  void keyDown(ci::app::KeyEvent event) override;

  // provided that you can see the entire UI on your screen.
  const double WindowHeight = 900;
  const double Margin = 50;
  const int CellNumRow = 80;

 private:
  app_t app_mode_;
  bool is_runing_;
  bool is_paused_;
  unsigned char brush_color_;
  int runing_step_counter_;
  CellAutomataVisualizer visualizer_;
  int current_prediction_ = -1;
};

}  // namespace visualizer

}  // namespace cellautomata
