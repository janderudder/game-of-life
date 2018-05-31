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
