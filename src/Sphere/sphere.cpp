#include "sphere.h"
#include <cmath>

// Delete after debug
#include <iostream>

int Sphere::tryObject(Line &Ray, double coef)
{
    // Need to calculate point of intersection of sphere and Ray
    Vector IntersecPoint = getIntersec(Ray);
    if (IntersecPoint == Ray.StartPoint_)
        return RayStatuses::NO_INTERSEC;

    Vector Normal = makeNormal(IntersecPoint);    
    double DirectNormalAngl = Ray.Direct_ ^ Normal;

    Ray.Direct_ -= 2 * Normal * (Ray.Direct_ * Normal) / Normal.getLenSq();
    double ReflectedStartPnt = Ray.Direct_ ^ Ray.StartPoint_;
    Ray.StartPoint_ = IntersecPoint;

    // if (DirectNormalAngl > 0)
    //     DirectNormalAngl = 0;
    // if (ReflectedStartPnt > 0)
    //     ReflectedStartPnt = 0;

    DirectNormalAngl  -= DirectNormalAngl  * (DirectNormalAngl  > 0);
    ReflectedStartPnt -= ReflectedStartPnt * (ReflectedStartPnt > 0);

    if (IsLightSrc_)
    {        
        Ray.IsCatchLightSourse = true;
        Ray.Color_ = coef * ((Ray.Color_ % Color_) * (-DirectNormalAngl + 0.002));// +
                 //Color_ * (std::pow(-ReflectedStartPnt, 15) * 5));
        
        return RayStatuses::INTERSEC_LIGHT;   
    }

    Ray.Color_ = Ray.Color_ % Color_ * coef;

    return RayStatuses::INTERSEC;
}

const Vector Sphere::getIntersec(Line &Ray)
{
    Vector S = Center_ - Ray.StartPoint_;

    double a = Ray.Direct_ * Ray.Direct_,
           b = -2 * Ray.Direct_ * S,
           c =  S * S - Radius_ * Radius_;

    double Diskr = b * b - 4 * a * c;
    if (Diskr <= 0)
        return Ray.StartPoint_; // if we have no intersection
    
    double SqrtDiskr = std::sqrt(Diskr);
    double root1 = (-b + SqrtDiskr) / (2 * a),
           root2 = (-b - SqrtDiskr) / (2 * a);
    
    double root;
    if (root1 < root2 && root1 > 0)
        root = root1;
    else if (root2 > 0)
        root = root2;
    else 
        return Ray.StartPoint_; // if we have no intersection

    return Ray.Direct_ * root + Ray.StartPoint_;
}

Vector Sphere::makeNormal(const Vector &Vec)
{
    return Vec - Center_;
}