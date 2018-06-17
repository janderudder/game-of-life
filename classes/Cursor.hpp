/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef CURSOR_HPP
#define CURSOR_HPP
#include <cstdint>
using std::uint8_t;
using std::size_t;

template <class T>
struct ClickedEntity {
    T*  ptr;
    typedef T Type;
};


class Cursor
{
    enum Editing : uint8_t { None, DeadCells, LiveCells };

    Editing     editing                     =   Editing::None;
    size_t      lastCellNumber              =   0;
    bool        lastCellAlive               =   false;

public:
    explicit Cursor() noexcept {}


    void clickOnGrid() {}


};

#endif // CURSOR_HPP
