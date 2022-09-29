#ifndef FIGURE_H
#define FIGURE_H

#include "vector.h"
#include "Line.h"

enum RayStatuses
{
    NO_INTERSEC    = 0,
    INTERSEC       = -1,
    INTERSEC_LIGHT = 1, 
};


class Figure
{
protected:
    Vector Center_;
    Vector Color_;
    double mirroring_;
    bool   isLightSrc_;

public:
    Figure(double x, double y, double z, double mirroring = 0.8, 
           bool isLightSrc = false) : Center_(x, y, z), Color_(255, 255, 255),
           mirroring_(mirroring), isLightSrc_(isLightSrc) {}

    // return {-1, -1, -1} if no intersec
    virtual int          tryObject  (Line &Ray, double coef) = 0;
    virtual const Vector getIntersec(Line &Ray) = 0;

    virtual void setLightSrc(bool isLightSrc)  { isLightSrc_ = isLightSrc; }
    virtual double getMirroring() { return mirroring_; }

    virtual ~Figure() {};
};

#endif
