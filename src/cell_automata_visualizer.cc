#include <cell_automata_visualizer.h>

namespace cellautomata {

namespace visualizer {

using glm::vec2;

CellAutomataVisualizer::CellAutomataVisualizer(
  const vec2& top_left_corner,
  int num_cells_row,
  double visualizer_size
) {

    top_left_ = top_left_corner;
    num_cells_row_ = num_cells_row;
    cell_width_ = visualizer_size / num_cells_row;

    for (auto i = 0; i < num_cells_row_; i++) {
      std::vector<unsigned char> row;
      std::vector<unsigned char> row_temp;
      for (auto j = 0; j < num_cells_row_; j++) {
        row.push_back(0);
        row_temp.push_back(0);
      }
      CA_state_.push_back(row);
      CA_state_temp_.push_back(row_temp);
    }
    ;
}

void CellAutomataVisualizer::Draw() const {
  for (auto row = 0; row < num_cells_row_; ++row) {
    for (auto col = 0; col < num_cells_row_; ++col) {
      if (CA_state_[row][col] == 1) {
        ci::gl::color(ci::Color::gray(0.3f));
      }
      else {
        ci::gl::color(ci::Color("white"));
      }

      vec2 cell_top_left = top_left_ + vec2(col * cell_width_, row * cell_width_);

      ci::Rectf cell_rect(
        cell_top_left, cell_top_left + vec2(cell_width_, cell_width_)
      );
      ci::gl::drawSolidRect(cell_rect);

      ci::gl::color(ci::Color("black"));
      ci::gl::drawStrokedRect(cell_rect);
    }
  }
}

void CellAutomataVisualizer::HandleBrush(const vec2& brush_screen_coords, unsigned char color) {

  vec2 brush_vis_coords =
      (brush_screen_coords - top_left_) / (float)cell_width_;

  for (auto row = 0; row < num_cells_row_; ++row) {
    for (auto col = 0; col < num_cells_row_; ++col) {
      vec2 cell_center = {col + 0.5, row + 0.5};

      if (glm::distance(brush_vis_coords, cell_center) <=
          2.0f) {
        CA_state_[row][col] = (unsigned char) color;
      }
    }
  }
}

void CellAutomataVisualizer::Clear() {

  for (auto row = 0; row < num_cells_row_; ++row) {
    for (auto col = 0; col < num_cells_row_; ++col) {
      CA_state_[row][col] = 0;
    }
  }
}

void CellAutomataVisualizer::Step() {

  for (auto row = 0; row < num_cells_row_; ++row) {
    for (auto col = 0; col < num_cells_row_; ++ col) {

      int count_nighbors_alive = 0;
      for (int i = -1; i < 2; i ++) {
        for (int j = -1; j < 2; j ++) {
          if (i == 0 && j == 0)
            continue;
          auto _i = (i + row) % num_cells_row_;
          auto _j = (j + col) % num_cells_row_;
          if (CA_state_[_i][_j]) {
            count_nighbors_alive += 1;
          }
        }
      }

      if (CA_state_[row][col] == 1) {
        if (count_nighbors_alive == 2 || count_nighbors_alive == 3) {
          CA_state_temp_[row][col] = 1;
        } else {
          CA_state_temp_[row][col] = 0;
        }
      } else {
        if (count_nighbors_alive == 3) {
          CA_state_temp_[row][col] = 1;
        } else {
          CA_state_temp_[row][col] = 0;
        }
      }
    }
  }

  for (auto row = 0; row < num_cells_row_; ++row) {
    for (auto col = 0; col < num_cells_row_; ++ col) {
      CA_state_[row][col] = CA_state_temp_[row][col];
    }
  }

}

}  // namespace visualizer

}  // namespace cellautomata
