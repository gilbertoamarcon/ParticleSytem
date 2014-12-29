#ifndef PARTICLE_H
#define PARTICLE_H
#include <stdlib.h>
#include "Vector.h"

using namespace std;

class Particle{
    private:
        int updateColor(double scalar);
        void birth();
    public:
        bool firstCycle;
        int lifeLimit;
        int life;
        double lifePercent;
        double p_size;
		double rndVel;
		Vector color;
		Vector birthMin;
		Vector birthMax;
		Vector initVel;
		Vector pos;
		Vector vel;
		Vector accel;
        Particle();
        virtual ~Particle();
        void init(int p_size,int lifeLimit,Vector birthMin,Vector birthMax,double rndVel);
        void update();
        void collisionDetect();
};

#endif // PARTICLE_H
