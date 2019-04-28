#ifndef BOIDS_H
#define BOIDS_H

#include <Eigen/Dense>


class Boid {
private:
	float r;
	float g;
	float b;

public:
	Eigen::Vector3f p;
	Eigen::Vector3f v;
	Eigen::Vector3f a;

	// Constructor
	Boid();
	Boid(float px, float py, float pz, float vx, float vy, float vz,
 			float ax, float ay, float az);
	// Destructor
	~Boid();

	void draw();
};

#endif  // BOIDS_LIB_SAMPLE_CLASS_H_
