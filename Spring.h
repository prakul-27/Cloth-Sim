#include "Particle.h"

#define TYPE_STRUCTURAL 0
#define TYPE_SHEAR 1
#define TYPE_FLEXION 2

#define STRUCTURAL_STIFFNESS 20.0f
#define STRUCTURAL_NATURAL_LENGTH 5.0f

#define SHEAR_STIFFNESS 20.0f
#define SHEAR_NARTURAL_LENGTH (STRUCTURAL_NATURAL_LENGTH * sqrt(2.0f))

#define FLEXION_STIFFNESS 20.0f
#define FLEXION_NATURAL_LENGTH (STRUCTURAL_NATURAL_LENGTH * 2)

class Spring{
public:
    Spring(int type, Particle *p1, Particle *p2, int xp1, int yp1, int xp2, int yp2);
    Spring(int type);
    float length();
    Eigen::Vector3d computeSpringForce();
    int type;        
    Particle *p1;
    Particle *p2;
    int xp1, yp1, xp2, yp2;

    //---new added---

    void Draw(void);
    //float ComputeLength(void);

};