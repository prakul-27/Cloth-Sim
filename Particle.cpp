#include "Particle.h"
#include <GL/glut.h>

// specify position as (x, y, z)
Particle::Particle(double x, double y, double z) {
    position = Eigen::Vector3d(x, y, z); 
    velocity.setZero();
    normal.setZero(); 
    netForce.setZero();
    texturecoord.setZero();
}

// specify position as vector
Particle::Particle(Eigen::Vector3d position) {
    this->position = position;
    velocity.setZero();
    normal.setZero();
    netForce.setZero();
     texturecoord.setZero();
}

// specify position as vector
Particle::Particle(Eigen::Vector3d position, Eigen::Vector2f texcord) {
    this->position = position;
    velocity.setZero();
    normal.setZero();
    netForce.setZero();
     texturecoord= texcord;
}


// set everything to origin
Particle::Particle() {
    position.setZero();
    velocity.setZero();
    normal.setZero();
    netForce.setZero();
     texturecoord.setZero();
}

//----newly added-------

// render on screen
void Particle::Draw() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex3f(position[0], position[1], position[2]);
	glEnd();
}

// zero the forces acting on it
void Particle::clearForces() {
    netForce.setZero();
}