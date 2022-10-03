#include <algorithm>
#include <cmath>
#include <iostream>
#include "sphere.h"

void Sphere::makeSphere(Basis &basis, const Vector &Lamp, const Vector &View)
{
    using namespace Settings;

    const int X0    = basis.getX(),
              Y0    = basis.getY(),
              Z0    = basis.getZ(),
              Scale = basis.getScale();
    
    long Rad = Radius_ * Radius_ * Scale;
    
    Vector View_l = View;
    View_l *= Scale;
    Vector Light = Lamp;
    Light *= Scale;
    Vector LightColor(0xCB, 0xC0, 0xFF);

    for (int y = 0; y < Heigth; ++y, Pixels_ += Width)
        for (int x = 0; x < Width; ++x)
        {
            if (((x - X0) * (x - X0) + (y - Y0) * (y - Y0)) > Rad)
                continue;

            double z = std::sqrt(Rad - (x - X0) * (x - X0) - (y - Y0) * (y - Y0));

            Vector Normal = makeNormal(x, y, z, basis);     // Normal Vector for (x,y,z)
            Vector Ray(Light.getX()  - x, Light.getY()  - y, Light.getZ()  - z);
            Vector Eye(View_l.getX() - x, View_l.getY() - y, View_l.getZ() - z);
            Vector Color;

            double FiAngle = Ray.getAngle(Normal);
            FiAngle -= FiAngle * (FiAngle < 0);

            Vector ReflectedRay =  2 * (Normal * Ray) * Normal / Normal.getLenSq() - Ray;

            double AlAngle = ReflectedRay.getAngle(Eye);
            AlAngle -= AlAngle * (AlAngle < 0);

            Color = ((LightColor % Color_  * ((FiAngle * 0.8  +  0.2)) / 255) +
                      LightColor * std::pow(AlAngle, 15) * 1) / 255; 

            if      (Color.getX() > 1) Color.setX(1);
            else if (Color.getX() < 0) Color.setX(0);
            if      (Color.getY() > 1) Color.setY(1);
            else if (Color.getY() < 0) Color.setY(0);
            if      (Color.getZ() > 1) Color.setZ(1);
            else if (Color.getZ() < 0) Color.setZ(0);

            Pixels_[x] = 0xFF000000 + (int(Color.getX() * 255.0) << 16) + 
                        (int(Color.getY() * 255.0) << 8) + int(Color.getZ() * 255.0);           
        }

    Pixels_ -= Width * Heigth;
}

Vector Sphere::makeNormal(double x, double y, double z, Basis basis)
{
    return Vector(x - basis.getX(), y - basis.getY(), z - basis.getZ());
}

void Sphere::makePositiveVec(Vector &vec)
{
    double Coord = vec.getX();
    if (Coord < 0)
        vec.setX(-Coord);

    Coord = vec.getY();
    if (Coord < 0)
        vec.setY(-Coord);

    Coord = vec.getZ();
    if (Coord < 0)
        vec.setZ(-Coord);
}

void Sphere::setColor(const Vector &vec)
{
    Color_ = vec;
}