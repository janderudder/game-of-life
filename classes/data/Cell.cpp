/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#include "data/Cell.hpp"


Cell::
Cell(bool isAlive, gen_num_t visitedOn) noexcept
    : mIsAlive              { isAlive }
    , mVisitedOnGeneration  { visitedOn }
{

}



void        Cell::
live(gen_num_t genNumber) {
    mIsAlive = true;
    mVisitedOnGeneration = genNumber;
}


void        Cell::
die(gen_num_t genNumber)
{
    if (mIsAlive  &&  !this->isVisited())
        mVisitedOnGeneration = genNumber;

    mIsAlive = false;
}



void        Cell::
visit(gen_num_t genNumber) {
    mVisitedOnGeneration = genNumber;
}



void        Cell::
toggleEdit() {
    mIsAlive = !mIsAlive;
}

