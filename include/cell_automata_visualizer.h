#pragma once

#include "cinder/gl/gl.h"

namespace cellautomata {

namespace visualizer {

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

 private:

  std::vector<std::vector<unsigned char>> CA_state_;
  std::vector<std::vector<unsigned char>> CA_state_temp_;

  glm::vec2 top_left_;
  /** Number of screen cells in the width/height of one visualizer cell */
  int num_cells_row_;
  double cell_width_;
};

}  // namespace visualizer

}  // namespace cellautomata
