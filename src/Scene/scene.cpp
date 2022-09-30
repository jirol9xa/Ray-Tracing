#include "scene.h"
#include "sphere.h"

// remove after debug
#include <iostream>
#include <cmath>

Vector Scene::processLight(Line &Ray)
{
    double Coef       = 1;
    bool   IsIntersec = false;

    // Lambda added for escaping nested cycles without goto
    [&]() 
    {
        for (int i = 0; i < 4; ++i)
        {
            // We need to know which objects does Ray intersect        
            int status = RayStatuses::NO_INTERSEC;
            for (auto &Figure : Figures_)
            {
                status = Figure->tryObject(Ray, Coef);

                if (status != RayStatuses::NO_INTERSEC)
                {
                    IsIntersec = true;
                    Coef      *= Figure->getMirroring();

                    if (status == RayStatuses::INTERSEC_LIGHT)
                        return;

                    break;
                }
            }
            // If ray does not intersect any object, just end cycle
            // and draw it into sky color
            if (status == RayStatuses::NO_INTERSEC)
            {
                Ray.Color_ = SkyBox_;
                return;
            }
        }
    }();
    
    return Ray.Color_;
}

void normolizeColor(Vector &Color)
{
    if      (Color.getX() > 1) Color.setX(1);
    else if (Color.getX() < 0) Color.setX(0);
    if      (Color.getY() > 1) Color.setY(1);
    else if (Color.getY() < 0) Color.setY(0);
    if      (Color.getZ() > 1) Color.setZ(1);
    else if (Color.getZ() < 0) Color.setZ(0);
}

uint32_t * Scene::drawScene()
{
    using Settings::Width;
    using Settings::Heigth;

    for (int y = 0; y < Heigth; ++y, Pixels_ += Width)
        for (int x = 0; x < Width; ++x)
        {
            Line Ray{ViewPoint_, {x - ViewPoint_.getX(), y - ViewPoint_.getY(),
                             /*z*/0 - ViewPoint_.getZ()}};
            Vector Color = processLight(Ray);
            // std::cout << Color << '\n';

            normolizeColor(Color);

            Pixels_[x] = Pixels_[x] = 0xFF000000 + (int(Color.getZ() * 255) << 16) + 
                         (int(Color.getY() * 255) << 8) + int(Color.getX() * 255);
        }

    Pixels_ -= Width * Heigth;
    return Pixels_;
}
