#include <catch2/catch.hpp>
#include <cell_automata_visualizer.h>

TEST_CASE("Test forest fire simulator rule") {

    std::vector<std::vector<unsigned char>> states;
    std::vector<std::vector<unsigned char>> landforms;
    std::vector<std::vector<float>> burning_timer;
    std::vector<std::vector<unsigned char>> next_states;

    int N = 6;

    for (auto i = 0; i < N; i++) {
      std::vector<unsigned char> row;
      std::vector<unsigned char> row_temp;
      std::vector<unsigned char> row_land;
      std::vector<float> row_burning_timer;
      for (auto j = 0; j < N; j++) {
        row.push_back(4);
        row_temp.push_back(0);
        row_land.push_back(0);
        row_burning_timer.push_back(0.0f);
      }
      states.push_back(row);
      next_states.push_back(row_temp);
      landforms.push_back(row_land);
      burning_timer.push_back(row_burning_timer);
    }


    for (int i = 0; i < 100; i ++) {
      cellautomata::visualizer::step_rule_forest_fire_simulator(states, landforms, burning_timer, next_states, true);

      for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < N; j++) {
          states[i][j] = next_states[i][j];
        }
      }
    }


    for (auto i = 0; i < N; i++) {
      for (auto j = 0; j < N; j++) {
        REQUIRE(next_states[i][j] == 5);
      }
    }

}
