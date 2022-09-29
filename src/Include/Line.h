#ifndef LINE_H
#define LINE_H

#include "vector.h"

class Line
{
public:
    Vector StartPoint_;
    Vector Direct_;
    Vector Color_;
    bool   IsCatchLightSourse;

    Line(Vector StartPoint, Vector Direct, Vector Color = {255, 255, 255}) : StartPoint_(StartPoint),
        Direct_(Direct), Color_(Color), IsCatchLightSourse(false) {}  
};

#endif