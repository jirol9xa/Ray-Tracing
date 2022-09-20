#include <utility>
#include <cmath>
#include <iostream>
#include "vector.h"

double Vector::setX(double x)
{
    double old_x = x_;
    x_ = x;
    length_ = -1;

    return old_x;
}

double Vector::setY(double y)
{
    double old_y = y_;
    y_ = y;
    length_ = -1;

    return old_y;    
}

double Vector::setZ(double z)
{
    double temp = z_;
    z_ = z;
    length_ = -1;
    
    return temp;
}

void Vector::rotate(double angle)
{
    double sin = std::sin(angle),
           cos = std::cos(angle);
    
    double x_temp = x_, y_temp = y_;

    x_ = x_temp * cos - y_temp * sin;
    y_ = x_temp * sin + y_temp * cos;
    // OZ меня не е6ет
    length_ = -1;

    return;
}
