#include "render.h"

void Render::draw(Vector &vec) const
{
    double X0    = basis_.getX(),
           Y0    = basis_.getY(),
           absX  = X0 + vec.getX() * basis_.getScale(),
           absY  = Y0 - vec.getY() * basis_.getScale();

    sf::Vertex mainLine[] = 
    {
        sf::Vertex(sf::Vector2f(X0, Y0)),
        sf::Vertex(sf::Vector2f(absX, absY)),
    };
    window_->draw(mainLine, 2, sf::Lines);
}