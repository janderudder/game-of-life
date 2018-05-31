#ifndef INFINITE_INDEX_HPP
#define INFINITE_INDEX_HPP
#include <cstdint>
using std::size_t;

class InfiniteIndex
{
    long    index;
    long    arraySize;


    void computeIndex() {
        if (index >= arraySize)
            index -= arraySize;
        
        else if ( index < 0 )
            index += arraySize;
    }

public:
    InfiniteIndex(size_t argArraySize, long pos = 0) noexcept
        : index     { pos }
        , arraySize { static_cast<long>(argArraySize) }
    {
        computeIndex();
    }

    size_t toSize_t() { return static_cast<size_t>(this->index); }

    void operator=(long n) { this->index = n; computeIndex(); }
    InfiniteIndex& operator++() { this->index++; computeIndex(); return *this; }

};

#endif // INFINITE_INDEX_HPP
