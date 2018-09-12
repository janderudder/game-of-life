/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#include "data/World.hpp"
#include <cstdint>
using std::uint8_t;

////////////////////////////////////////////////////////////////
//  CONSTRUCTORS
////////////////////////////////////////////////////////////////
World::
World(size_t w, size_t h)
    : mCells     { w * h, Cell() }
    , mWidth     { w }
    , mHeight    { h }
{

}


World::
World(size_t squareWorldSideSize)
    : World(squareWorldSideSize, squareWorldSideSize)
{

}


////////////////////////////////////////////////////////////////
//  APPLY RULES
////////////////////////////////////////////////////////////////
void World::
computeNextState()
{
    auto nextState(this->mCells);    // Copy world data array
    auto cellCount = this->mCells.size();


    for ( int h=0;  (size_t)h < this->mHeight;  ++h )
    for ( int w=0;  (size_t)w < this->mWidth;  ++w )
    {
        uint8_t aliveNeighbors = 0;

        // Neighbors above the cell
        for (int i=0; i < 3; ++i) {
            if ( (*this)(w - 1 + i,   h - 1).isAlive() )
                ++aliveNeighbors;
        }

        // To the left and right
        if ( (*this)( w - 1,  h ).isAlive() )
            ++aliveNeighbors;

        if ( (*this)( w + 1,  h).isAlive() )
            ++aliveNeighbors;

        // Line below the cell
        for (int i=0; i < 3; ++i) {
            if ( (*this)(w - 1 + i,   h + 1).isAlive() )
                ++aliveNeighbors;
        }

        // We got the number of alive neighbors,
        // determine the cell's next state.
        size_t cell = this->mWidth * h + w;
        if ( aliveNeighbors == 3 ) {
            nextState[cell].live();
        }
        else if ( aliveNeighbors != 2 ) {
            nextState[cell].die();
        }

    }

    // Now that the new state is computed, make it the current one
    std::swap(this->mCells, nextState);

}




////////////////////////////////////////////////////////////////
//  DIMENSIONS GETTERS
////////////////////////////////////////////////////////////////
const size_t&      World::
getWidth() const {
    return this->mWidth;
}


const size_t&      World::
getHeight() const {
    return this->mHeight;
}



////////////////////////////////////////////////////////////////
//  CELL ACCESS BY COORDINATES, WITH WRAP AROUND CORRECTION
////////////////////////////////////////////////////////////////
Cell&               World::
operator()(int x, int y) {
    if ( x >= (int)this->mWidth )
        x -= (int)this->mWidth;
    else if ( x < 0 )
        x += (int)this->mWidth;

    if ( y >= (int)this->mHeight )
        y -= (int)this->mHeight;
    else if ( y < 0 )
        y += (int)this->mHeight;

    return this->mCells[this->mWidth * y + x];
}


const Cell&         World::
operator()(int x, int y) const {
    return (*this)(x, y);
}
