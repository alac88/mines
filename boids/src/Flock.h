#ifndef FLOCK_H
#define FLOCK_H

#include "Boid.h"
#include <vector>

class Flock {
public:
	std::vector<Boid> boids;
	Boid target;

	// Constructor
	Flock();
	// Destructor
	~Flock();

	void add();
	void draw();
	void move(float dt);
};

#endif 
