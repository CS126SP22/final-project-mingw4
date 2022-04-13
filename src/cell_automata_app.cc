#include <cell_automata_visualizer.h>
#include <cell_automata_app.h>

namespace cellautomata {

namespace visualizer {

CellAutomataApp::CellAutomataApp() : visualizer_(glm::vec2(Margin, Margin), CellNumRow, WindowHeight - 2 * Margin) {
  ci::app::setWindowSize((int) WindowHeight + 150, (int) WindowHeight);
  is_runing_ = false;
  brush_color_ = 1;
  runing_step_counter_ = 10;
}

void CellAutomataApp::draw() {
  ci::Color8u background_color(255, 255, 255);
  ci::gl::clear(background_color);

  if (is_runing_) {
    if (runing_step_counter_ <= 0) {
      runing_step_counter_ = 3;
      visualizer_.Step();
    }
    else {
      runing_step_counter_ -= 1;
    }
  }

  visualizer_.Draw();

  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(900, 100), glm::vec2(950, 130)));
  ci::gl::drawStringCentered("Black", glm::vec2(925, 110), ci::Color("black"));

  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(900, 150), glm::vec2(950, 180)));
  ci::gl::drawStringCentered("White", glm::vec2(925, 160), ci::Color("black"));


  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(900, 400), glm::vec2(950, 430)));
  ci::gl::drawStringCentered("Run", glm::vec2(925, 410), ci::Color("black"));

  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(900, 450), glm::vec2(950, 480)));
  ci::gl::drawStringCentered("Pause", glm::vec2(925, 460), ci::Color("black"));
}

void CellAutomataApp::mouseDown(ci::app::MouseEvent event) {

  glm::vec2 pos = event.getPos();

  if (
      pos.x > Margin && pos.x < WindowHeight - Margin && 
      pos.y > Margin && pos.y < WindowHeight - Margin
  ) {
    visualizer_.HandleBrush(pos, brush_color_);
  } else if (
      pos.x > 900 && pos.x < 950 && 
      pos.y > 400 && pos.y < 430
  ) {
    is_runing_ = 1;
    runing_step_counter_ = 10;
  } else if (
      pos.x > 900 && pos.x < 950 && 
      pos.y > 450 && pos.y < 480
  ) {
    is_runing_ = 0;
    runing_step_counter_ = 10;
  } else if (
      pos.x > 900 && pos.x < 950 && 
      pos.y > 100 && pos.y < 130
  ) {
    brush_color_ = 1;
  } else if (
      pos.x > 900 && pos.x < 950 && 
      pos.y > 150 && pos.y < 180
  ) {
    brush_color_ = 0;
  }

}

void CellAutomataApp::mouseDrag(ci::app::MouseEvent event) {
  visualizer_.HandleBrush(event.getPos(), brush_color_);
}

void CellAutomataApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:
      // ask your classifier to classify the image that's currently drawn on the
      // sketchpad and update current_prediction_
      {
        // image_t image = visualizer_.GetImage();
        // current_prediction_ = classifier_.Predict(image);
        break;
      }
    case ci::app::KeyEvent::KEY_DELETE:
      visualizer_.Clear();
      break;
  }
}

}  // namespace visualizer

}  // namespace naivebayes
