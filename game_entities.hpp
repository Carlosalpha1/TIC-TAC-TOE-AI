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

#ifndef TICTACTOE_AI_GAME_ENTITIES_HPP_
#define TICTACTOE_AI_GAME_ENTITIES_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

typedef std::vector<char> State;

class GraphicsTable : public sf::Drawable
{
protected:
    int width_, height_, side_;
    std::vector<char> boxes_;
    std::map<std::string, sf::Vector2f> points_;
    float cellsize_;

public:
    /**
     * Extreme 1 point is the Top Left point
     * Extreme 2 point is the Bottom Right point
     **/
    GraphicsTable(const sf::Vector2f & ext1, const sf::Vector2f & ext2, int side = 3);
    
    ~GraphicsTable(){};

    /**
     * It returns x, y, w, h of the Table
     **/
    std::vector<int> getDimensions() const;
    
    /**
     * It returns the current State (map of the cells)
     **/
    State getState() const { return boxes_; }
    
    /**
     * It converts a Real Pose to Discrete Pose (Row, Column)
     **/
    std::unique_ptr<sf::Vector2i> realPose2DiscretePose(const sf::Vector2i & pose) const;

    void setPosePiece(int row, int col, char piece);
    
    void setState(const State & state);
    
    char getPiece(int row, int col) const;
    
    bool isFull() const;
    
    /**
     * It resets the table. All cells to empty (-)
     **/
    void clear();
    
    /**
     * This functions lets the GraphicsTable class to be a drawable object
     **/
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    friend std::ostream & operator<<(std::ostream & os, const GraphicsTable & table);
};

#endif  // TICTACTOE_AI_GAME_ENTITIES_HPP_
