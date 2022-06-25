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

typedef std::vector<char> State;

namespace game_manager
{

class Node
{
public:
    State state;
    int value;

    Node(const State st);
};

int utility(const State & state);
bool is_tic_tac_toe(State state, char piece);
Node max_value__minmax(const State & state);
Node min_value__minmax(const State & state);
bool is_terminal_state(const State & state);
std::vector<State> successors(const State & state, char piece);
State minmax_decision(const State & state);

};

#endif