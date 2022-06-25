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

#include "game_entities.hpp"
#include <string>
#include <map>

void drawGrid(sf::RenderTarget & target, sf::RenderStates states,
    std::map<std::string, sf::Vector2f> points, int rows = 3, int cols = 3)
{
    for (int i = 1 ; i < rows; i++) {
        sf::RectangleShape line(sf::Vector2f(points["BR"].x-points["BL"].x, 5));
        line.setPosition(sf::Vector2f(
            points["TL"].x, points["TL"].y+i*(points["BL"].y-points["TL"].y)/rows));
        line.setFillColor(sf::Color::Black);
        target.draw(line, states);
    }

    for (int i = 1 ; i < cols; i++) {
        sf::RectangleShape line(sf::Vector2f(points["BR"].x-points["BL"].x, 5));
        line.rotate(90);
        line.setPosition(sf::Vector2f(
            points["TL"].x + i*(points["BR"].x - points["TL"].x)/cols, points["TL"].y));
        line.setFillColor(sf::Color::Black);
        target.draw(line, states);
    }
}

GraphicsTable::GraphicsTable(const sf::Vector2f & tl, const sf::Vector2f & br, int side)
    : boxes_(side*side, '-'), side_(side)
{
    points_["TL"] = tl;                         // Top Left
    points_["TR"] = sf::Vector2f(br.x, tl.y);   // Top Right
    points_["BL"] = sf::Vector2f(tl.x, br.y);   // Bottom Left
    points_["BR"] = br;                         // Bottom Right

    width_ = br.x - tl.x;
    height_ = br.y - tl.y;
    // Get Size of cell
    cellsize_ = (points_.at("TR").x-points_.at("TL").x)/side_;
};

/** It returns x, y, w, h **/
std::vector<int> GraphicsTable::getDimensions() const
{
    std::vector<int> dim(4, 0);
    dim[0] = points_.at("TL").x;
    dim[1] = points_.at("TL").y;
    dim[2] = width_;
    dim[3] = height_;
    return dim;
}

sf::Vector2i GraphicsTable::realPose2DiscretePose(const sf::Vector2i & pose) const
{
    // TODO DELIMITAR TABLA

    // We focus only the table, not the window
    int r = (pose.y - points_.at("TL").y) / cellsize_;
    int c = (pose.x - points_.at("TL").x) / cellsize_;

    return sf::Vector2i(r, c);
}

void GraphicsTable::setPosePiece(int row, int col, char piece)
{
    boxes_[row*side_+col] = piece;
}

void GraphicsTable::setState(const std::vector <char> state)
{
    boxes_=state;
}

char GraphicsTable::getPiece(int row, int col) const
{
    return boxes_[row*side_+col];
}

bool GraphicsTable::isFull() const
{
    for (auto box : boxes_) {
        if (box == '-') {
            return false;
        }
    }
    return true;
}

void GraphicsTable::clear()
{
    for (std::size_t i = 0; i < boxes_.size(); i++) {
        boxes_[i] = '-';
    }
}

void GraphicsTable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Draw Grid
    drawGrid(target, states, points_, side_, side_);

    // Get Size of cell
    float cellsize = (points_.at("TR").x-points_.at("TL").x)/side_;

    // Draw Pieces
    for (std::size_t i = 0; i < boxes_.size(); i++) {
        sf::Texture piece_texture;

        if (boxes_[i] == 'X') {
            piece_texture.loadFromFile("assets/img/x-piece.png");
        }
        else if (boxes_[i] == 'O') {
            piece_texture.loadFromFile("assets/img/o-piece.png");
        }
        else {
            continue;
        }

        int row = i/side_;
        int col = i%side_;
        float x_gap = (cellsize-piece_texture.getSize().x)/2.0;
        float y_gap = (cellsize-piece_texture.getSize().y)/2.0;

        sf::Sprite piece(piece_texture);
        piece.setPosition(sf::Vector2f(points_.at("TL").x+col*cellsize_+x_gap, points_.at("TL").y+row*cellsize_+y_gap));
        target.draw(piece, states);
    }
}

std::ostream & operator<<(std::ostream & os, const GraphicsTable & table)
{
    for (std::size_t i = 0; i < table.boxes_.size(); i++) {
        os << table.boxes_[i] << ' ';
    }
    return os;
}
