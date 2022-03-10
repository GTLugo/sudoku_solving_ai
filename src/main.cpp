#include "sudoku/agent.hpp"
#include "sudoku/difficulty.hpp"

#include "time.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 2 && argc != 3) {
    std::cout << "Usage: ./sudoku.exe <difficulty: easy, medium, hard, evil> [smart]\n";
    return 1;
  }

  Sudoku puzzle;
  if      (strcmp(argv[1], "easy") == 0)   puzzle = Difficulty::easy();
  else if (strcmp(argv[1], "medium") == 0) puzzle = Difficulty::medium();
  else if (strcmp(argv[1], "hard") == 0)   puzzle = Difficulty::hard();
  else if (strcmp(argv[1], "evil") == 0)   puzzle = Difficulty::evil();
  else {
    std::cout << "Unknown difficulty! Usage: ./sudoku.exe <difficulty: easy, medium, hard, evil> [smart]\n";
    return 1;
  }

  bool smartSearch{argc == 3 && (strcmp(argv[2], "smart") == 0)};
  Agent agent{};
  flf::Stopwatch sw{};
  auto solution{agent.solve(puzzle, smartSearch)};
  double timeSpent{sw.getTimeElapsed<flf::Seconds>()};

  if (solution.has_value()) {
    std::cout << "Found solution for \"" << argv[1] << "\" in " << timeSpent << " seconds and "
      << agent.assignmentCount() << " assignments\n"
      << solution.value() << '\n';
  } else {
    std::cout << "Failed to find solution for \"" << argv[1] << "\" after " << timeSpent << " seconds and "
      << agent.assignmentCount() << " assignments\n";
  }

  return 0;
}
