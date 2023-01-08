# Topological Sort

Topological sort, not very well done. Added my own bitset implementation(tsort::bitset2) and by quick-bench measurements it preforms worse than std::bitset. If you want to use std::bitset, it should't be too much of an effort to change it.

## How to use it

Example file is [main.cpp](main.cpp). 
Step 1. create vector with all edges
Step 2. create vector with all nodes
Step 3. create empty vector for sorted nodes
Step 4. pass on these parameters to function tsort:tsort(...)

## Notice

This function uses [this](https://en.wikipedia.org/wiki/Topological_sorting#Kahn.27s_algorithm) sort. If your graph is not acyclical, tsort funtion is not going to cathc it.
