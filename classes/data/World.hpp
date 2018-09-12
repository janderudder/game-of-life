/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef DATA_WORLD_CPP
#define DATA_WORLD_CPP
#include "data/Cell.hpp"
#include <vector>
#include <stack>
#include <cassert>
using std::size_t;
using gen_num_t = std::size_t;


class World
{
    std::vector<Cell>               mCells;
    std::stack<std::vector<Cell>>   mPreviousGenerations            =   {};
    std::stack<std::vector<Cell>>   mFutureGenerations              =   {};
    size_t                          mWidth;
    size_t                          mHeight;
    gen_num_t                       mGenerationNumber = 0;


public:
    World(size_t w, size_t h);
    explicit World(size_t squareWorldSideSize);


    // --- Generations
    void computeNextState();
    void goBackward();


    // --- Grid dimensions
    const size_t& getWidth() const;
    const size_t& getHeight() const;
    inline gen_num_t getGeneration() const      { return mGenerationNumber; }


    // --- Access cell by number
    Cell&       operator[](size_t i)            { return mCells[i]; }
    const Cell& operator[](size_t i) const      { return mCells[i]; }


    // --- Access cell by coordinates,
    // --- with wrap around correction
    Cell&       operator()(int, int);
    const Cell& operator()(int, int) const;


    // --- Iterators on mCells
    auto begin() noexcept                       {  return mCells.begin();   }
    auto end()  noexcept                        {  return mCells.end();     }
    const auto begin() const noexcept           {  return mCells.begin();   }
    const auto end() const noexcept             {  return mCells.end();     }


};

#endif // DATA_WORLD_CPP
