/****
 * Author: Anthony
 * Practice code for project.
 * Barnes-Hut Algorithm
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include "mpi.h"
#include <omp.h>
#include <numeric>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>  //pow
#include <cstring>
#include <string>
using namespace std;
MPI_Comm comm = MPI_COMM_WORLD;
double MPI_WTime();


#include <time.h> // from professor
static void get_walltime_(double* wcTime) {
  struct timespec tp;
  timespec_get(&tp, TIME_UTC);
  *wcTime = (double)(tp.tv_sec + tp.tv_nsec/1000000000.0);
}

void get_walltime(double* wcTime) {
  get_walltime_(wcTime);
}

//Taken from ChatGPT
struct Body {
  double mass; // mass of the body
  double x, y; // coordinates of the body
  double vx, vy; // velocities of the body

  // Constructor
  Body(double mass, double x, double y, double vx, double vy)
    : mass(mass), x(x), y(y), vx(vx), vy(vy) {}
};

//Also Taken from ChatGPT
// class Quad {
// public:
//   Quad(double x, double y, double size)
//     : x(x), y(y), size(size), totalMass(0.0), cx(0.0), cy(0.0), hasBody(false) {
//     for (int i = 0; i < 4; ++i) {
//       children[i] = nullptr;
//     }
//   }

//   ~Quad() {
//     for (int i = 0; i < 4; ++i) {
//       delete children[i];
//     }
//   }

//   bool isLeaf() const {
//     return !children[0] && !children[1] && !children[2] && !children[3];
//   }

//   void insert(Body* body) {
//     if (!hasBody) {
//       cx = body->x;
//       cy = body->y;
//       totalMass = body->mass;
//       hasBody = true;
//     } else {
//       // If the quad has a body, update the center of mass
//       // and total mass of the quad
//       cx = (cx * totalMass + body->x * body->mass) / (totalMass + body->mass);
//       cy = (cy * totalMass + body->y * body->mass) / (totalMass + body->mass);
//       totalMass += body->mass;
//     }

//     if (isLeaf()) {
//       if (!hasBody) {
//         // If the leaf node is empty, directly insert the body
//         hasBody = true;
//       } else {
//         // If the leaf node has a body, split the node and insert both bodies
//         for (int i = 0; i < 4; ++i) {
//           double childSize = size / 2;
//           double childX = x + (i % 2 == 0 ? -childSize / 2 : childSize / 2);
//           double childY = y + (i < 2 ? -childSize / 2 : childSize / 2);
//           children[i] = new Quad(childX, childY, childSize);
//         }

//         // Re-insert the body that was already in the quad
//         int index = getIndex(cx, cy);
//         children[index]->insert(new Body(totalMass, cx, cy, 0.0, 0.0));
//         totalMass = 0.0;
//         cx = cy = 0.0;

//         // Insert the new body
//         int newIndex = getIndex(body->x, body->y);
//         children[newIndex]->insert(body);
//       }
//     } else {
//       // Insert the body into the appropriate child quad
//       int index = getIndex(body->x, body->y);
//       children[index]->insert(body);
//     }
//   }
// };



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

  double mass = 1; // mass of the body
  double x, y; // coordinates of the body
  double vx, vy; 
  x=1,y=1;
  vx=0,vy=0;

  const int ARRAY_SIZE = 100; // size of the array
  const double VALUE_MIN = -10; // minimum value for the struct member
  const double VALUE_MAX = 10; // maximum value for the struct member
  uniform_real_distribution<double> unif(VALUE_MIN,VALUE_MAX);
  default_random_engine re;

  std::vector<Body> bodies; // vector to store the generated bodies

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

  printf("x:%f \n",bodies.at(0).x);

  return 0;
}