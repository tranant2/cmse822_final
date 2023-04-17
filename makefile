main_mp: bh.cpp
	mpicxx -fopenmp bh.cpp Quad.cpp -o bh.out
run_mp:
	mpiexec -n 2 ./bh.out
main: bh.cpp
	g++ bh.cpp Quad.cpp -o bh.out
run:
	./bh.out
clean:
	rm -f *.o bh.out