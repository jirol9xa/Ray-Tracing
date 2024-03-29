#ifndef VECTOR_H
#define VECTOR_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <istream>
#include "basis.h"


class Vector
{
private:
    double x_,
           y_,
           z_;
    long double length_;

public:
    Vector(double x = 0, double y = 0, double z = 0) : 
           x_(x), y_(y), z_(z), length_(-1) {}

    Vector(const Vector &&vec)  :  x_(vec.x_), y_(vec.y_), z_(vec.z_),
                                   length_(vec.length_)   {}
    Vector(const Vector &vec)   :  x_(vec.x_), y_(vec.y_), z_(vec.z_),
                                   length_(vec.length_) {}

    double getX() const { return x_; }
    double getY() const { return y_; }
    double getZ() const { return z_; }

    double setX(double x);
    double setY(double y);
    double setZ(double z);

    double getLenSq() 
    {
        if (length_ < 0)
            length_ = x_*x_ + y_*y_ + z_*z_;

        return length_;
    }

    void normolize();
    void rotate(double angle);
    double getAngle(Vector &vec);

    friend Vector operator*(double coef, const Vector &vec);
    friend std::ostream & operator<<(std::ostream &os, const Vector &vec);

    const  Vector & operator=(const Vector &&vec);
    const  Vector & operator=(const Vector &vec);
           Vector   operator+(const Vector &vec);
           Vector   operator-(const Vector &vec);
           Vector   operator&(const Vector &vec);
           Vector   operator%(const Vector &vec);
           Vector   operator/(double coef);
           Vector   operator*(double coef);
           Vector   operator-();

    double operator*(const Vector &arg);

    explicit operator double() const { return std::sqrt(x_*x_ + y_*y_ + z_*z_); }
    const Vector & operator+=(const Vector &arg);
    const Vector & operator-=(const Vector &arg);
    const Vector & operator*=(double coef); 
};


inline const Vector & Vector::operator=(const Vector &&vec)
{
    x_      = vec.x_;
    y_      = vec.y_;
    z_      = vec.z_;
    length_ = vec.length_;

    return *this;
}

inline const Vector & Vector::operator=(const Vector &vec)
{
    x_      = vec.x_;
    y_      = vec.y_;
    z_      = vec.z_;
    length_ = vec.length_;

    return *this;
}

inline Vector Vector::operator*(double coef)
{
    return Vector(x_ * coef, y_ * coef, z_ * coef);
}

inline double Vector::operator*(const Vector &vec)
{
    return (x_ * vec.x_ + y_ * vec.y_ + z_ * vec.z_);
}


inline Vector operator*(double coef, const Vector &vec)
{
    return Vector(vec.x_ * coef, vec.y_ * coef, vec.z_ * coef);
}

inline Vector Vector::operator+(const Vector &arg)
{
    return Vector(x_ + arg.x_, y_ + arg.y_, z_ + arg.z_);
}

inline const Vector & Vector::operator+=(const Vector &arg)
{
    x_ += arg.x_;
    y_ += arg.y_;
    z_ += arg.z_;

    length_ = -1;
    return *this;
}

inline Vector Vector::operator-(const Vector &arg)
{
    return Vector(x_ - arg.x_, y_ - arg.y_, z_ - arg.z_);
}

inline Vector Vector::operator-()
{
    return (-1) * (*this);
}

inline Vector Vector::operator&(const Vector &vec)
{
    double x2 = vec.x_,
           y2 = vec.y_,
           z2 = vec.z_; 
    
    return Vector(y_ * z2 - z_ * y2, z_ * x2 - x_ * z2, x_ * y2 - y_ * x2);
}

inline Vector Vector::operator%(const Vector &vec)
{
    return Vector(x_ * vec.x_, y_ * vec.y_, z_ * vec.z_);
}

inline const Vector & Vector::operator-=(const Vector &arg)
{

    x_ -= arg.x_;
    y_ -= arg.y_;
    z_ -= arg.z_;

    length_ = -1;
    return *this;
}

inline Vector Vector::operator/(double coef)
{
    return this->operator*(1 / coef);
}

inline const Vector & Vector::operator*=(double coef)
{
    x_ *= coef;
    y_ *= coef;
    z_ *= coef;

    length_ = -1;
    return *this;
}

#endif