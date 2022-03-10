# CS 480 - Assignment 2 - Sudoku Solving AI

## CSP
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
+ smart (optional): flag that indicates whether to use a minimum remaining value (MRV) strategy.

Examples:
```
./sudoku_ai easy
./sudoku_ai hard smart
```
## Analysis

The smart search algorithm far outperforms the simple algorithm. There are orders of magnitude in difference between the run time of the simple versus smart algorithms. 

Additionally, the variable assignment count of the smart algorithm was astronomically lower.

Overall, the smart algorithm's run time and variable assignments did not explode nearly as quickly as the simple algorithm's did, indicating much better performance.

Sample output:
![Output of simple algorithm](https://github.com/GTLugo/cs480_hw2_cpp/blob/master/output.png)
![Output of smart algorithm](https://github.com/GTLugo/cs480_hw2_cpp/blob/master/output_smart.png)