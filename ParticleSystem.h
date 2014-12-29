#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Particle.h"

class ParticleSystem : public Particle
{
    public:
        double width;
        double gravity;
        int num_particles;
        Particle* particle;
        ParticleSystem();
        virtual ~ParticleSystem();
        void init(int p_size,int lifeLimit,Vector birthMin,Vector vel,double rndVel,int num_particles,double width,double gravity,double absVel);
        void setBirth(Vector birthMin);
        void update();
};

#endif // PARTICLESYSTEM_H
