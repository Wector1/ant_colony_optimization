# Ant Colony Optimization

Ant Colony Optimization algorithm solving Google HashCode 2020 online elimination problem  

## Problem Statement

The problem statement can be found [here](
https://storage.googleapis.com/coding-competitions.appspot.com/HC/2020/hashcode_2020_online_qualification_round.pdf)

## Solution

The solution is based on Ant Colony Optimization algorithm with additional mutations.

## How to run

```
bash -c "git clone https://github.com/Wector1/ant_colony_optimization.git && \
         cd ant_colony_optimization && \
         cmake -B build             && \
         cd build                   && \
         make                       && \
         ./main"
```

Program accepts data through the standard input and outputs the solution to the standard output. Alternatively, you can specify the input and output files using the following command:

```
./main <input_file >output_file
```
