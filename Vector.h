#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>
#include <cmath>
#define PI 3.14159265359

using namespace std;

class Vector{
    private:
        double aux;
    public:
        double x;
        double y;
        double z;
        Vector();
        Vector(double x,double y,double z);
        virtual ~Vector();
        void setDirection(double theta,double phi);
        void setPolar(double theta,double phi,double mod);
		void setRect(double x,double y,double z);
		void increment(Vector inc);
		double getAbs();
		void setAbs(double val);
		void mult(double val);
		void randomize(double val);
        double cosd(double ang);
        double sind(double ang);
};

#endif // VECTOR_H
