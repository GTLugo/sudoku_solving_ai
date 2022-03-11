//
// Created by galex on 3/8/2022.
//

#include "sudoku.hpp"

#include <iomanip>
#include <bitset>

Sudoku::Sudoku(std::initializer_list<int> list) {
  // initialize puzzle with either the values given or a default of 0
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

std::bitset<Sudoku::size * Sudoku::size> Sudoku::validValues(const Position& pos) {
  // This method finds and returns the valid states for the cell at the given position

  // https://stackoverflow.com/a/802109 <- Used this algorithm to speed up this method,
  // as my original method had additional loops that cause a 7x slowdown
  // This method utilizes bit flags to keep track of which numbers are seen
  //int bitFlags{0};
  std::bitset<Sudoku::size * Sudoku::size> flags;

//  for (auto pair : board_) {
//    flags |= 1 << (board_.at({pos.rX, pair.first.rY, pos.cX, pair.first.cY}).value() - 1);
//    flags |= 1 << (board_.at({pair.first.rX, pos.rY, pair.first.cX, pos.cY}).value() - 1);
//    flags |= 1 << (board_.at({pos.rX, pos.rY, pair.first.cX, pair.first.cY}).value() - 1);
//  }

  // column
  for (int rY{0}; rY < Sudoku::size; ++rY) {
    for (int cY{0}; cY < Sudoku::size; ++cY) {
      flags |= 1 << (board_.at({pos.rX, rY, pos.cX, cY}).value() - 1);
    }
  }

  // row
  for (int rX{0}; rX < Sudoku::size; ++rX) {
    for (int cX{0}; cX < Sudoku::size; ++cX) {
      flags |= 1 << (board_.at({rX, pos.rY, cX, pos.cY}).value() - 1);
    }
  }

  // region
  for (int cY{0}; cY < Sudoku::size; ++cY) {
    for (int cX{0}; cX < Sudoku::size; ++cX) {
      flags |= 1 << (board_.at({pos.rX, pos.rY, cX, cY}).value() - 1);
    }
  }

  return flags.flip();
}

std::ostream& operator<<(std::ostream& o, const Sudoku& puzzle) {
  // Print a formatted puzzle board
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
