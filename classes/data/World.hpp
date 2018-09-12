/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef DATA_WORLD_CPP
#define DATA_WORLD_CPP
#include "data/Cell.hpp"
#include <vector>
#include <cassert>
using std::size_t;

class World
{
    std::vector<Cell>       mCells;
    size_t                  mWidth;
    size_t                  mHeight;


public:
    World(size_t w, size_t h);
    explicit World(size_t squareWorldSideSize);


    // --- Apply rules
    void computeNextState();


    // --- Grid dimensions
    const size_t& getWidth() const;
    const size_t& getHeight() const;


    // --- Access cell by number
    Cell&       operator[](size_t i)            { return this->mCells[i]; }
    const Cell& operator[](size_t i) const      { return this->mCells[i]; }


    // --- Access cell by coordinates,
    // --- with wrap around correction
    Cell&       operator()(int, int);
    const Cell& operator()(int, int) const;


    // --- Iterators on mCells
    auto begin() noexcept                       {  return this->mCells.begin();   }
    auto end()  noexcept                        {  return this->mCells.end();     }
    const auto begin() const noexcept           {  return this->mCells.begin();   }
    const auto end() const noexcept             {  return this->mCells.end();     }


};

#endif // DATA_WORLD_CPP
