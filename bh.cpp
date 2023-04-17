/****
 * Author: Anthony
 * Practice code for project.
 * Barnes-Hut Algorithm
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
//#include "mpi.h"
//#include <omp.h>
#include <fstream>
#include <iostream>
#include <vector>

#include "Quad.hpp"  //Quad tree code
#include "Body.hpp"  //Body code
using namespace std;
//MPI_Comm comm = MPI_COMM_WORLD;
//double MPI_WTime();


#include <time.h> // from professor
static void get_walltime_(double* wcTime) {
  struct timespec tp;
  timespec_get(&tp, TIME_UTC);
  *wcTime = (double)(tp.tv_sec + tp.tv_nsec/1000000000.0);
}

void get_walltime(double* wcTime) {
  get_walltime_(wcTime);
}


int main()
{
  srand(0);

  // initilaized MPI
  // MPI_Init(NULL, NULL);
  // int rank;
  // MPI_Comm_rank(comm, &rank);
  // int size_mpi;
  // MPI_Comm_size(comm, &size_mpi);
  // MPI_Finalize();

  const int ARRAY_SIZE = 100; // size of the array
  const double VALUE_MIN = -4; // minimum value for the struct member
  const double VALUE_MAX = 4; // maximum value for the struct member
  uniform_real_distribution<double> unif(VALUE_MIN,VALUE_MAX);
  default_random_engine re;

  std::vector<Body> bodies; // vector to store the generated bodies

  //Initialize all bodies
  for (int i = 0; i < ARRAY_SIZE; ++i) {
    // Generate a random value within the specified range
    double x = unif(re);
    double y = unif(re);
    double mass = 1; // mass of the body
    double vx, vy; 
    vx=0,vy=0;

    // Assign the random value to the struct member
    Body body(mass, x, y, vx, vy);
    bodies.push_back(body);
  }

  Quad root(0.0, 0.0, 8.0);

  for (int i=0; i<ARRAY_SIZE; i++) {
    printf("inserting %i th body at: %f, %f \n",i, bodies[i].x, bodies[i].y);
    root.insert(&bodies[i]);
  }

  // // Create some bodies
  // Body body1(10.0, -1.0, 1.0, 0.0, 0.0);
  // Body body2(5.0, 1.0, 1.0, 0.0, 0.0);
  // Body body3(3.0, -1.0, -1.0, 0.0, 0.0);

  // // Create a quad that covers the region (-2, -2) to (2, 2)
  // Quad root(0.0, 0.0, 4.0);

  // // Insert the bodies into the quad
  // root.insert(&body1);
  // root.insert(&body2);
  // root.insert(&body3);

  return 0;
}