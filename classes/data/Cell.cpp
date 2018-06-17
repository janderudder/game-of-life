/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#include "data/Cell.hpp"


Cell:: 
Cell(bool isAlive) noexcept
    : alive     ( isAlive )
    , visited   ( isAlive )
{

}



void        Cell::
live() {
    this->alive = true;
    this->visited = true;
}


void        Cell::
die() {
    if ( this->alive )
        this->visited = true;
    this->alive = false;
}



void        Cell::
visit() {
    this->visited = true;
}



void        Cell::
toggleEdit() {
    this->alive = !this->alive;
}
