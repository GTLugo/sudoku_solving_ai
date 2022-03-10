//
// Created by galex on 3/8/2022.
//

#include "agent.hpp"

#include <algorithm>

std::optional<Sudoku> Agent::solve(const Sudoku& puzzle, bool smart) {
  puzzle_ = puzzle;
  assignmentCount_ = 0;
  // find all unassigned positions on the board
  for (const auto& pair : puzzle) {
    if (pair.second.value() == 0) {
      unassignedPositions_.push_front(pair.first);
    }
  }
  // if smart search, calculate heuristics
  if (smart) updateValuesAndSort();

  // begin and return result of search algorithm
  return backtrack(smart);
}

std::optional<Sudoku> Agent::backtrack(bool smart) {
  // Check for full solution
  if (unassignedPositions_.empty()) return puzzle_; // if assignment is complete then return assignment


  auto pos{unassignedPositions_.front()}; // var  SELECT-UNASSIGNED-VARIABLE(VARIABLES[csp],assignment,csp)
  auto validValues{puzzle_.validValues(pos)};
  for (auto& value : validValues) { // for each value in ORDER-DOMAIN-VALUES(var, assignment, csp) do
    // if value is consistent with assignment according to CONSTRAINTS[csp] then
    // Assign
    puzzle_.cell(pos).setValue(value); // add {var=value} to assignment
    ++assignmentCount_;
    unassignedPositions_.pop_front();
    if (smart) updateValuesAndSort();
    // Search
    auto result{backtrack(smart)}; // result  BACKTRACK(assignment, csp)
    if (result.has_value()) return result; // if result  failure then return result
    // Backtrack
    puzzle_.cell(pos).setValue(0); // remove {var=value} from assignment
    unassignedPositions_.push_front(pos);
  }

  // Return failure
  return std::nullopt;
}

void Agent::updateValuesAndSort() {
  // Each cell stores a heuristic which is the number of valid values.
  // This allows for sorting of the deque of unassigned variables by
  // the number of valid values. Additionally, doing this before sorting allows
  // for calculating this heuristic only once per cell, rather than multiple times
  // for each comparison per cell (I believe it would be 3 (constraints) * 9 * 9 (dimensions) times per cell)
  // This provides a SIGNIFICANT speed up.
  updateValidValues();
  // Simple sorting of the deque going from lowest to highest number of valid values
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
