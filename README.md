# Metaheuristiques
The aim of this work is to complete the introduction to the concepts covered during the module's course sessions on the value of using heuristics and/or metaheuristics when the problem to be solved is ‘difficult’.


# Execution : 
```bash
g++ -o scp_solver src/main.cpp src/retrieving_data.cpp src/greedy_algorithm.cpp

```
Then execute the run file scp_solver with the following options : 

```bash
./scp_solver --path/filename [--greedy|--dualfitting]      
```

### Explanation of the problem : 
We want to create a matrix with a certain amount of line and column. Then we want to cover all the lines using column minimising the cost.

In the document scpXX.txt, we have the following information :
- The first line contains the number of rows and columns of the matrix.
- The second line contains the cost of each column.
- The following lines contain the number of elements in each row.
- The following lines contain the elements of the row.


### Explanation of the algorithm :
## Greedy algorithm (algorithme_glouton.cpp):
The algorithm is based on the following steps :
- We sort the columns by cost.
- We take the column with the lowest cost and we add it to the solution.
- We remove the column from the matrix.
- We remove the rows that are covered by the column.
- We repeat the process until all the rows are covered.
- We return the solution.
- The complexity of the algorithm is O(n^2) where n is the number of rows.
- The algorithm is not optimal but it is fast.