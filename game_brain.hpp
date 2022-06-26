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

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

// Aliases
typedef std::vector<char> State;
typedef sf::Vector2i Movement;
typedef char Piece;



namespace game_manager
{

struct Action
{
    Movement move;
    Piece piece;
};

class Game {

private:
    int side_;

    int max_value__minmax(const State &);
    int min_value__minmax(const State &);
    std::vector<State> successors(const State &, Piece);

public:
    Game() : side_(0) {}


    bool isTicTacToe(State state, Piece);

    /**
     * It returns all possible movements:
     * Movement -> (Row, Column, Piece)
     **/
    std::vector<Action> actions(const State & state, Piece);

    /**
     * It returns a result state of doing a movement in a state
     * The result is a map of all cells:
     * State -> [X, O, -, X, X ...]
     **/
    State result(const State & state, Action & action) const;

    /**
     * This is the Evaluation Function of the Problem
     **/
    int utility(const State & state);

    /**
     * This function returns if is TICTACTOE or the table is FULL
     **/
    bool isTerminalState(const State & state);
    
    State minmax_decision(const State & state);
};

};

// Debugging functions
std::ostream & operator<<(std::ostream & os, const game_manager::Action & action);
std::ostream & operator<<(std::ostream & os, const std::vector<game_manager::Action> & actions);
std::ostream & operator<<(std::ostream & os, const State & state);

#endif  // TICTACTOE_AI_GAME_BRAIN_HPP_
