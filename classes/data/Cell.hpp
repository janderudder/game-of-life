#ifndef DATA_CELL_HPP
#define DATA_CELL_HPP

class Cell
{
    bool        alive;
    bool        visited;

public:
    explicit Cell(bool alive = false) noexcept;

    // --- States access
    const bool& isAlive() const         { return this->alive; }
    const bool& wasVisited() const      { return this->visited; }

    void live();
    void die();
    void visit();
    void toggleEdit();

};

#endif // DATA_CELL_HPP
