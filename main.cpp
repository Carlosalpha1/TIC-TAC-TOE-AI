#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

const std::string WND_TITLE = "TIC-TAC-TOE AI";

int main()
{
    sf::Texture bg_texture;
    bg_texture.loadFromFile("assets/img/background.png");
    sf::Sprite background(bg_texture);
    sf::VideoMode vm(bg_texture.getSize().x, bg_texture.getSize().y);

    sf::RenderWindow window;
    window.create(vm, WND_TITLE);
    window.setFramerateLimit(20);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Updates
        window.clear();
        window.draw(background);
        window.display();
    }

    return EXIT_SUCCESS;
}