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

#include "game_brain.hpp"

namespace game_manager
{

Node::Node(const std::vector <char> st)
    : state(st)
{
    value = utility(state);
}

std::vector <char> minmax_decision(const std::vector <char> & state)
{
    Node best_node = max_value__minmax(state);
    return best_node.state;
}

Node max_value__minmax(const std::vector <char> & state)
{
    if (is_terminal_state(state)) {
        return Node(state);
    }
    int best_score = -100;
    auto state_successors = successors(state, 'O');
    int i_max = 0, value = 0;

    for (std::size_t i = 0; i < state_successors.size(); i++) {
        value = min_value__minmax(state_successors[i]).value;
        if (value > best_score) {
            best_score = value;
            i_max = i;
        }
    }
    return Node(state_successors[i_max]);
}

Node min_value__minmax(const std::vector <char> & state)
{
    if (is_terminal_state(state)) {
        return Node(state);
    }

    int best_score = 100;
    auto state_successors = successors(state, 'X');
    int i_min = 0, value = 0;

    for (std::size_t i = 0; i < state_successors.size(); i++) {
        value = min_value__minmax(state_successors[i]).value;
        if (value < best_score) {
            best_score = value;
            i_min = i;
        }
    }
    return Node(state_successors[i_min]);
}

bool is_terminal_state(const std::vector <char> & state)
{
    if (is_tic_tac_toe(state, 'O') || is_tic_tac_toe(state, 'X')) {
        return true;
    }
    for (std::size_t i = 0; i < state.size(); i++) {
        if (state[i] == '-') {
            return false;
        }
    }
    return true;
}

int utility(const std::vector<char> & state)
{
    int value;

    if (is_tic_tac_toe(state, 'O')) {
        value = 1;
    }
    else if (is_tic_tac_toe(state, 'X')) {
        value = -1;
    }
    else {
        value = 0;
    }

    int k = 1;
    for (int i = 0; i < state.size(); i++) {
        if (state[i] == '-') {
            k++;
        }
    }

    return value*k;
}

std::vector<std::vector<char> > successors(const std::vector<char> & state, char piece)
{
    std::vector <std::vector<char> > states;
    for (std::size_t i = 0; i < state.size(); i++) {
        if (state[i] != '-') {
            continue;
        }

        states.push_back(state);
        states.back()[i] = piece;
    }
    return states;
}

bool is_tic_tac_toe(std::vector<char> state, char piece)
{
    if ((piece == state[0] && piece == state[4] && piece == state[8]) ||
        (piece == state[2] && piece == state[4] && piece == state[6]) ||
        (piece == state[0] && piece == state[1] && piece == state[2]) ||
        (piece == state[3] && piece == state[4] && piece == state[5]) ||
        (piece == state[6] && piece == state[7] && piece == state[8]) ||
        (piece == state[0] && piece == state[3] && piece == state[6]) ||
        (piece == state[1] && piece == state[4] && piece == state[7]) ||
        (piece == state[2] && piece == state[5] && piece == state[8])) {
        return true;
    }
    return false;
}


}