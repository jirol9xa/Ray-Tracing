#include "plane.h"

// Delete after debug
#include <iostream>

int Plane::tryObject(Line &Ray, double coef)
{
    Vector Intersec = getIntersec(Ray);
    if (Ray.StartPoint_ != Intersec)
    {
        Vector ReflectRay = Ray.Direct_ - 2 * Normal_ * (Ray.Direct_ * Normal_) / Normal_.getLenSq();

        if (!IsLightSrc_)
        {
            Ray.Color_      = Ray.Color_ % Color_ * coef;
            Ray.Direct_     = ReflectRay;
            Ray.StartPoint_ = Intersec;

            return RayStatuses::INTERSEC;
        }

        double DirectNormalAngl  = Ray.Direct_ ^ Normal_;
        if (DirectNormalAngl > 0)
            DirectNormalAngl = 0;
        double RefVecSrttPntAngl = ReflectRay ^ Ray.StartPoint_;
        if (RefVecSrttPntAngl > 0)
            RefVecSrttPntAngl = 0;
        
        Ray.IsCatchLightSourse = true;
        Ray.Color_ = coef * ((Ray.Color_ % Color_) * LightIntens_ * 
                 (-DirectNormalAngl + 0.8));// + Color_ * 
                 //(std::pow(-RefVecSrttPntAngl, 15) * 5));

        return RayStatuses::INTERSEC_LIGHT;        
    }

    return RayStatuses::NO_INTERSEC;
}

const Vector Plane::getIntersec(Line &Ray)
{
    Vector Normal_Strt_Pnt = Normal_ % Ray.StartPoint_;
    Vector Normal_Direct   = Normal_ % Ray.Direct_;

    double t = -(Normal_Strt_Pnt.getX() + Normal_Strt_Pnt.getY() + 
                 Normal_Strt_Pnt.getZ() + D_) / (Normal_Direct.getX() + 
                 Normal_Direct.getY() + Normal_Direct.getZ());

    if (t > 0)
        return Ray.StartPoint_ + Ray.Direct_ * t;
    else
        return Ray.StartPoint_;
}
