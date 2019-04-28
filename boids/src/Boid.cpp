#include <iostream>
#include <GL/glut.h>
#include "Boid.h"

//BOID
Boid::Boid() : p(0,0,0), v(0,0,0), a(0,0,0){
	r = (float)rand() / (float) RAND_MAX;
	g = (float)rand() / (float) RAND_MAX;
	b = (float)rand() / (float) RAND_MAX;
}

Boid::Boid(float px, float py, float pz, float vx, float vy, float vz,
 			float ax, float ay, float az) : p(Eigen::Vector3f(px,py,pz)), v(Eigen::Vector3f(vx,vy,vz)),
			 								a(Eigen::Vector3f(ax,ay,az)){
	r = (float)rand() / (float) RAND_MAX;
	g = (float)rand() / (float) RAND_MAX;
	b = (float)rand() / (float) RAND_MAX;
}

Boid::~Boid(){
}

void Boid::draw()
{
	float x = p(0), y=p(1), z=p(2);
	glPushMatrix();
	glTranslatef(x,y,z);
	glColor3f(r,g,b);
	glutSolidCube(1); //1 = size of the cube
	glPopMatrix();
}
