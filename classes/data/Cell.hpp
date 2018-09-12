/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef DATA_CELL_HPP
#define DATA_CELL_HPP
#include <cstddef>
using gen_num_t = std::size_t;


class Cell
{
    bool            mIsAlive;
    gen_num_t       mVisitedOnGeneration;

public:
    explicit Cell(bool mIsAlive = false, gen_num_t = 0) noexcept;

    // --- States access
    inline bool isAlive() const         { return mIsAlive; }
    inline bool isVisited() const       { return static_cast<bool>(mVisitedOnGeneration); }
    inline gen_num_t visitedOn() const  { return mVisitedOnGeneration; }

    void live(gen_num_t = 0);
    void die(gen_num_t = 0);
    void visit(gen_num_t = 0);
    void toggleEdit();

};

#endif // DATA_CELL_HPP
