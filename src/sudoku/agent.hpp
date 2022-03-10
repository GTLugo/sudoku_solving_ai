//
// Created by galex on 3/8/2022.
//

#pragma once

#include "sudoku.hpp"

#include <optional>
#include <deque>

class Agent {
public:
  Agent();
  ~Agent();

  std::optional<Sudoku> solve(Sudoku puzzle, bool smart = false);
  [[nodiscard]] int assignmentCount() const { return assignmentCount_; }

private:
  Sudoku puzzle_;
  std::deque<Position> unassignedPositions_{};
  int assignmentCount_{};

  std::optional<Sudoku> backtrack(bool smart);

  void updateValuesAndSort();
  void updateValidValues();
  void sortUnassignedPositions();
};

