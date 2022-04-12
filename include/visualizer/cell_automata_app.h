#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "sketchpad.h"

namespace cellautomata {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class CellAutomataApp : public ci::app::App {
 public:
  CellAutomataApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  // provided that you can see the entire UI on your screen.
  const double kWindowSize = 900;
  const double kMargin = 50;
  const size_t kImageDimension = 50;

 private:
  // naivebayes::Classifier classifier_;
  bool is_runing_;
  int runing_step_counter_;
  Sketchpad sketchpad_;
};

}  // namespace visualizer

}  // namespace naivebayes
