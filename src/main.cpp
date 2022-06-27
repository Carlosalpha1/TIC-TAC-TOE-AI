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
#include "game_brain.hpp"
#include <SFML/Graphics.hpp>

const std::string WND_TITLE = "TIC-TAC-TOE AI";

int main(int argc, char **argv)
{
    /**
     * It initializes the Background creating a texture and a sprite
     * **/
    sf::Texture bg_texture;
    bg_texture.loadFromFile("assets/img/background.png");

    sf::Sprite background(bg_texture);
    sf::VideoMode vm(bg_texture.getSize().x, bg_texture.getSize().y);

    /**
     * It creates the Window where insert the background
     * **/
    sf::RenderWindow window;
    window.create(vm, WND_TITLE);
    window.setFramerateLimit(20);

    /**
     * It creates the Font and places it on the background
     * **/
    sf::Font font;
    int scale_font_factor=2;
    font.loadFromFile("assets/fonts/bodoni/BodoniFLF-Bold.ttf");
    sf::Text enter_text("Enter To Start", font);
    enter_text.setFillColor(sf::Color::Black);
    enter_text.scale(scale_font_factor, scale_font_factor);
    enter_text.setPosition(    // Placing in center of the window
        window.getSize().x/2 - enter_text.getLocalBounds().width*scale_font_factor/2,
        window.getSize().y/2);
    
    /**
     * It creates the table of the game
     * **/
    GraphicsTable table(
        sf::Vector2f(45, 215),
        sf::Vector2f(735, 900));
    game_manager::Problem game;
    game_manager::ProblemResolver problem_resolver;
    problem_resolver.setProblem(&game);
    
    /**
     * It sets the initial value of the game state variables
     * **/
    bool b_lock_click, b_clicked = false;
    bool b_player_turn, b_start_game, b_analysis, b_init_timer, b_game_over;
    auto reset = [&table, &b_player_turn,
                  &b_start_game, &b_analysis,
                  &b_init_timer, &b_game_over] () {
        table.clear();
        b_player_turn = true;
        b_start_game = false;
        b_analysis = false;
        b_init_timer = true;
        b_game_over = false;
    };
    reset();
    

    /**
     * It creates a timer for casual events of delay
     * **/
    sf::Clock clock;
    sf::Time start_time;

    /**
     * Mainloop
     **/
    while (window.isOpen())
    {
        /**
         * It listens all interactive events
         * **/
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Space Event Key: Start Game
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    b_start_game = true;
                }
            }

            // It The Mouse is clicked it locks to avoid continuos clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Button::Left && !b_lock_click && b_start_game && !b_game_over) {
                    b_lock_click = true;
                    b_clicked = true;
                }
            }

            // It releases the mouse's lock
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    b_lock_click = false;
                }
            }
        }

        /**
         * Logic of the Game
         **/
        if (b_start_game) {
            if (b_player_turn) {
                if (b_clicked) {
                    b_clicked = false;
                    sf::Vector2i position = sf::Mouse::getPosition(window);            
                    std::unique_ptr<sf::Vector2i> transform_pose = table.realPose2DiscretePose(position);

                    if (transform_pose != nullptr) {
                        int row = transform_pose->x;
                        int col = transform_pose->y;
                        
                        if (table.getPiece(row, col) == '-') {
                            table.setPosePiece(row, col, 'X');
                            b_analysis = true;
                        }
                    }
                }
            }
            else {
                if (!b_game_over) {
                    //auto opponent_move = problem_resolver.minmax_decision(table.getState());
                    auto opponent_move = problem_resolver.alpha_beta_search(table.getState());
                    table.setState(opponent_move);
                    b_analysis = true;
                }
            }

            if (b_analysis) {
                auto state = table.getState();

                if (game.isTicTacToe(state, 'O') || game.isTicTacToe(state, 'X')) {
                    
                    std::string str_winner = b_player_turn ? "YOU WIN!" : "MACHINE WINS!";
                    b_game_over = true;
                }
                else if (table.isFull()) {
                    b_game_over = true;
                }
                else {
                    b_player_turn = !b_player_turn;
                }
                b_analysis = false;
            }
        }

        /** 
         * It creates a delay to show the final result
         **/ 
        if (b_game_over) {
            if (b_init_timer) {
                clock.restart();
                b_init_timer = false;
            }
            sf::Time time_elapsed = clock.getElapsedTime();
            if (time_elapsed.asSeconds() > 2) {
                reset();
            }
        }

        /**
         * It updates the windows
         **/
        window.clear();
        window.draw(background);
        if (b_start_game) {
            window.draw(table);
        }
        else if (!b_game_over) {
            window.draw(enter_text);
        }
        window.display();
    }

    return 0;
}
