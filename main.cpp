#include <SFML/Graphics.hpp>
#include <iostream>
#include "render.h"
#include "vector.h"
#include "videoSettings.h"
#include "sphere.h"
#include "scene.h"
#include "plane.h"

int main() {
    using namespace Settings;  

    sf::RenderWindow window(sf::VideoMode(Width, Heigth), "Vectors");
    Render render(&window);
    Basis basis;
    sf::Clock clock;
    Vector Light(20, 20, 20);
    Vector Eye(basis.getX(), basis.getY(), basis.getZ() + 1000);

    Sphere sphere1(basis.getX() - 100, basis.getY() - 100, basis.getZ(), 70);
    Sphere sphere2(basis.getX() + 100, basis.getY() + 100, basis.getZ() + 100, 70);

    sphere1.setColor({0.02, 0.01, 0.01});
    sphere1.setLightInt(1);

    sphere2.setLightSrc(true);
    sphere2.setColor({1, 1, 1});

    Plane plane1({0, -1, 0}, -1500);
    Plane plane2({0, -1, 0},  1500);

    plane1.setLightSrc(true);
    plane1.setLightInt(0.4);

    // plane2.setLightSrc(true);
    plane2.setLightInt(0.4);
    plane2.setColor({0.3, 0, 0.3});

    Scene scene(Eye, basis);

    scene.addFigure(&sphere1);
    scene.addFigure(&sphere2);
    scene.addFigure(&plane1);
    scene.addFigure(&plane2);

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
        // std::cout << "Frame drew\n";
    }

  return 0;
}