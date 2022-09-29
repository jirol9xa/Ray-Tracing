#include "sphere.h"
#include <cmath>

// Delete after debug
#include <iostream>

int Sphere::tryObject(Line &Ray, double coef)
{
    // Need to calculate point of intersection of sphere and Ray
    Vector IntersecPoint = getIntersec(Ray);
    if (IntersecPoint.getX() == 0 && IntersecPoint.getY() == 0 &&
        IntersecPoint.getZ() == 0)
        return RayStatuses::NO_INTERSEC;

    Vector Normal = makeNormal(IntersecPoint);
    
    double Direct_Normal_Angl = Ray.Direct_ ^ Normal;

    Ray.Direct_     = 2 * (Ray.Direct_ ^ Normal) * Normal - Ray.Direct_; // Ray = ReflectedRay
    Ray.StartPoint_ = IntersecPoint;
    
    if (isLightSrc_)
    {
        Ray.Color_ = coef * (Ray.Color_ % Color_);// * Direct_Normal_Angl;
        return RayStatuses::INTERSEC_LIGHT;   
    }

    return RayStatuses::INTERSEC;
}

const Vector Sphere::getIntersec(Line &Ray)
{
    Vector S = Center_ - Ray.StartPoint_;

    double a = Ray.Direct_ * Ray.Direct_,
           b = -2 * Ray.Direct_ * S,
           c =  S * S - Radius_ * Radius_;

    double Diskr = b * b - 4 * a * c;
    if (Diskr < 0)
        return {0, 0, 0};
    
    double SqrtDiskr = std::sqrt(Diskr);
    double root1 = (-b + SqrtDiskr) / (2 * a),
           root2 = (-b - SqrtDiskr) / (2 * a);
    
    double root;
    if (root1 < root2 && root1 > 0)
        root = root1;
    else if (root2 > 0)
        root = root2;
    else 
        return {0, 0, 0};

    // Vector S = Center_ - Ray.StartPoint_;

    // double Direct_S     = Ray.Direct_ * S;
    // double Direct_LenSq = Ray.Direct_.getLenSq();
    // double Diskr        = Direct_S * Direct_S - Direct_LenSq * 
    //                       (S.getLenSq() - Radius_ * Radius_);

    // if (Diskr < 0)
    //     return {0, 0, 0};

    // double sqrt_diskr = std::sqrt(Diskr);
    // double root1      = (Direct_S + sqrt_diskr) / Direct_LenSq,
    //        root2      = (Direct_S - sqrt_diskr) / Direct_LenSq;
    // double root;
    // if (root1 < root2 && root1 > 0)
    //     root = root1;
    // else if (root2 > 0)
    //     root = root2;
    // else 
    //     return {0, 0, 0};

    return Ray.Direct_ * root + Ray.StartPoint_;
}

Vector Sphere::makeNormal(const Vector &vec)
{
    return Vector(vec.getX() - Center_.getX(), vec.getY() - Center_.getY(),
                  vec.getZ() - Center_.getZ());
}