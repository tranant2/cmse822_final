Use this to get long onto amd20 and get started with some processors to test on the hpcc

```shell
 module load powertools
 amd20
 salloc -n 4 --time 1:30:00
```

Then use this to complie and run the program on mpi
```shell
 mpicxx hello.cpp
 mpiexec -n 4 ./a.out 
```

# Part 1

Combine two different parallel programming models: distributed memory (i.e., MPI), shared memory (i.e., OpenMP)
- Use MPI to distribute tree structure
- Use OpenMP to distribute calculation of force

Explore different parallelization strategies (i.e., domain decomposition, task-based, etc.).
- domain decomposition is simple

Develop a verification test to ensure the correctness of your solution. Ensure that the solution does not change with the number of parallel tasks.
- Run agaist calculation of potential manually

Address load balancing and strategies for maintaining balance as tasks are increased.
- spacing filling curve

Address memory usage and how it scales with tasks for your problem.
- Speed up as N increases

Perform extensive scaling studies (i.e., weak, strong, thread-to-thread speedup). Your scaling studies should extend to as large a number of tasks as you are able to with your probl
- Much stuides