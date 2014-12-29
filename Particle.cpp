#include "Particle.h"

Particle::Particle(){};

Particle::~Particle(){};

void Particle::init(int p_size,int lifeLimit,Vector birthMin,Vector birthMax,double rndVel){
	this->rndVel        = rndVel;
	this->firstCycle    = true;
	this->initVel       = Vector(0,0,0);
	this->p_size	    = p_size;
	this->lifeLimit	    = lifeLimit;
	this->birthMin	    = birthMin;
	this->birthMax	    = birthMax;
	life			    = lifeLimit*rand()/RAND_MAX;
	lifePercent		    = 0;
	accel.setRect(0,0,0);
	birth();
}

void Particle::birth(){
    pos.x   = (double)rand()*(birthMax.x - birthMin.x)/RAND_MAX + birthMin.x;
    pos.y   = (double)rand()*(birthMax.y - birthMin.y)/RAND_MAX + birthMin.y;
    pos.z   = (double)rand()*(birthMax.z - birthMin.z)/RAND_MAX + birthMin.z;
	vel     = initVel;
	vel.randomize(rndVel);
}

void Particle::update(){
	life++;
	if (life > lifeLimit){
        firstCycle  = false;
        life        = 0;
        birth();
	}else{
        vel.increment(accel);
        pos.increment(vel);
        collisionDetect();
	}
    lifePercent = (double)life/lifeLimit;
    updateColor(lifePercent);
}

void Particle::collisionDetect(){
    if (pos.z < 0){
        pos.z *= -1;
        vel.x *=  0.9;
        vel.y *=  0.9;
        vel.z *= -0.75;
        vel.randomize(0.2);
    }
    double aux = 5;
    if (pos.x > aux){
        pos.x -= pos.x-aux;
        vel.x *=  -0.5;
    }else if (pos.x < -aux){
        pos.x -= pos.x+aux;
        vel.x *=  -0.5;
    }
    if (pos.y > aux){
        pos.y -= pos.y-aux;
        vel.y *=  -0.5;
    }else if (pos.y < -aux){
        pos.y -= pos.y+aux;
        vel.y *=  -0.5;
    }
}

int Particle::updateColor(double scalar){
    if(scalar < 0.2){
        color.x = 0.5+scalar*2.5;
        color.y = 0;
        color.z = 0;
        return 0;
    }
    if(scalar < 0.4){
        color.x = 1;
        color.y = (scalar-0.2)*5;
        color.z = 0;
        return 0;
    }
    if(scalar < 0.6){
        color.x = 1-(scalar-0.4)*5;
        color.y = 1;
        color.z = (scalar-0.4)*5;
        return 0;
    }
    if(scalar < 0.8){
        color.x = 0;
        color.y = 1-(scalar-0.6)*5;
        color.z = 1;
        return 0;
    }
    color.x = 0;
    color.y = 0;
    color.z = 1-(scalar-0.8)*2.5;
    return 0;
}
