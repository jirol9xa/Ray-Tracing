#ifndef FIGURE_H
#define FIGURE_H

#include <cmath>
#include "vector.h"
#include "Line.h"

enum RayStatuses
{
    NO_INTERSEC    = -1,
    INTERSEC       = 0,
    INTERSEC_LIGHT = 1, 
};


class Figure
{
protected:
    Vector Center_;
    Vector Color_;
    double Mirroring_;
    double LightIntens_;
    bool   IsLightSrc_;

public:
    Figure(double x, double y, double z, double mirroring = 0.8, 
           bool isLightSrc = false, double Intens = 0) : Center_(x, y, z),
           Color_(1, 1, 1), Mirroring_(mirroring), IsLightSrc_(isLightSrc),
           LightIntens_(Intens) {}

    // return {-1, -1, -1} if no intersec
    virtual int          tryObject  (Line &Ray, double coef) = 0;
    virtual const Vector getIntersec(Line &Ray) = 0;

    virtual void   setLightSrc(bool isLightSrc)  { IsLightSrc_  = isLightSrc; }
    virtual void   setLightInt(double Intens)    { LightIntens_ = Intens; }
    virtual double getMirroring()  { return Mirroring_; }
    virtual bool   IsLightSrc()    { return IsLightSrc_; }

    virtual ~Figure() {};
};

#endif
