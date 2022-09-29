#include <utility>
#include <cmath>
#include <iostream>
#include "vector.h"

double VectorKernel::setX(double x)
{
    double old_x = x_;
    x_ = x;

    return old_x;
}

double VectorKernel::setY(double y)
{
    double old_y = y_;
    y_ = y;
    length_ = -1;

    return old_y;    
}

double VectorKernel::setZ(double z)
{
    double temp = z_;
    z_ = z;
    length_ = -1;
    
    return temp;
}

void VectorKernel::rotate(double angle)
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

std::ostream & operator<<(std::ostream &os, Vector &vec)
{
    os << "x = " << vec.getX() << ", y = " << vec.getY() << ", z = " 
       << vec.getZ() << ", length = " << vec.getLenSq() << std::endl;
    
    return os;
}

void VectorKernel::normolize()
{
    double length = std::sqrt(getLenSq());

    x_ /= length;
    y_ /= length;
    z_ /= length;
}

bool IsEqDoubles(double a, double b) { return std::fabs(a - b) < 1e-4; }

bool Vector::operator==(const Vector &vec) const
{
    return IsEqDoubles(getX(), vec.getX()) && IsEqDoubles(getY(), vec.getY()) &&
           IsEqDoubles(getZ(), vec.getZ());
} 