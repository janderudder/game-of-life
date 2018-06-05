#include "data/World.hpp"
#include <cstdint>
using std::uint8_t;

////////////////////////////////////////////////////////////////
//  CONSTRUCTORS
////////////////////////////////////////////////////////////////
World::
World(size_t w, size_t h)
    : cells     { w * h, Cell() }
    , width     { w }
    , height    { h }
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
    auto nextState(this->cells);    // Copy world data array    
    auto cellCount = this->cells.size();


    for ( int h=0;  (size_t)h < this->height;  ++h )
    for ( int w=0;  (size_t)w < this->width;  ++w )
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
        size_t cell = this->width * h + w;
        if ( aliveNeighbors == 3 ) {
            nextState[cell].live();
        }
        else if ( aliveNeighbors != 2 ) {
            nextState[cell].die();
        }

        // Handle visited state -- this really should be optimized
        if ( cells[cell].isAlive() && !cells[cell].wasVisited() )
            nextState[cell].visit();
    }

    // Now that the new state is computed, make it the current one
    std::swap(this->cells, nextState);

}




////////////////////////////////////////////////////////////////
//  DIMENSIONS GETTERS
////////////////////////////////////////////////////////////////
const size_t&      World::
getWidth() const {
    return this->width;
}


const size_t&      World::
getHeight() const {
    return this->height;
}



////////////////////////////////////////////////////////////////
//  CELL ACCESS BY COORDINATES, WITH WRAP AROUND CORRECTION
////////////////////////////////////////////////////////////////
Cell&               World::
operator()(int x, int y) {
    if ( x >= (int)this->width )
        x -= (int)this->width;
    else if ( x < 0 )
        x += (int)this->width;

    if ( y >= (int)this->height )
        y -= (int)this->height;
    else if ( y < 0 )
        y += (int)this->height;

    return this->cells[this->width * y + x];
}


const Cell&         World::
operator()(int x, int y) const {
    return (*this)(x, y);
}
