#CS 480 - Assignment 2
Sudoku Solving AI

**Variables**
+ V = {Cell<sub>rX,rY,cX,cY</sub>}
  + rX = the column of the region in the puzzle
  + rY = the row of the region in the puzzle
  + cX = the column of the cell in the region
  + cY = the row of the cell in the region

**Domains**
+ D = {1, 2, 3, 4, 5, 6, 7, 8, 9}
  + Domain spans the number of cells in a region, row, or column


**Constraints**
+ Each row must contain no duplicate numbers
+ Each column must contain no duplicate numbers
+ Each region must contain no duplicate numbers


## Usage
Built with CMake 3.16 and C++20. Tested on Windows and Linux.

Run the following command syntax. Binaries are built into the build directory under the folder for the target platform.
```
./sudoku_ai <difficulty> [smart]
```

+ difficulty: can be of the values: "easy," "medium," "hard," or "evil"
+ smart (optional): flag that indicates whether or not to use a minimum remaining value (MRV) strategy.

Examples:
```
./sudoku_ai easy
./sudoku_ai hard smart
```
## Analysis
