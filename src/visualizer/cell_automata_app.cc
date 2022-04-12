#include <visualizer/cell_automata_app.h>

namespace cellautomata {

namespace visualizer {

CellAutomataApp::CellAutomataApp()
    : sketchpad_(glm::vec2(kMargin, kMargin), kImageDimension,
                 kWindowSize - 2 * kMargin) {
  ci::app::setWindowSize((int) kWindowSize + 150, (int) kWindowSize);
  is_runing_ = false;
  runing_step_counter_ = 10;
  // classifier_.LoadModel("./saved.model");
}

void CellAutomataApp::draw() {
  // ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::Color8u background_color(255, 255, 255);  // light yellow
  ci::gl::clear(background_color);

  if (is_runing_) {
    if (runing_step_counter_ <= 0) {
      runing_step_counter_ = 3;
      sketchpad_.Step();
    }
    else {
      runing_step_counter_ -= 1;
    }
  }

  sketchpad_.Draw();

  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(900, 100), glm::vec2(950, 130)));
  ci::gl::drawStringCentered("Black", glm::vec2(925, 110), ci::Color("black"));


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
      pos.x > kMargin && pos.x < kWindowSize - kMargin && 
      pos.y > kMargin && pos.y < kWindowSize - kMargin
  ) {
    sketchpad_.HandleBrush(pos);
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
  }

}

void CellAutomataApp::mouseDrag(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
}

void CellAutomataApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:
      // ask your classifier to classify the image that's currently drawn on the
      // sketchpad and update current_prediction_
      {
        // image_t image = sketchpad_.GetImage();
        // current_prediction_ = classifier_.Predict(image);
        break;
      }
    case ci::app::KeyEvent::KEY_DELETE:
      sketchpad_.Clear();
      break;
  }
}

}  // namespace visualizer

}  // namespace naivebayes
