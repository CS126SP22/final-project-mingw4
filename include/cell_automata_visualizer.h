#pragma once

#include "cinder/gl/gl.h"

namespace cellautomata {

namespace visualizer {

enum app_t {
  game_of_life=0,
  forest_fire_simulator=1
};

enum cell_t {
  square=0,
  hexagon=1
};

enum landforms_t {
  grassland=0,
  scrubland=1,
  forest=2,
  lake=3,
  burning=4,
  burnout=5
};

// Step rule of game_of_life and forest_fire_simulator
void step_rule_game_of_life(
  std::vector<std::vector<unsigned char>> &states,
  std::vector<std::vector<unsigned char>> &next_states
);

void step_rule_forest_fire_simulator(
  std::vector<std::vector<unsigned char>> &states,
  std::vector<std::vector<unsigned char>> &landforms,
  std::vector<std::vector<float>> &burning_timer,
  std::vector<std::vector<unsigned char>> &next_states,
  bool is_square
);

/**
 * A visualizer which will displayed 2D cellular automata and response the
 * mouse and key events. 
 */
class CellAutomataVisualizer {
 public:
  /**
   * Creates a visualizer.
   *
   * @param top_left            the screen coordinates of the top left corner of
   *                            the visualizer
   * @param num_cells_row       the number of visualizer cells in one row/column
   *                            of the visualizer
   * @param visualizer_size     the side length of the visualizer, measured in
   *                            screen cells
   */
  CellAutomataVisualizer(const glm::vec2& top_left, int num_cells_row, double visualizer_size);

  /**
   * Displays the current state of the visualizer in the Cinder application.
   */
  void Draw() const;

  /**
   * Shades cells to change their state within brush_radius units.
   *
   * @param brush_screen_coords the screen coordinates at which the brush is
   *           located
   */
  void HandleBrush(const glm::vec2& brush_screen_coords, unsigned char color);

  /**
   * Set all cells state to 0.
   */
  void Clear();

  /**
   * Run cell automata one step.
   */
  void Step();

  /**
   * Setter of the app mode
   */
  void SetAppMode(app_t app_mode);
  void SetCellMode(cell_t cell_mode);

  void Initialize();

  /**
   * Backups landforms from CA_state_ to CA_landforms_
   * and load landforms from CA_landforms_ to CA_state_
   */
  void BackupLandform();
  void LoadLandform();


 private:

  // visualization state and state buffer
  std::vector<std::vector<unsigned char>> CA_state_;
  std::vector<std::vector<unsigned char>> CA_state_temp_;

  // hidden states for forest_fire_simulator
  std::vector<std::vector<unsigned char>> CA_landforms_;
  std::vector<std::vector<float>> CA_burning_timer_;

  app_t app_mode_;
  cell_t cell_mode_;
  glm::vec2 top_left_;
  /** Number of screen cells in the width/height of one visualizer cell */
  int num_cells_row_;
  double cell_width_;
};

}  // namespace visualizer

}  // namespace cellautomata
