// #include <glad/glad.h>
#pragma once
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
//in windows #include <Eigen/Dense>
#include <eigen3/Eigen/Dense>

#define PARTICLE_MASS 1.0f

class Particle{
public:
    Particle(double x, double y, double z);    
    Particle(Eigen::Vector3d position);
    Particle(Eigen::Vector3d position, Eigen::Vector2f texturecoord);
    Particle();
    void Draw();
    void clearForces();

    Eigen::Vector3d position;
    Eigen::Vector3d velocity;

    Eigen::Vector3d normal;
    
    Eigen::Vector3d netForce;    
    
    Eigen::Vector2f texturecoord;
}; 