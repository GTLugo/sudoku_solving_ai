//
// Created by galex on 3/8/2022.
//

#pragma once

#include <iostream>
#include <bitset>
#include <unordered_map>
#include <initializer_list>

struct Position {
  int rX{0};
  int rY{0};
  int cX{0};
  int cY{0};

  Position(int rx, int ry, int cx, int cy)
      : rX{rx}, rY{ry}, cX{cx}, cY{cy} {}
  bool operator==(const Position& rhs) const {
    return rX == rhs.rX && rY == rhs.rY && cX == rhs.cX && cY == rhs.cY;
  }
};

namespace std {
  template<>
  struct hash<Position> {
    std::size_t operator()(const Position& pos) const {
      return hash<int>()(pos.cX) ^ hash<int>()(pos.cY) ^ hash<int>()(pos.rX) ^ hash<int>()(pos.rY);
    }
  };
}

class Cell {
public:
  explicit Cell(int value = 0) : value_{value} {}

  [[nodiscard]] int value() const { return value_; }
  void setValue(int value) { value_ = value; }
  [[nodiscard]] int validValueCount() const { return validValueCount_; }
  void setValidValueCount(int count) { validValueCount_ = count; }
private:
  int value_;
  int validValueCount_{};
};

class Sudoku {
public:
  static const int size{3};
  using Board = std::unordered_map<Position, Cell>;

  Sudoku() : Sudoku({}) {}
  Sudoku(std::initializer_list<int> list);

  std::bitset<Sudoku::size * Sudoku::size> validValues(const Position& pos);
  // Board& board() { return board_; } // Unnecessary since apparently this is implicitly convertable
  Cell& cell(const Position& pos) { return board_.at(pos); }

  Board::iterator begin() { return board_.begin(); }
  Board::iterator end() { return board_.end(); }
  [[nodiscard]] Board::const_iterator begin() const { return board_.begin(); }
  [[nodiscard]] Board::const_iterator end() const { return board_.end(); }

  friend std::ostream& operator<<(std::ostream& o, const Sudoku& board);
private:
  Board board_{};
};

