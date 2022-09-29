#include <SFML/Graphics.hpp>
#include <iostream>
#include "render.h"
#include "vector.h"
#include "videoSettings.h"
#include "sphere.h"
#include "scene.h"

int main() {
    using namespace Settings;  

    sf::RenderWindow window(sf::VideoMode(Width, Heigth), "Vectors");
    Render render(&window);
    Basis basis;
    sf::Clock clock;
    Vector Light(20, 20, 20);
    Vector Eye(basis.getX(), basis.getY(), basis.getZ() + 1000);

    Sphere sphere1(basis.getX(), basis.getY(), basis.getZ(), 30);
    Sphere sphere2(basis.getX() + 100, basis.getY() + 100, basis.getZ() + 100, 30);

    // sphere1.setLightSrc(true);
    sphere1.setColor({255, 255, 0});

    sphere2.setLightSrc(true);
    sphere2.setColor({0, 255, 0});

    Scene scene(Eye, basis);

    scene.addFigure(&sphere1);
    scene.addFigure(&sphere2);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        // sphere.makeSphere(basis, Light, Eye);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))     Light -= {0, 2, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))   Light += {0, 2, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  Light += {2, 0, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))   Light -= {2, 0, 0};

        render.draw(scene.drawScene());

        window.display();
        window.clear();
        std::cout << "Frame drew\n";
    }

  return 0;
}