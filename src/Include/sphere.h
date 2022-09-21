#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"

class Sphere
{
private:
    uint32_t *Pixels_;
    int Radius_;
    Vector Color_;
public:
    Sphere(uint32_t *Pixels, int radius = 50) : 
        Pixels_(Pixels), Radius_(radius) {} 
    Sphere(int radius = 50) : Radius_(radius) 
    { 
        Color_ = {255, 255, 255};
        Pixels_ = new uint32_t[Settings::Width * Settings::Heigth];
    
    }
    ~Sphere() { delete [] Pixels_; }

    void makeSphere(Basis &basis, const Vector &Lamp, const Vector &View);

    const uint32_t *getPixels() { return Pixels_; }

private:
    Vector makeNormal(double x, double y, double z, Basis basis);
    void   makePositiveVec(Vector &vec);
};

#endif