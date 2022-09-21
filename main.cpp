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
    Basis basis;
    sf::Clock clock;
    Vector Light(10, 25, 20);
    Vector Eye(0, 14, 15);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        sphere.makeSphere(basis, Light, Eye);
        //Light.rotate(0.2);

        render.draw(sphere.getPixels());

        window.display();
        window.clear();

        //std::cout << "New frame\n";
    }

  return 0;
}