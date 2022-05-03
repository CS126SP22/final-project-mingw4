#include <catch2/catch.hpp>
#include <cell_automata_visualizer.h>

TEST_CASE("Test game of life rule hex") {

    std::vector<std::vector<unsigned char>> states;
    std::vector<std::vector<unsigned char>> next_states;

    int N = 6;

    for (auto i = 0; i < N; i++) {
      std::vector<unsigned char> row;
      std::vector<unsigned char> row_temp;
      for (auto j = 0; j < N; j++) {

        if ( i > j ) {
            row.push_back(0);
        } else {
            row.push_back(1);
        }
        row_temp.push_back(0);
      }
      states.push_back(row);
      next_states.push_back(row_temp);
    }

    cellautomata::visualizer::step_rule_game_of_life(states, next_states);

    for (auto i = 0; i < N; i++) {
      for (auto j = 0; j < N; j++) {
        if (
            (i == 2 && j == 1) || 
            (i == 3 && j == 0) || 
            (i == 3 && j == 2) || 
            (i == 4 && j == 0) ||
            (i == 4 && j == 3) ||
            (i == 5 && j == 1) ||
            (i == 5 && j == 2)
        ) {
            REQUIRE(next_states[i][j] == 1);
        }
        else {
            REQUIRE(next_states[i][j] == 0);
        }
        // std::cout << (int)next_states[i][j] << " ";
      }
      // std::cout << std::endl;
    }

}
