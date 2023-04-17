// Body.h
#ifndef BODY_H
#define BODY_H

//Taken from ChatGPT
struct Body {
  double mass; // mass of the body
  double x, y; // coordinates of the body
  double vx, vy; // velocities of the body

  // Constructor
  Body(double mass, double x, double y, double vx, double vy)
    : mass(mass), x(x), y(y), vx(vx), vy(vy) {}
};

#endif // BODY_H