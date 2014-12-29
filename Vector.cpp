#include "Vector.h"

Vector::Vector(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
};

Vector::Vector(double x,double y,double z){
	this->x = x;
	this->y = y;
	this->z = z;
};

Vector::~Vector(){};

void Vector::setDirection(double theta,double phi){
    aux     = getAbs();
    x       = sind(theta)*sind(phi);
    y       = cosd(theta)*sind(phi);
    z       = cosd(phi);
    setAbs(aux);
};

void Vector::setPolar(double theta,double phi,double mod){
    x = mod*sind(theta)*sind(phi);
    y = mod*cosd(theta)*sind(phi);
    z = mod*cosd(phi);
};

void Vector::setRect(double x,double y,double z){
	this->x = x;
	this->y = y;
	this->z = z;
};

void Vector::increment(Vector inc){
	x += inc.x;
	y += inc.y;
	z += inc.z;
};

double Vector::getAbs(){
    return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
};

void Vector::setAbs(double val){
    aux = getAbs();
	x *= val/aux;
	y *= val/aux;
	z *= val/aux;
};

void Vector::mult(double val){
	x *= val;
	y *= val;
	z *= val;
};

void Vector::randomize(double val){
	x += val*getAbs()*((double)rand()/RAND_MAX-0.5);
	y += val*getAbs()*((double)rand()/RAND_MAX-0.5);
	z += val*getAbs()*((double)rand()/RAND_MAX-0.5);
};

double Vector::cosd(double ang){
    return cos(PI*ang/180);
}

double Vector::sind(double ang){
    return sin(PI*ang/180);
}
