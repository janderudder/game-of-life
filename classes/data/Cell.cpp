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
