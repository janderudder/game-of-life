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
    auto nextState(mCells);    // Copy world data array
    auto cellCount = mCells.size();

    mGenerationNumber++;

    for ( int h=0;  (size_t)h < mHeight;  ++h )
    for ( int w=0;  (size_t)w < mWidth;  ++w )
    {
        // Get number of neighbors alive
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
        size_t cell = mWidth * h + w;
        if ( aliveNeighbors == 3 ) {
            nextState[cell].live(mGenerationNumber);
        }
        else if ( aliveNeighbors != 2 ) {
            nextState[cell].die(mGenerationNumber);
        }

    }

    // Now that the new state is computed, move the previous one in
    // the prev stack, and make this one the current one.
    mPreviousGenerations.emplace(std::move(mCells));
    mCells = std::move(nextState);

    // Since we moved normally, clear saved future states
    while ( !mFutureGenerations.empty() )
        mFutureGenerations.pop();

}



void World::goBackward()
{
    if ( mPreviousGenerations.empty() )
        return;

    mCells = std::move(mPreviousGenerations.top());
    mPreviousGenerations.pop();
    mGenerationNumber--;
}





////////////////////////////////////////////////////////////////
//  DIMENSIONS GETTERS
////////////////////////////////////////////////////////////////
const size_t&      World::
getWidth() const {
    return mWidth;
}


const size_t&      World::
getHeight() const {
    return mHeight;
}



////////////////////////////////////////////////////////////////
//  CELL ACCESS BY COORDINATES, WITH WRAP AROUND CORRECTION
////////////////////////////////////////////////////////////////
Cell&               World::
operator()(int x, int y) {
    if ( x >= (int)mWidth )
        x -= (int)mWidth;
    else if ( x < 0 )
        x += (int)mWidth;

    if ( y >= (int)mHeight )
        y -= (int)mHeight;
    else if ( y < 0 )
        y += (int)mHeight;

    return mCells[mWidth * y + x];
}


const Cell&         World::
operator()(int x, int y) const {
    return (*this)(x, y);
}
