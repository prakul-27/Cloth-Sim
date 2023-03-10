#include "Cloth.h"
#include <GL/glut.h>

Cloth::Cloth() {

    // Particles
    particles.assign(MESH_SIZE, std::vector<Particle>(MESH_SIZE));    
    for (int i=0; i<MESH_SIZE; i++) {
        Eigen::Vector3d origin(0, STRUCTURAL_NATURAL_LENGTH*i, 0);
        for (int j=0; j<MESH_SIZE; j++) {
            Eigen::Vector2f texCoord(j / (MESH_SIZE - 1.0f), i / (MESH_SIZE - 1.0f));

            particles[i][j] = Particle(origin,texCoord);
            origin += Eigen::Vector3d(STRUCTURAL_NATURAL_LENGTH, 0, 0);
        }
    }

    // Structural Springs
    springs.assign(MESH_SIZE, std::vector<std::vector<Spring>>(MESH_SIZE, std::vector<Spring>()));
    for (int i=0; i<MESH_SIZE-1; i++) {
        for (int j=0; j<MESH_SIZE; j++) {                        
            springs[i][j].push_back(Spring(TYPE_STRUCTURAL, &particles[i][j], &particles[i+1][j], i, j, i+1, j));
            springs[i+1][j].push_back(Spring(TYPE_STRUCTURAL, &particles[i+1][j], &particles[i][j], i+1, j, i, j));
            structural_springs.push_back(Spring(TYPE_STRUCTURAL, &particles[i][j], &particles[i+1][j], i, j, i+1, j));
        }
    }
    for (int i=0; i<MESH_SIZE; i++) {
        for (int j=0; j<MESH_SIZE-1; j++) {                        
            springs[i][j].push_back(Spring(TYPE_STRUCTURAL, &particles[i][j], &particles[i][j+1], i, j, i, j+1));
            springs[i][j+1].push_back(Spring(TYPE_STRUCTURAL, &particles[i][j+1], &particles[i][j], i, j+1, i, j));
            structural_springs.push_back(Spring(TYPE_STRUCTURAL, &particles[i][j], &particles[i][j+1], i, j, i, j+1));
        }
    }
    
    // Shear Springs
    for (int i=0; i<MESH_SIZE-1; i++) {
        for (int j=0; j<MESH_SIZE-1; j++) {            
            springs[i][j].push_back(Spring(TYPE_SHEAR, &particles[i][j], &particles[i+1][j+1], i, j, i+1, j+1));
            springs[i+1][j+1].push_back(Spring(TYPE_SHEAR, &particles[i+1][j+1], &particles[i][j], i+1, j+1, i, j));
            springs[i+1][j].push_back(Spring(TYPE_SHEAR, &particles[i+1][j], &particles[i][j+1], i+1, j, i, j+1));
            springs[i][j+1].push_back(Spring(TYPE_SHEAR, &particles[i][j+1], &particles[i+1][j], i, j+1, i+1, j));
            shear_springs.push_back(Spring(TYPE_SHEAR, &particles[i+1][j], &particles[i][j+1], i+1, j, i, j+1));
            shear_springs.push_back(Spring(TYPE_SHEAR, &particles[i][j], &particles[i+1][j+1], i, j, i+1, j+1));
        }
    }

    // Flexion Springs
    for (int i=0; i<MESH_SIZE-2; i++) {
        for (int j=0; j<MESH_SIZE; j++) {     
            springs[i][j].push_back(Spring(TYPE_FLEXION, &particles[i][j], &particles[i+2][j], i, j, i+2, j));
            springs[i+2][j].push_back(Spring(TYPE_FLEXION, &particles[i+2][j], &particles[i][j], i+2, j, i, j));       
            flexion_springs.push_back(Spring(TYPE_FLEXION, &particles[i][j], &particles[i+2][j], i, j, i+2, j));            
        }
    }   
    for (int i=0; i<MESH_SIZE; i++) {
        for (int j=0; j<MESH_SIZE-2; j++) {  
            springs[i][j].push_back(Spring(TYPE_FLEXION, &particles[i][j], &particles[i][j+2], i, j, i, j+2));
            springs[i][j+2].push_back(Spring(TYPE_FLEXION, &particles[i][j+2], &particles[i][j], i, j+2, i, j));          
            flexion_springs.push_back(Spring(TYPE_FLEXION, &particles[i][j], &particles[i][j+2], i, j, i, j+2));
        }
    }
    
}


void Cloth::Draw(void){


    	// Draw springs
	// for (int i = 0; i < structural_springs.size(); i++)
	// 	structural_springs[i].Draw();
	// for (int i = 0; i < shear_springs.size(); i++)
	// 	shear_springs[i].Draw();
	// for (int i = 0; i < flexion_springs.size(); i++)
	// 	flexion_springs[i].Draw();

	// // Draw particles
	// for (int i = 0; i < MESH_SIZE; i++) {
	// 	for (int j = 0; j < MESH_SIZE; j++)
	// 		particles[i][j].Draw();
	// }

    
    
    //draw texture

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureObj);
	for (int i = 0; i < MESH_SIZE - 1; i++) {
		for (int j = 0; j < MESH_SIZE - 1; j++) {
			glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(particles[i][j].normal[0], particles[i][j].normal[1], particles[i][j].normal[2]);
			glTexCoord2f(particles[i][j].texturecoord[0], particles[i][j].texturecoord[1]);
			glVertex3f(particles[i][j].position[0], particles[i][j].position[1],particles[i][j].position[2]);

            	glNormal3f(particles[i+1][j].normal[0], particles[i+1][j].normal[1], particles[i+1][j].normal[2]);
			glTexCoord2f(particles[i+1][j].texturecoord[0], particles[i+1][j].texturecoord[1]);
			glVertex3f(particles[i+1][j].position[0], particles[i+1][j].position[1],particles[i+1][j].position[2]);
			

            	glNormal3f(particles[i][j+1].normal[0], particles[i][j+1].normal[1], particles[i][j+1].normal[2]);
			glTexCoord2f(particles[i][j+1].texturecoord[0], particles[i][j+1].texturecoord[1]);
			glVertex3f(particles[i][j+1].position[0], particles[i][j+1].position[1],particles[i][j+1].position[2]);


            	glNormal3f(particles[i+1][j+1].normal[0], particles[i+1][j+1].normal[1], particles[i+1][j+1].normal[2]);
			glTexCoord2f(particles[i+1][j+1].texturecoord[0], particles[i+1][j+1].texturecoord[1]);
			glVertex3f(particles[i+1][j+1].position[0], particles[i+1][j+1].position[1],particles[i+1][j+1].position[2]);
		
			

			glEnd();
		}
	}

}

// void Cloth::Simulate(float T, float delta_t) {
//     float t = 0;
//     while(t < T) {
//         printState(t);
//         sleep(1);
//         nextState(delta_t);
//         t = t + delta_t;        
//     }         
// }

void Cloth::Simulate() {
    float delta_t = 0.01f;
    // tmp update to particles
    std::vector<std::vector<std::pair<Eigen::Vector3d, Eigen::Vector3d>>> tmp;
    // assign empty pairs
    tmp.assign(MESH_SIZE, std::vector<std::pair<Eigen::Vector3d, Eigen::Vector3d>>
    (MESH_SIZE, std::pair<Eigen::Vector3d, Eigen::Vector3d>()));

    // iterate over all mesh points (particles)
    for (int i=0; i<MESH_SIZE; i++) {
        for (int j=0; j<MESH_SIZE; j++) {
            // compute forces
            Eigen::Vector3d F_gr = computeNetGravitationalForce(i, j);            
            Eigen::Vector3d F_int = computeNetInternalForce(i, j);            
            // Eigen::Vector3d F_dis = computeNetDampingForce(i, j); // glm::vec3(.0f, .0f, .0f);           
            // Eigen::Vector3d F_vi = computeNetViscousForce(i, j);                        
            //net force
            Eigen::Vector3d F_net = F_gr + F_int; //+ F_dis + F_vi;
            //v_ij (t) and P_ij (t)
            Eigen::Vector3d v_ij = particles[i][j].velocity;
            Eigen::Vector3d P_ij = particles[i][j].position;            
            // integration
            Eigen::Vector3d nxt_a_ij =  F_net / PARTICLE_MASS;
            Eigen::Vector3d nxt_v_ij = v_ij + delta_t*nxt_a_ij;
            Eigen::Vector3d nxt_P_ij = P_ij + delta_t*nxt_v_ij; 
            // update 
            tmp[i][j] = std::make_pair(nxt_P_ij, nxt_v_ij);
        }
    }

    //-------------
    // apply dynamic inverse procedure to remove super elasticity
    // structural springs and shear springs
    for (int i = 0; i < MESH_SIZE; i++) {
        for (int j = 0; j < MESH_SIZE; j++) {
            // case 1: fixed particle and loose particle
            if ((i == MESH_SIZE-1 && j == 0) || (i == MESH_SIZE-1 && j == MESH_SIZE-1)) {
                for (auto spring : springs[i][j]) {
                    int type = spring.type;
                    if (type != TYPE_STRUCTURAL && type != TYPE_SHEAR) continue;
                    Particle *p1 = spring.p1;
                    Particle *p2 = spring.p2;
                    int length = spring.length();
                    int nlength = type == TYPE_STRUCTURAL ? STRUCTURAL_NATURAL_LENGTH:SHEAR_NARTURAL_LENGTH;
                    float deformationRate = (length-nlength)/nlength;
                    if (deformationRate > CRITICAL_DEFORMATION_RATE) {
                        float m = 1.1 * nlength;
                        float n = length - m;
                        Eigen::Vector3d newPosition = (p1->position*n + p2->position*m)/length;
                        p2->position = newPosition;
                        int xp2 = spring.xp2;
                        int yp2 = spring.yp2;
                        Eigen::Vector3d vel = tmp[xp2][yp2].second;
                        tmp[xp2][yp2] = std::make_pair(newPosition, vel); 
                    }
                }
            }    
            // case 2: both loose particles        
            else {
                for (auto spring : springs[i][j]) {
                    int type = spring.type;
                    if (type != TYPE_STRUCTURAL && type != TYPE_SHEAR) continue;
                    Particle *p1 = spring.p1;
                    Particle *p2 = spring.p2;
                    float length = spring.length();
                    float nlength = type == TYPE_STRUCTURAL ? STRUCTURAL_NATURAL_LENGTH:SHEAR_NARTURAL_LENGTH; 
                    float deformationRate = (length-nlength)/nlength;
                    if (deformationRate > CRITICAL_DEFORMATION_RATE) {
                        Eigen::Vector3d middle = (p1->position + p2->position) / 2.0f;
                        float n = 0.55f * nlength;
                        float m = 0.5f * length - n;
                        p1->position = (p1->position * n + middle * m) / (0.5f * length);
                        p2->position = (p2->position * n + middle * m) / (0.5f * length);
                        int xp1 = spring.xp1;
                        int xp2 = spring.xp2;
                        int yp1 = spring.yp1;
                        int yp2 = spring.yp2;
                        Eigen::Vector3d vel = tmp[xp1][yp1].second;
                        tmp[xp1][yp1] = std::make_pair(p1->position, vel);
                        vel = tmp[xp2][yp2].second;
                        tmp[xp2][yp2] = std::make_pair(p2->position, vel);
                    }
                }
            }
        }
    }

    //---------------
        
    // fix two points
    // particles[0][0].position = particles[0][0].velocity = Eigen::Vector3d(.0f, .0f, .0f);
    // particles[0][MESH_SIZE-1].position = Eigen::Vector3d(STRUCTURAL_NATURAL_LENGTH*MESH_SIZE, .0f, .0f);
    // particles[0][MESH_SIZE-1].velocity = Eigen::Vector3d(.0f, .0f, .0f);
    // update state
    for (int i=0; i<MESH_SIZE; i++) {
        for (int j=0; j<MESH_SIZE; j++) {
            if (i == MESH_SIZE-1 && j == 0) continue;
            if (i == MESH_SIZE-1 && j == MESH_SIZE-1) continue;
            particles[i][j].position = tmp[i][j].first;
            particles[i][j].velocity = tmp[i][j].second;
        }
    }         
    // update the surface normals for next iteration
    //computeNormal();

    // clear the net force
    // for (int i=0; i<MESH_SIZE; i++) {
    //     for (int j=0; j<MESH_SIZE; j++) {            
    //         particles[i][j].netForce.setZero();
    //     }
    // }

    // // accumulate internal forces
    // // accumulateNetInternalForces();

    // // accumulate external forces
    // for (int i=0; i<MESH_SIZE; i++) {
    //     for (int j=0; j<MESH_SIZE; j++) {
    //         particles[i][j].netForce += computeNetGravitationalForce(i, j);
    //         // std::cout << particles[i][j].position[0] << ' ' << particles[i][j].position[1] << ' ' << particles[i][j].position[2] << std::endl;
    //         if(std::isnan(particles[i][j].netForce[0]) || std::isnan(particles[i][j].netForce[1]) || std::isnan(particles[i][j].netForce[2])) {
    //             //std::cout << "i, j has nan" << std::endl;
    //             //std::cout << i << ' ' << j  << std::endl;
    //             //std::cout << particles[i][j].netForce[0] << ' ' << particles[i][j].netForce[1] << ' ' << particles[i][j].netForce[2] << std::endl;
    //         }
    //         if(std::isinf(particles[i][j].netForce[0]) || std::isinf(particles[i][j].netForce[1]) || std::isinf(particles[i][j].netForce[2])) {
    //             //std::cout << "i, j has inf" << std::endl;
    //             //std::cout << i << ' ' << j  << std::endl;
    //             //std::cout << particles[i][j].netForce[0] << ' ' << particles[i][j].netForce[1] << ' ' << particles[i][j].netForce[2] << std::endl;
    //         }
    //     }
    // }    

    // // fix two points
    // // particles[MESH_SIZE-1][0].netForce.setZero();
    // // particles[MESH_SIZE-1][MESH_SIZE-1].netForce.setZero();

    // // update simulation state
    // for (int i=0; i<MESH_SIZE; i++) {
    //     for (int j=0; j<MESH_SIZE; j++) {
    //         // std::cout << particles[i][j].position[0] << ' ' << particles[i][j].position[1] << ' ' << particles[i][j].position[2] << std::endl;
    //         // std::cout << particles[i][j].velocity[0] << ' ' << particles[i][j].velocity[1] << ' ' << particles[i][j].velocity[2] << std::endl;
    //         Eigen::Vector3d acceleration = particles[i][j].netForce / PARTICLE_MASS;
    //         particles[i][j].velocity = particles[i][j].velocity + delta_t*acceleration;
    //         particles[i][j].position = particles[i][j].position + delta_t*particles[i][j].velocity;            
    //         // std::cout << particles[i][j].position[0] << ' ' << particles[i][j].position[1] << ' ' << particles[i][j].position[2] << std::endl;
    //         // std::cout << particles[i][j].velocity[0] << ' ' << particles[i][j].velocity[1] << ' ' << particles[i][j].velocity[2] << std::endl;
    //         // std::cout << acceleration[0] << ' ' << acceleration[1] << ' ' << acceleration[2] << std::endl;
    //         // exit(1);
    //     }
    // }
}

Eigen::Vector3d Cloth::computeNetGravitationalForce(int i, int j) {    
    return Eigen::Vector3d(0, -ACCELERATION_OF_GRAVITY*PARTICLE_MASS, 0);
}

void Cloth::accumulateNetInternalForces() {
    auto computeForce = [&](std::vector<Spring>&springs) {
        for (int i=0; i<springs.size(); i++) {
            Eigen::Vector3d force = springs[i].computeSpringForce();
            springs[i].p2->netForce -= force;
            springs[i].p1->netForce += force;
        }
    };
    computeForce(structural_springs);
    computeForce(shear_springs);
    computeForce(flexion_springs);
}

Eigen::Vector3d Cloth::computeNetInternalForce(int i, int j) {    
    Eigen::Vector3d F_int = Eigen::Vector3d(.0f, .0f, .0f);
    for(auto spring : springs[i][j]) {
        int type = spring.type;
        float spring_length = type == TYPE_STRUCTURAL ? STRUCTURAL_NATURAL_LENGTH:
                            type == TYPE_SHEAR ? SHEAR_NARTURAL_LENGTH:FLEXION_NATURAL_LENGTH;
        float spring_consant = type == TYPE_STRUCTURAL ? STRUCTURAL_STIFFNESS:
                            type == TYPE_SHEAR ? SHEAR_STIFFNESS:FLEXION_STIFFNESS;        
        Eigen::Vector3d particle_displacement = spring.p2->position - spring.p1->position;
        Eigen::Vector3d normal = particle_displacement/particle_displacement.norm();
        Eigen::Vector3d spring_displacement = spring_length*normal;
        Eigen::Vector3d diff = particle_displacement - spring_displacement;
        F_int = F_int + diff*spring_consant; 
    }
    return F_int;
}

// glm::vec3 Cloth::computeNetDampingForce(int i, int j) {
//     return -DAMPING_COEFF*particles[i][j]->velocity;
// }


// glm::vec3 Cloth::computeNetViscousForce(int i, int j) {
//     glm::vec3 n = particles[i][j]->normal;
//     glm::vec3 v = particles[i][j]->velocity;
//     return DAMPING_COEFF*(glm::dot(n, UNIFORM_VELOCITY_FLUID-v))*n;
// }

Eigen::Vector3d Cloth::computeNormal(int i, int j) {
    return Eigen::Vector3d(0, 0, 0);    
}

// void Cloth::computeNormal() {
//     // initialize the normal for all particles
//     for (int i=0; i<MESH_SIZE; i++) {
//         for (int j=0; j<MESH_SIZE; j++) {
//             particles[i][j]->normal = glm::vec3(.0f, .0f, .0f);
//         }
//     }

//     // compute normal for each particle
//     for (int i=0; i<MESH_SIZE-1; i++) {
//         for (int j=0; j<MESH_SIZE-1; j++) {
//             // normal of the upper triangle
//             glm::vec3 v1 = particles[i+1][j+1]->position - particles[i][j]->position;
//             glm::vec3 v2 = particles[i+1][j]->position - particles[i][j]->position;
//             glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

//             // accumulate the normal
//             particles[i][j]->normal += normal;
//             particles[i+1][j]->normal += normal;
//             particles[i+1][j+1]->normal += normal;

//             // compute the lower triangle
//             v1 = particles[i][j+1]->position - particles[i][j]->position;
//             v2 = particles[i+1][j+1]->position - particles[i][j]->position;
//             normal = glm::normalize(glm::cross(v1, v2));

//             // accumulate
//             particles[i][j]->normal += normal;
//             particles[i][j+1]->normal += normal;
//             particles[i+1][j+1]->normal += normal;
//         }
//     }

//     // normalize
//     for (int i=0; i<MESH_SIZE; i++) {
//         for (int j=0; j<MESH_SIZE; j++) {
//             particles[i][j]->normal = glm::normalize(particles[i][j]->normal);
//         }
//     }
// }


void Cloth::printState(int time) {
    float x, y, z;
    std::cout << "t = " << time << std::endl;
    std::cout << "----POSITION----" << std::endl;
    for (int i=0; i<MESH_SIZE; i++) {
        for (int j=0; j<MESH_SIZE; j++) {
            x = particles[i][j].position[0];
            y = particles[i][j].position[1];
            z = particles[i][j].position[2];
            std::cout << x << ' ' << y << ' ' << z << std::endl;
        }
        std::cout << std::endl;
    }
    // std::cout << "----VELOCITY----" << std::endl;
    // for (int i=0; i<MESH_SIZE; i++) {
    //     for (int j=0; j<MESH_SIZE; j++) {
    //         x = particles[i][j]->velocity[0];
    //         y = particles[i][j]->velocity[1];
    //         z = particles[i][j]->velocity[2];            
    //         std::cout << x << y << z << std::endl;
    //     }
    //     std::cout << std::endl;
    // }
}