//
// Created by galex on 3/8/2022.
//

#include "sudoku.hpp"

#include <iomanip>
#include <bitset>

Sudoku::Sudoku(std::initializer_list<int> list) {
  for (int regionY{0}; regionY < Sudoku::size; ++regionY) {
    for (int cellY{0}; cellY < Sudoku::size; ++cellY) {
      for (int regionX{0}; regionX < Sudoku::size; ++regionX) {
        for (int cellX{0}; cellX < Sudoku::size; ++cellX) {
          int index{(cellY * Sudoku::size * Sudoku::size + cellX)
              + (regionY * Sudoku::size * Sudoku::size + regionX) * Sudoku::size};
          board_.emplace(Position{regionX, regionY, cellX, cellY}, Cell{(index < list.size()) ? data(list)[index] : 0});
        }
      }
    }
  }
}

std::vector<int> Sudoku::validValues(const Position& pos) {
  // https://stackoverflow.com/a/802109 <- Used this algorithm to speed up this method,
  // as my original method had additional loops that cause a 7x slowdown
  // This method utilizes bit flags to keep track of which numbers are seen
  int bitFlags{0};

//  for (auto pair : board_) {
//    bitFlags |= 1 << (board_.at({pos.rX, pair.first.rY, pos.cX, pair.first.cY}).value() - 1);
//    bitFlags |= 1 << (board_.at({pair.first.rX, pos.rY, pair.first.cX, pos.cY}).value() - 1);
//    bitFlags |= 1 << (board_.at({pos.rX, pos.rY, pair.first.cX, pair.first.cY}).value() - 1);
//  }

  // column
  for (int rY{0}; rY < Sudoku::size; ++rY) {
    for (int cY{0}; cY < Sudoku::size; ++cY) {
      bitFlags |= 1 << (board_.at({pos.rX, rY, pos.cX, cY}).value() - 1);
    }
  }

  // row
  for (int rX{0}; rX < Sudoku::size; ++rX) {
    for (int cX{0}; cX < Sudoku::size; ++cX) {
      bitFlags |= 1 << (board_.at({rX, pos.rY, cX, pos.cY}).value() - 1);
    }
  }

  // region
  for (int cY{0}; cY < Sudoku::size; ++cY) {
    for (int cX{0}; cX < Sudoku::size; ++cX) {
      bitFlags |= 1 << (board_.at({pos.rX, pos.rY, cX, cY}).value() - 1);
    }
  }

  std::vector<int> values{};
  for (auto i{0}; i < Sudoku::size * Sudoku::size; ++i) {
    if (!(bitFlags & (1 << i))) {
      values.push_back(i + 1);
    }
  }

  return values;
}

std::ostream& operator<<(std::ostream& o, const Sudoku& puzzle) {
  for (int regionY{0}; regionY < Sudoku::size; ++regionY) {
    for (int cellY{0}; cellY < Sudoku::size; ++cellY) {
      for (int regionX{0}; regionX < Sudoku::size; ++regionX) {
        for (int cellX{0}; cellX < Sudoku::size; ++cellX) {
          o << puzzle.board_.at({regionX, regionY, cellX, cellY}).value();
          if (cellX != 3 - 1) o << ' ';
        }
        if (regionX != 3 - 1) o << " | ";
      }
      o << '\n';
    }
    if (regionY != 3 - 1)
      o << std::setw(3 * 2)     << std::setfill('-') << '-' << '+'
        << std::setw(3 * 2 + 1) << std::setfill('-') << '-' << '+'
        << std::setw(3 * 2 + 1) << std::setfill('-') << '-'
        << '\n';
  }
  return o;
}
