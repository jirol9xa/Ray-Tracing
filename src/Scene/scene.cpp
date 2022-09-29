#include "scene.h"
#include "sphere.h"

// remove after debug
#include  <iostream>

Vector Scene::processLight(Line &Ray)
{
    double coef = 1;

    for (int i = 0; i < 4; ++i)
    {
        int status = RayStatuses::NO_INTERSEC;
        for (auto &Figure : Figures_)
        {
            status = Figure->tryObject(Ray, coef);
            coef  *= Figure->getMirroring();
            
            if (status == RayStatuses::INTERSEC_LIGHT)
                return Ray.Color_;
            // We need to know which objects does Ray intersect        
        }

        // If ray does not intersect any object, just end cycle
        if (status == NO_INTERSEC)
            return {0, 0, 0};
    }

    return Ray.Color_;
}

void normolizeColor(Vector &Color)
{
    if      (Color.getX() > 255) Color.setX(255);
    else if (Color.getX() < 0)   Color.setX(0);
    if      (Color.getY() > 255) Color.setY(255);
    else if (Color.getY() < 0)   Color.setY(0);
    if      (Color.getZ() > 255) Color.setZ(255);
    else if (Color.getZ() < 0)   Color.setZ(0);
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

            Pixels_[x] = Pixels_[x] = 0xFF000000 + (int(Color.getX()) << 16) + 
                         (int(Color.getY()) << 8) + int(Color.getZ());
        }

    Pixels_ -= Width * Heigth;
    return Pixels_;
}
