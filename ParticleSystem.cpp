#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(){};

ParticleSystem::~ParticleSystem(){
    free(particle);
};

void ParticleSystem::init(int p_size,int lifeLimit,Vector birthMin,Vector vel,double rndVel,int num_particles,double width,double gravity,double absVel){
	this->gravity       = gravity;
	this->width         = width;
	this->num_particles = num_particles;
	this->rndVel        = rndVel;
	this->initVel       = vel;
	initVel.setAbs(absVel);
	this->p_size	    = p_size;
	this->lifeLimit	    = lifeLimit;
	this->birthMin	    = birthMin;
	this->birthMax	    = Vector(birthMin.x+width,birthMin.y+width,birthMin.z+width);
    this->num_particles = num_particles;
    particle = (Particle*)malloc(num_particles*sizeof(Particle));
    for (int i = 0; i < num_particles; i++){
        particle[i].init(p_size,lifeLimit,birthMin,birthMax,rndVel);
        particle[i].accel = Vector(0,0,gravity);
    }
};

void ParticleSystem::setBirth(Vector birthMin){
	this->birthMin	    = birthMin;
	this->birthMax	    = Vector(birthMin.x+width,birthMin.y+width,birthMin.z+width);
};


void ParticleSystem::update(){
	birthMax	        = Vector(birthMin.x+width,birthMin.y+width,birthMin.z+width);
    for (int i = 0; i < num_particles; i++){
        particle[i].birthMin    = birthMin;
        particle[i].birthMax    = birthMax;
        particle[i].lifeLimit   = lifeLimit;
        particle[i].rndVel      = rndVel;
        particle[i].initVel     = initVel;
        particle[i].initVel     = initVel;
        particle[i].update();
    }
};
