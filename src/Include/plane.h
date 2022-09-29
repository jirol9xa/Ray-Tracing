#ifndef PLANE_H
#define PLANE_H

#include "figure.h"
#include "vector.h"

class Plane : public Figure
{
private:
    Vector Normal_;
    double D_;

public:
    Plane(Vector Normal, double D) : Figure(Normal.getX(), Normal.getY(), Normal.getZ(), true),
                                     Normal_(Normal), D_(D) {}

    void setColor(const Vector &vec)    { Color_ = vec; }

    virtual int          tryObject  (Line &ray, double coef);
    virtual const Vector getIntersec(Line &Ray);
};

#endif