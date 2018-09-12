/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#include "data/Cell.hpp"


Cell::
Cell(bool isAlive) noexcept
    : mIsAlive     ( isAlive )
    , mIsVisited   ( isAlive )
{

}



void        Cell::
live() {
    mIsAlive = true;
    mIsVisited = true;
}


void        Cell::
die() {
    if ( mIsAlive )
        mIsVisited = true;
    mIsAlive = false;
}



void        Cell::
visit() {
    mIsVisited = true;
}



void        Cell::
toggleEdit() {
    mIsAlive = !mIsAlive;
}

