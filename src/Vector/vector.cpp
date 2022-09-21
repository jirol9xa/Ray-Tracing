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

double Vector::getAngle(Vector &vec)
{
    double LengthMul = std::sqrt(this->getLenSq() * vec.getLenSq());

    return (*this * vec) / LengthMul;
}

std::ostream & operator<<(std::ostream &os, const Vector &vec)
{
    os << "x = " << vec.x_ << ", y = " << vec.y_ << ", z = " << vec.z_ << ", length = "
       << vec.length_ << std::endl;
    
    return os;
}


void Vector::normolize()
{
    double length = std::sqrt(getLenSq());

    x_ /= length;
    y_ /= length;
    z_ /= length;
}