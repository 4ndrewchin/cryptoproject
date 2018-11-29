# cryptoproject

Pollard's p-1 Algorithm

Author: Andrew Chin

The program is simple. We use command line arguments as input into the program with no input validation.

### Introduction
This simple program is used to factor numbers. The user can choose to factor a random number or pick their own number. The output consists of 3 lines: the first line is the number of algorithm iterations it takes to find the first factor, the second line consists of N (the number to factor) and its two factors, p and q, the third line displays the run time in seconds.

### Usage:
- to build, use the command `make all`.
- to run, use the command `./pollards` with appropriate options.

### Help Text
```
USAGE: pollards [options] <inputs>
OPTIONS:
  -n <value> factor a specified value
  -r         generate a random number to factor
  -h         print this help menu
```

### Future Work
Create an interpreter with a simple text-based GUI using the ncurses API that factors numbers that are entered.
