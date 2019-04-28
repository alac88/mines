#include <iostream>
#include <GL/glut.h>
#include "Flock.h"

int initial_boids_number = 5;

float randomFloat(float a, float b){
    //Returns a random float between a and b
    float r = (float)rand() / (float)RAND_MAX;
    return (b-a)*r + a;
}

//BOID
Flock::Flock() : target(1,1,1,
                        randomFloat(-4,4),randomFloat(-4,4),randomFloat(-4,4),
                        0,0,0){
    for(int i = 0; i < initial_boids_number; i++){
        Boid b(randomFloat(-2,2), randomFloat(-2,2), randomFloat(-2,2),
                randomFloat(-4,4), randomFloat(-4,4), randomFloat(-4,4),
                0, 0, 0);
        boids.push_back(b);
    }
}

Flock::~Flock() {
}

void Flock::add(){
    Boid b(randomFloat(-0.5,0.5), randomFloat(-0.5,0.5), randomFloat(-0.5,0.5),
                randomFloat(-4,4), randomFloat(-4,4), randomFloat(-4,4),
                0, 0, 0);
    boids.push_back(b);
}

void Flock::draw()
{
    target.draw();
    for(auto& b:boids){
        b.draw();
    }
}

int direction = 1;
void Flock::move(float dt)
{
    float cx = 0, cy = 0, cz = 0;
    float vx = 0, vy = 0, vz = 0;
    float ax = 0, ay = 0, az = 0;

    for(auto& b:boids){
        cx += b.p(0);
        cy += b.p(1);
        cz += b.p(2);

        vx += b.v(0);
        vy += b.v(1);
        vz += b.v(2);  

        ax += b.a(0);
        ay += b.a(1);
        az += b.a(2);  
    }

    int size = boids.size();
    cx /= size;
    cy /= size;
    cz /= size;
    Eigen::Vector3f c(cx,cy,cz);

    vx /= size;
    vy /= size;
    vz /= size;
    Eigen::Vector3f v(vx,vy,vz);

    ax /= size;
    ay /= size;
    az /= size;
    Eigen::Vector3f a(ax,ay,az);

    for(auto& b:boids){
        
        //Acceleration
        Eigen::Vector3f cohesion, alignment;
        Eigen::Vector3f separation(0,0,0);

        //Regle de cohesion
        cohesion = 0.01*(c-b.p);

        //Regle de separation
        for(auto& c:boids){
            //20 is arbitrary, does it need to change ?
            if(&c != &b and (c.p - b.p).norm() < 10){
                separation = 0.5*(b.p - c.p);
            }
        }

        //Regle d'alignement
        alignment = 0.2*(v-b.p);

        //Acceleration
        float amax = 10;
        if((cohesion + separation + alignment).norm() < amax)
            b.a = cohesion + separation + alignment;
        else
            b.a = b.a;

        //Vitesse
        b.v = b.v + dt*b.a + 0.001*(target.p - b.p)/(target.p - b.p).norm();

        //Position
        b.p = b.p + dt*b.v;

    }

    //target.a = target.a + Eigen::Vector3f(randomFloat(-1,1), randomFloat(-1,1), randomFloat(-1,1));
    
    target.a = (-target.p)/(target.p.norm()*target.p.norm()*target.p.norm());
    // if(abs(target.p(0)) > 7)
    //     direction = -direction;

    target.v = target.v + dt*target.a;
    
    target.p(0) = target.p(0) + dt*target.v(0);
    target.p(1) = target.p(1) + dt*target.v(1);
    target.p(2) = target.p(2) + dt*target.v(2);
}