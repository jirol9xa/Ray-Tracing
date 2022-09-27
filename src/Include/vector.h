#ifndef VECTOR_H
#define VECTOR_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <istream>
#include "basis.h"

class VectorKernel
{
private:
    double x_,
           y_,
           z_;
    long double length_;

public: 
    VectorKernel(double x = 0, double y = 0, double z = 0) :
                 x_(x), y_(y), z_(z), length_(-1) {}              

    double getX() const { return x_; }
    double getY() const { return y_; }
    double getZ() const { return z_; }

    double setX  (double x);
    double setY  (double y);
    double setZ  (double z);

    const VectorKernel & operator=(const VectorKernel &ker);
    
    const VectorKernel & operator+=(const VectorKernel &arg);
    const VectorKernel & operator-=(const VectorKernel &arg);
    const VectorKernel & operator*=(double coef); 

    
    void rotate(double angle);
    void normolize();

    double getLenSq() 
    {
        if (length_ < 0)
            length_ = x_*x_ + y_*y_ + z_*z_;

        return length_;
    }
};

class Vector
{
private:
    VectorKernel Kernel;

public:
    Vector(double x = 0, double y = 0, double z = 0) : 
           Kernel(x, y, z) {}

    Vector(const Vector &&vec) { Kernel = vec.Kernel; }
    Vector(const Vector &vec)  { Kernel = vec.Kernel; }

    double getX() const { return Kernel.getX(); }
    double getY() const { return Kernel.getY(); }
    double getZ() const { return Kernel.getZ(); }

    double setX(double x) { return Kernel.setX(x); }
    double setY(double y) { return Kernel.setY(y); }
    double setZ(double z) { return Kernel.setZ(z); }

    double getLenSq()           { return Kernel.getLenSq(); }
    void   normolize()          { return Kernel.normolize(); }
    void   rotate(double angle) { return Kernel.rotate(angle); };

    double getAngle(Vector &vec);

    friend Vector operator*(double coef, const Vector &vec);
    friend std::ostream & operator<<(std::ostream &os, const Vector &vec);

    const  Vector & operator=(const Vector &&vec);
    const  Vector & operator=(const Vector &vec);
           Vector   operator+(const Vector &vec);
           Vector   operator-(const Vector &vec);
           Vector   operator&(const Vector &vec);
           Vector   operator%(const Vector &vec);
           Vector   operator*(double coef);
           Vector   operator/(double coef) { return this->operator*(1 / coef); }
           Vector   operator-() { return (-1) * (*this); }

    double operator*(const Vector &arg);

    explicit operator double() const { return std::sqrt(Kernel.getX() * Kernel.getX() 
                                                   + Kernel.getY() * Kernel.getY() 
                                                   + Kernel.getZ() * Kernel.getZ()); }
    void operator+=(const Vector &arg) { Kernel += arg.Kernel; }
    void operator-=(const Vector &arg) { Kernel -= arg.Kernel; }
    void operator*=(double coef)       { Kernel *= coef; } 
};


inline const VectorKernel & VectorKernel::operator=(const VectorKernel &ker)
{
    x_ = ker.x_;
    y_ = ker.y_;
    z_ = ker.z_;

    length_ = ker.length_;

    return *this; 
}

inline const VectorKernel & VectorKernel::operator+=(const VectorKernel &ker)
{
    x_ += ker.x_;
    y_ += ker.y_;
    z_ += ker.z_;

    length_ = -1;

    return *this; 
}

inline const VectorKernel & VectorKernel::operator-=(const VectorKernel &ker)
{
    x_ -= ker.x_;
    y_ -= ker.y_;
    z_ -= ker.z_;

    length_ = -1;

    return *this; 
}

inline const VectorKernel & VectorKernel::operator*=(double coef)
{
    x_ *= coef;
    y_ *= coef;
    z_ *= coef;

    length_ = -1;

    return *this; 
}

inline const Vector & Vector::operator=(const Vector &&vec)
{
    Kernel = vec.Kernel;
    return *this;
}

inline const Vector & Vector::operator=(const Vector &vec)
{
    Kernel = vec.Kernel;
    return *this;
}

inline Vector Vector::operator*(double coef)
{
    return Vector(Kernel.getX() * coef, Kernel.getY() * coef, Kernel.getZ() * coef);
}

inline double Vector::operator*(const Vector &vec)
{
    return (Kernel.getX() * vec.Kernel.getX() + Kernel.getY() * vec.Kernel.getY() 
            + Kernel.getZ() * vec.Kernel.getZ());
}


inline Vector operator*(double coef, const Vector &vec)
{
    return Vector(vec.Kernel.getX() * coef, vec.Kernel.getY() * coef, vec.Kernel.getZ() * coef);
}

inline Vector Vector::operator+(const Vector &arg)
{
    return Vector(Kernel.getX() + arg.Kernel.getX(), Kernel.getY() + arg.Kernel.getY(),
                  Kernel.getZ() + arg.Kernel.getZ());
}

inline Vector Vector::operator-(const Vector &arg)
{
    return Vector(Kernel.getX() - arg.Kernel.getX(), Kernel.getY() - arg.Kernel.getY(),
                  Kernel.getZ() - arg.Kernel.getZ());
}

// Vector multiplication
inline Vector Vector::operator&(const Vector &vec)
{
    double x1 = Kernel.getX(), x2 = vec.Kernel.getX(),
           y1 = Kernel.getY(), y2 = vec.Kernel.getY(),
           z1 = Kernel.getZ(), z2 = vec.Kernel.getZ(); 
    
    return Vector(y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2);
}

inline Vector Vector::operator%(const Vector &vec)
{
    return Vector(Kernel.getX() * vec.Kernel.getX(), Kernel.getY() * vec.Kernel.getY(),
                  Kernel.getZ() * vec.Kernel.getZ());
}
#endif