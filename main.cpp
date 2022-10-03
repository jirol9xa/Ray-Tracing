#include <SFML/Graphics.hpp>
#include <iostream>
#include "render.h"
#include "vector.h"
#include "videoSettings.h"
#include "sphere.h"


int main() {
    using namespace Settings;  

    sf::RenderWindow window(sf::VideoMode(Width, Heigth), "Vectors");
    Render render(&window);
    Sphere sphere;
    sphere.setColor({0xCB, 0xC0, 0xFF});
    Basis basis;
    sf::Clock clock;
    Vector Light(20, 20, 15);
    Vector Eye(-20, -20, 15);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        sphere.makeSphere(basis, Light, Eye);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))     Light -= {0, 2, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))   Light += {0, 2, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  Light += {2, 0, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))   Light -= {2, 0, 0};


        render.draw(sphere.getPixels());

        window.display();
        window.clear();
    }

  return 0;
}