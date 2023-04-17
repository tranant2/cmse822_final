//Also Taken from ChatGPT

#include "Quad.hpp"

Quad::Quad(double x, double y, double size)
: x(x), y(y), size(size), totalMass(0.0), cx(0.0), cy(0.0), hasBody(false) {
for (int i = 0; i < 4; ++i) {
    children[i] = nullptr;
}
}

Quad::~Quad() {
for (int i = 0; i < 4; ++i) {
    delete children[i];
}
}

bool Quad::isLeaf() const {
return !children[0] && !children[1] && !children[2] && !children[3];
}

// Implementation of getIndex member function
int Quad::getIndex(double x, double y) const {
    // Determine which child quad the point (x, y) belongs to
    int index = 0;
    if (x > this->x) {
        index += 1;
    }
    if (y > this->y) {
        index += 2;
    }
    return index;
}

void Quad::updateForce(Body* body, double theta) {
    if (!isLeaf()) {
        double dx = cx - body->x;
        double dy = cy - body->y;
        double d = std::sqrt(dx * dx + dy * dy);

        if (size / d < theta) {
            // If
            // the ratio of the size of the quad to the distance to the body
            // is less than theta, approximate the quad as a single body
            // and update the force on the body accordingly
            double f = G * totalMass * body->mass / (d * d * d);
            body->vx += f * dx;
            body->vy += f * dy;
        } else {
            // If the quad is far enough, recursively update forces
            // on the body from the children quads
            for (int i = 0; i < 4; ++i) {
                if (children[i]->hasBody) {
                    children[i]->updateForce(body, theta);
                }
            }
        }
    }
}

// From ChatGPT with some modifications by me
void Quad::insert(Body* body) {

    //printf("1. Starting new inserting\n");
    if (!hasBody) {  // If node x does not contain a body, put the new body here
        //printf("2. New Body!...inserting\n");
        cx = body->x;
        cy = body->y;
        totalMass = body->mass;
        hasBody = true;
    } else {  // Need to check if it's an internal node or external node
        //printf("2. Has a Body...updating\n");
        if (isLeaf()) {  // if external node
            //printf("3. Is a leaf\n"); // There are two bodies
            for (int i = 0; i < 4; ++i) {
                double childSize = size / 2;
                double childX = x + (i % 2 == 0 ? -childSize / 2 : childSize / 2);
                double childY = y + (i < 2 ? -childSize / 2 : childSize / 2);
                children[i] = new Quad(childX, childY, childSize);
            }

            // Re-insert the body that was already in the quad
            int index = getIndex(cx, cy);
            //printf("4. Index: %i \n", index);
            children[index]->insert(new Body(totalMass, cx, cy, 0.0, 0.0));

            // Insert the new body
            int newIndex = getIndex(body->x, body->y);
            //printf("4. newIndex: %i \n", newIndex);

            children[newIndex]->insert(body);
            
        } else {  // if internal, must have child made already
            //printf("3. Is not a leaf...\n");
            // Insert the body into the appropriate child quad
            int index = getIndex(body->x, body->y);
            //printf("4. Index: %i \n", index);
            children[index]->insert(body);
        }
        // If the quad has a body, update the center of mass
        // and total mass of the quad
        cx = (cx * totalMass + body->x * body->mass) / (totalMass + body->mass);
        cy = (cy * totalMass + body->y * body->mass) / (totalMass + body->mass);
        totalMass += body->mass;
    }
    printf("cx:%f, cy:%f, total mass: %f \n", cx,cy,totalMass);
}
