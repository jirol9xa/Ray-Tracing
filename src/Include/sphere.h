#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"
#include "figure.h"

class Sphere: public Figure
{ 
private:
    double Radius_;
public:
    Sphere(double x, double y, double z, double r) : Figure(x, y, z), Radius_(r)  {}

    void setColor(const Vector &vec) { Color_ = vec; }
    void setMirroring(double coef)   { Mirroring_ = coef; }

    virtual int          tryObject  (Line &ray, double coef);
    virtual const Vector getIntersec(Line &Ray);

    Vector makeNormal(const Vector &vec);
};

#endif 