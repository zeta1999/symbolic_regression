# CSE822 Symbolic Regression Project

A simple symbolic regression project using genetic programming, MPI, and OpenMP. This code makes heavy use of reverse polish notation (abbreviated rpn in the code; also known as post-fix notation) which is a simple way of representing a function so it can be evaluated on a stack: [see here for more](https://en.wikipedia.org/wiki/Reverse_Polish_notation). For more on genetic programming see [wikipedia](https://en.wikipedia.org/wiki/Genetic_programming), [geneticprogramming.com](http://geneticprogramming.com/), and [this excellent introductory book](https://www.amazon.com/Genetic-Programming-Introduction-Artificial-Intelligence/dp/155860510X).

## Compiling

Run  `make`.

## Running

Compiled program takes a few arguments to be able to run.

```
-m <float> mutation rate, in range [0, 1]
-c <float> crossover rate, in range [0, 1]
-s <int> seed, random seed
-f <int> function, from FunctionFactory::FunctionType enum
-p <int> population size, > 0
-g <int> generations, > 0
```

Each must be provided, no default values are hard coded. See `simple_run.sh` for an example.
