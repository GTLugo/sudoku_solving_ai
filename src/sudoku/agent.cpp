//
// Created by galex on 3/8/2022.
//

#include "agent.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

//for (const auto& x : board_.validValues(0, 0, 0, 0)) {
//std::cout << x << ' ';
//}
//std::cout << '\n';

Agent::Agent() {

}

Agent::~Agent() {

}
std::optional<Sudoku> Agent::solve(Sudoku puzzle, bool smart) {
  puzzle_ = puzzle;
  assignmentCount_ = 0;
  for (const auto& pair : puzzle.board()) {
    if (pair.second.value() == 0) {
      unassignedPositions_.push_front(pair.first);
    }
  }
  if (smart) updateValuesAndSort();

  return backtrack(smart);
}

std::optional<Sudoku> Agent::backtrack(bool smart) {
  if (unassignedPositions_.empty()) return puzzle_;

  auto pos{unassignedPositions_.front()};
  auto validValues{puzzle_.validValues(pos)};
  for (auto& value : validValues) {
    // Assign
    puzzle_.cell(pos).setValue(value);
    ++assignmentCount_;
    unassignedPositions_.pop_front();
    if (smart) updateValuesAndSort();
    // Search
    auto result{backtrack(smart)};
    if (result.has_value()) return result;
    // Backtrack
    puzzle_.cell(pos).setValue(0);
    unassignedPositions_.push_front(pos);
  }

  return std::nullopt;
}

void Agent::updateValuesAndSort() {
  updateValidValues();
  sortUnassignedPositions();
}

void Agent::sortUnassignedPositions() {
  std::sort(unassignedPositions_.begin(), unassignedPositions_.end(), [&](const Position& l, const Position& r){
    return puzzle_.cell(l).validValueCount() < puzzle_.cell(r).validValueCount();
  });
}

void Agent::updateValidValues() {
  for (auto& pos : unassignedPositions_) {
    puzzle_.cell(pos).setValidValueCount(puzzle_.validValues(pos).size());
  }
}
