#include "data/World.hpp"
#include <cstdint>
#include "InfiniteIndex.hpp"
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
    // Copy all world data
    auto nextState ( this->cells );
    
    auto cellCount = this->cells.size();

    /**
     * We'll make range checks only in particular cases
     */
    for ( size_t cellN=0;  cellN < cellCount;  ++cellN )
    {
        uint8_t aliveNeighbors = 0;

        // Neighbors above the cell
        auto n = InfiniteIndex(cellCount, static_cast<long>(cellN) - static_cast<long>(this->width + 1));

        for (uint8_t i=0; i < 3; ++i) {
            if (cells[n.toSize_t()].isAlive()) ++aliveNeighbors;
            ++n;
        }

        // To the left and right
        n = cellN - 1;
        if (cells[n.toSize_t()].isAlive()) ++aliveNeighbors;
        n = cellN + 1;
        if (cells[n.toSize_t()].isAlive()) ++aliveNeighbors;

        // Line below the cell
        n = cellN + this->width - 1;
        for (uint8_t i=0; i < 3; ++i) {
            if (cells[n.toSize_t()].isAlive()) ++aliveNeighbors;
            ++n;
        }

        // We got the number of alive neighbors,
        // determine the cell's next state.
        if ( aliveNeighbors == 3 ) {
            nextState[cellN].live();
        }
        else if ( aliveNeighbors != 2 ) {
            nextState[cellN].die();
        }

        // Handle visited state -- this really should be optimized
        if ( cells[cellN].isAlive() && !cells[cellN].wasVisited() )
            nextState[cellN].visit();
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
//  CELL ACCESS BY COORDINATES
////////////////////////////////////////////////////////////////
Cell&               World::
operator()(size_t x, size_t y) {
    return this->cells[this->width * y + x];
}


const Cell&         World::
operator()(size_t x, size_t y) const {
    return (*this)(x, y);
}
