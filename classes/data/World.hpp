#ifndef DATA_WORLD_CPP
#define DATA_WORLD_CPP
#include "data/Cell.hpp"
#include <vector>
#include <cassert>
using std::size_t;

class World
{
    std::vector<Cell>       cells;
    size_t                  width;
    size_t                  height;
    

public:
    World(size_t w, size_t h);
    explicit World(size_t squareWorldSideSize);


    // --- Apply rules
    void computeNextState();


    // --- Grid dimensions
    const size_t& getWidth() const;
    const size_t& getHeight() const;


    // --- Access cell by number
    Cell&       operator[](size_t i)            { return this->cells[i]; }
    const Cell& operator[](size_t i) const      { return this->cells[i]; }


    // --- Access cell by coordinates,
    // --- with wrap around correction
    Cell&       operator()(int, int);
    const Cell& operator()(int, int) const;


    // --- Iterators on cells
    auto begin() noexcept                       {  return this->cells.begin();   } 
    auto end()  noexcept                        {  return this->cells.end();     }
    const auto begin() const noexcept           {  return this->cells.begin();   } 
    const auto end() const noexcept             {  return this->cells.end();     }


};

#endif // DATA_WORLD_CPP
