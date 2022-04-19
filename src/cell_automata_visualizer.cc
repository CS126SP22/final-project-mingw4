#include <cell_automata_visualizer.h>
#include <cstdlib>

namespace cellautomata {

namespace visualizer {

using glm::vec2;


float randf() {
    return (float)rand() / RAND_MAX;
}

void step_rule_game_of_life(
  std::vector<std::vector<unsigned char>> &states,
  std::vector<std::vector<unsigned char>> &next_states
) {

  int N = states.size();

  for (auto row = 0; row < N; ++row) {
    for (auto col = 0; col < N; ++ col) {

      int count_nighbors_alive = 0;
      for (int i = -1; i < 2; i ++) {
        for (int j = -1; j < 2; j ++) {
          if (i == 0 && j == 0)
            continue;
          auto _i = (i + row + N) % N;
          auto _j = (j + col + N) % N;

          if (states[_i][_j]) {
            count_nighbors_alive += 1;
          }
        }
      }

      if (states[row][col] == 1) {
        if (count_nighbors_alive == 2 || count_nighbors_alive == 3) {
          next_states[row][col] = 1;
        } else {
          next_states[row][col] = 0;
        }
      } else {
        if (count_nighbors_alive == 3) {
          next_states[row][col] = 1;
        } else {
          next_states[row][col] = 0;
        }
      }
    }
  }
}

void step_rule_forest_fire_simulator(
  std::vector<std::vector<unsigned char>> &states,
  std::vector<std::vector<unsigned char>> &landforms,
  std::vector<std::vector<float>> &burning_timer,
  std::vector<std::vector<unsigned char>> &next_states
) {

  int N = states.size();

  for (auto row = 0; row < N; ++row) {
    for (auto col = 0; col < N; ++ col) {

      int count_nighbors_burning = 0;
      float count_nighbors_burning_time = 0.0f;

      for (int i = -1; i < 2; i ++) {
        for (int j = -1; j < 2; j ++) {
          if (i == 0 && j == 0)
            continue;
          auto _i = i + row;
          auto _j = j + col;

          if (_i < 0 || _j < 0)
            continue;
          if (_i >= N || _j >= N)
            continue;

          if (states[_i][_j] == burning) {
            count_nighbors_burning += 1;
            if (abs(i) + abs(j) == 1)
              count_nighbors_burning_time += burning_timer[_i][_j];
            else
              count_nighbors_burning_time += burning_timer[_i][_j] * 0.7f;
          }
        }
      }

      int burn_time[5] = {1, 5, 12, -1, 3};
      int burnout_time[5] = {2, 15, 36, -1, 4};

      // burning to burnout
      if (states[row][col] == burning) {
        
        int _burnout_time = burnout_time[landforms[row][col]];

        if (burning_timer[row][col] > _burnout_time && randf() > 0.7) {
          next_states[row][col] = burnout;
          burning_timer[row][col] = 0.0f;
        }
        else {
          next_states[row][col] = burning;
          burning_timer[row][col] += 1.0f;
        }

      }

      // burnout stay burnout
      else if (states[row][col] == burnout) {
        next_states[row][col] = burnout;
      }

      // notburning to burning
      else {

        int _burn_time = burn_time[landforms[row][col]];

        if (_burn_time != -1 && count_nighbors_burning_time > _burn_time && randf() > 0.2) {
          next_states[row][col] = burning;
          burning_timer[row][col] = 0.0f;
        }
        else {
          next_states[row][col] = states[row][col];
        }
      }

    }
  }
}


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
      std::vector<unsigned char> row_land;
      std::vector<float> row_burning_timer;
      for (auto j = 0; j < num_cells_row_; j++) {
        row.push_back(0);
        row_temp.push_back(0);
        row_land.push_back(0);
        row_burning_timer.push_back(0.0f);
      }
      CA_state_.push_back(row);
      CA_state_temp_.push_back(row_temp);
      CA_landforms_.push_back(row_land);
      CA_burning_timer_.push_back(row_burning_timer);
    }
}

void CellAutomataVisualizer::Draw() const {
  for (auto row = 0; row < num_cells_row_; ++row) {
    for (auto col = 0; col < num_cells_row_; ++col) {

      if (app_mode_ == game_of_life) {
        if (CA_state_[row][col] == 1) {
          ci::gl::color(ci::Color::gray(0.3f));
        }
        else {
          ci::gl::color(ci::Color("white"));
        }
      }

      else if (app_mode_ == forest_fire_simulator) {
        if (CA_state_[row][col] == grassland) {
          ci::gl::color(ci::Color8u(154, 242, 170));
        } else if (CA_state_[row][col] == scrubland) {
          ci::gl::color(ci::Color8u(72, 204, 97));
        } else if (CA_state_[row][col] == forest) {
          ci::gl::color(ci::Color8u(31, 113, 47));
        } else if (CA_state_[row][col] == lake) {
          ci::gl::color(ci::Color8u(72, 152, 232));
        } else if (CA_state_[row][col] == burning) {
          ci::gl::color(ci::Color8u(229, 49, 49));
        } else if (CA_state_[row][col] == burnout) {
          ci::gl::color(ci::Color8u(150, 150, 150));
        }
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
          5.0f) {
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

  if (app_mode_ == game_of_life) {
    step_rule_game_of_life(CA_state_, CA_state_temp_);
  }
  else if (app_mode_ == forest_fire_simulator) {
    step_rule_forest_fire_simulator(CA_state_, CA_landforms_, CA_burning_timer_, CA_state_temp_);
  }

  for (auto row = 0; row < num_cells_row_; ++row) {
    for (auto col = 0; col < num_cells_row_; ++ col) {
      CA_state_[row][col] = CA_state_temp_[row][col];
    }
  }

}

void CellAutomataVisualizer::SetAppMode(app_t app_mode) {
  app_mode_ = app_mode;
}

void CellAutomataVisualizer::BackupLandform() {
  for (auto row = 0; row < num_cells_row_; ++row) {
    for (auto col = 0; col < num_cells_row_; ++col) {
      CA_landforms_[row][col] = CA_state_[row][col];
    }
  }
}

void CellAutomataVisualizer::LoadLandform() {
  for (auto row = 0; row < num_cells_row_; ++row) {
    for (auto col = 0; col < num_cells_row_; ++col) {
      CA_state_[row][col] = CA_landforms_[row][col];
    }
  }
}


}  // namespace visualizer

}  // namespace cellautomata
