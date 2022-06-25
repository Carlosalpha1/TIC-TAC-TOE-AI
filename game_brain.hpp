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

#ifndef TICTACTOE_AI_GAME_BRAIN_HPP_
#define TICTACTOE_AI_GAME_BRAIN_HPP_

#include <vector>
#include <SFML/Graphics.hpp>

namespace game_manager
{

class Node
{
public:
    std::vector <char> state;
    int value;

    Node(const std::vector <char> st);
};

int utility(const std::vector<char> & state);
bool is_tic_tac_toe(std::vector<char> state, char piece);
Node max_value__minmax(const std::vector <char> & state, int level);
Node min_value__minmax(const std::vector <char> & state, int level);
bool is_terminal_state(const std::vector <char> & state);
std::vector<std::vector <char> > successors(const std::vector<char> & state, char piece);
std::vector <char> minmax_decision(const std::vector <char> & state);

};

#endif