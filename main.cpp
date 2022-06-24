//  Copyright (C) 2022  Carlos Caminero (Carlosalpha1)

//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <iostream>
#include <string>
#include "game_entities.hpp"
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

    GraphicsTable table;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i position = sf::Mouse::getPosition(window);            
            sf::Vector2i transform_pose = table.realPose2DiscretePose(position);

            int row = transform_pose.x;
            int col = transform_pose.y;
            
            if (table.getPiece(row, col) == '-') {
                table.setPosePiece(row, col, 'O');

                auto state = table.getState();
                
                if (table.isFull()) {
                    table.clear();
                }
            }
        }

        // Updates
        window.clear();
        window.draw(background);
        window.draw(table);
        window.display();
    }

    return EXIT_SUCCESS;
}
