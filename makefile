main: bh.cpp
	mpicxx -fopenmp bh.cpp -o bh.out
run:
	mpiexec -n 2 ./bh.out
clean:
	rm -f *.o bh.out