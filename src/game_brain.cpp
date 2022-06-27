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

#include <unistd.h>
#include <cmath>
#include "game_brain.hpp"

using namespace std;

namespace game_manager
{

/**
 * GAME/PROBLEM METHODS
 **/
std::vector<Action> Problem::actions(const State & state, Piece piece)
{
    side_ = std::sqrt(state.size());

    std::vector<Action> actions;

    for (std::size_t i = 0; i < state.size(); i++) {
        if (state[i] == '-') {
            Action act;
            act.move.x = i / side_;
            act.move.y = i % side_;
            act.piece = piece;
            actions.push_back(act);
        }
    }
    return actions;
}

State Problem::result(const State & state, Action & action) const
{
    State st_result = state;
    st_result[action.move.x*side_+action.move.y] = action.piece;
    return st_result;
}

int Problem::utility(const State & state)
{
    int value;

    if (isTicTacToe(state, 'O')) {
        value = 1;
    }
    else if (isTicTacToe(state, 'X')) {
        value = -1;
    }
    else {
        value = 0;
    }

    int k = 1;
    for (std::size_t i = 0; i < state.size(); i++) {
        if (state[i] == '-') {
            k++;
        }
    }

    return value*k;
}

bool Problem::isTerminalState(const State & state)
{
    if (isTicTacToe(state, 'O') || isTicTacToe(state, 'X')) {
        return true;
    }
    for (std::size_t i = 0; i < state.size(); i++) {
        if (state[i] == '-') {
            return false;
        }
    }
    return true;
}

bool Problem::isTicTacToe(State state, Piece piece)
{
    // Analizing colums
    for (int i = 0; i < side_; i++) {
        for (int j = 0; j < side_; j++) {
            if (piece != state[i+j*side_]) {
                break;
            }
            if (j == (side_-1)) return true;
        }
    }

    // Analizing rows
    for (int i = 0; i < side_; i++) {
        for (int j = 0; j < side_; j++) {
            if (piece != state[i*side_ + j]){
                break;
            }
            if (j == (side_-1)) return true;
        }
    }

    // Analizing diagonal 1
    for (int i = 0; i < side_; i++) {
        if (piece != state[(1+side_)*i]) {
            break;
        }
        if (i == (side_-1)) return true;
    }

    // Analizing diagonal 2
    for (int i = 0; i < side_; i++) {
        if (piece != state[(side_-1)*(i+1)]) {
            break;
        }
        if (i == (side_-1)) return true;
    }
    return false;
}

/**
 *  MinMax Algorithm
 **/
State ProblemResolver::minmax_decision(const State & state)
{
    State best_state;
    int value, i_max = 0, max_score = -99999;
    auto moves = problem_->actions(state, 'O');

    for (std::size_t i = 0; i < moves.size(); i++) {
        value = min_value__minmax(problem_->result(state, moves[i]));
        if (value > max_score) {
            max_score = value;
            i_max = i;
        }
    }
    return problem_->result(state, moves[i_max]);
}

int ProblemResolver::max_value__minmax(const State & state)
{
    if (problem_->isTerminalState(state)) {
        return problem_->utility(state);
    }
    
    int value = -std::numeric_limits<int>::max();
    for (auto action : problem_->actions(state, 'O')) {
        value = std::max(value, min_value__minmax(problem_->result(state, action)));
    }
    return value;
}

int ProblemResolver::min_value__minmax(const State & state)
{
    if (problem_->isTerminalState(state)) {
        return problem_->utility(state);
    }
    
    int value = std::numeric_limits<int>::max();
    for (auto action : problem_->actions(state, 'X')) {
        value = std::min(value, max_value__minmax(problem_->result(state, action)));
    }
    return value;
}

/**
 * Alpha-Beta Algorithm
 **/
State ProblemResolver::alpha_beta_search(const State & state)
{
    State best_state;
    int value, i_best = 0;
    int best_score = -std::numeric_limits<int>::max();
    int beta = std::numeric_limits<int>::max();

    auto moves = problem_->actions(state, 'O');

    for (std::size_t i = 0; i < moves.size(); i++) {
        value = min_value__minmax(problem_->result(state, moves[i]), best_score, beta, 0);
        if (value > best_score) {
            best_score = value;
            i_best = i;
        }
    }

    return problem_->result(state, moves[i_best]);
}

int ProblemResolver::max_value__minmax(const State & state, int alpha, int beta, int depth)
{
    if (problem_->isTerminalState(state) || (depth > 8)) {
        return problem_->utility(state);
    }
    
    int value = -std::numeric_limits<int>::max();
    for (auto action : problem_->actions(state, 'O')) {
        value = std::max(value, min_value__minmax(problem_->result(state, action), alpha, beta, depth+1));
        if (value >= beta) {
            return value;
        }
        alpha = std::max(alpha, value);
    }
    return value;
}

int ProblemResolver::min_value__minmax(const State & state, int alpha, int beta, int depth)
{
    if (problem_->isTerminalState(state) || (depth > 8)) {
        return problem_->utility(state);
    }

    int value = std::numeric_limits<int>::max();
    for (auto action : problem_->actions(state, 'X')) {
        value = std::min(value, max_value__minmax(problem_->result(state, action), alpha, beta, depth+1));
        if (value <= alpha) {
            return value;
        }
        beta = std::min(beta, value);
    }
    return value;
}

}

ostream & operator<<(ostream & os, const game_manager::Action & action)
{
    os << action.move.x << " " << action.move.y << " " << action.piece;
    return os;
}

ostream & operator<<(ostream & os, const std::vector<game_manager::Action> & actions)
{
    for (auto action : actions) {
        os << "[(" << action << ")] ";
    }
    return os;
}

ostream & operator<<(ostream & os, const State & state)
{
    for (std::size_t i = 0; i < state.size(); i++) {
        os << state[i] << " ";
    }
    return os;
}
