/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#include "WorldRenderer.hpp"
#include "data/Cell.hpp"
#include <cmath>
#include <iostream>


////////////////////////////////////////////////////////////////
//  DRAW METHOD
////////////////////////////////////////////////////////////////
void        WorldRenderer::
draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(triangles, states);

    if ( this->drawLines_b )
        target.draw(lines, states);
}





////////////////////////////////////////////////////////////////
//  CONSTRUCTOR
////////////////////////////////////////////////////////////////
WorldRenderer::
WorldRenderer(const World& w, float cellSize)
    : world     ( w )
    , cellSize  ( cellSize )
    , bounds    { 0, 0, w.getWidth() * cellSize, w.getHeight() * cellSize }
{
    auto width = cellSize * world.getWidth();
    auto height = cellSize * world.getHeight();


    // Triangles
    for (size_t y=0;  y < world.getHeight();  ++y)
    for (size_t x=0;  x < world.getWidth();  ++x) {
        triangles.append(sf::Vertex(sf::Vector2f( x * cellSize, y * cellSize )));
        triangles.append(sf::Vertex(sf::Vector2f( x * cellSize + cellSize, y * cellSize )));
        triangles.append(sf::Vertex(sf::Vector2f( x * cellSize, y * cellSize + cellSize )));
        triangles.append(sf::Vertex(sf::Vector2f( x * cellSize, y * cellSize + cellSize )));
        triangles.append(sf::Vertex(sf::Vector2f( x * cellSize + cellSize, y * cellSize )));
        triangles.append(sf::Vertex(sf::Vector2f( x * cellSize + cellSize, y * cellSize + cellSize )));
    }


    // Vertical lines
    for (size_t i=0;  i < world.getWidth() + 1;  ++i) {
        lines.append(sf::Vertex(sf::Vector2f(i * cellSize, 0)));
        lines.append(sf::Vertex(sf::Vector2f(i * cellSize, height)));
    }

    // Horizontal lines
    for (size_t i=0;  i < world.getHeight() + 1;  ++i) {
        lines.append(sf::Vertex(sf::Vector2f(0, i * cellSize)));
        lines.append(sf::Vertex(sf::Vector2f(width, i * cellSize)));
    }


    // Default empty cells color
    for (size_t i=0;  i < triangles.getVertexCount();  ++i)
        triangles[i].color = this->noCell_col;

    // Default lines color
    for (size_t i=0;  i < lines.getVertexCount();  ++i)
        lines[i].color = lines_col;

}




////////////////////////////////////////////////////////////////
//  GEOMETRY
////////////////////////////////////////////////////////////////
const sf::FloatRect&        WorldRenderer::
getBounds() const {
    return this->bounds;
}



const float&                WorldRenderer::
getCellSize() const {
    return this->cellSize;
}




////////////////////////////////////////////////////////////////
//  DRAW LINES SWITCH
////////////////////////////////////////////////////////////////
void        WorldRenderer::
drawLines(bool b) {
    this->drawLines_b = b;
}




////////////////////////////////////////////////////////////////
//  SET COLORS
////////////////////////////////////////////////////////////////
void        WorldRenderer::
noCellColor(const sf::Color& c) {
    this->noCell_col = c;
    this->update();
}


void        WorldRenderer::
aliveCellColor(const sf::Color& c) {
    this->aliveCell_col = c;
    this->update();
}


void        WorldRenderer::
visitedCellColor(const sf::Color& c) {
    this->visitedCell_col = c;
    this->update();
}



void        WorldRenderer::
linesColor(const sf::Color& color) {
    for (size_t i=0;  i < lines.getVertexCount();  ++i)
        lines[i].color = color;
}





////////////////////////////////////////////////////////////////
//  CELL NUMBER -> POINTER TO VERTEX (FIRST CELL'S VERTEX)
////////////////////////////////////////////////////////////////
sf::Vertex*        WorldRenderer::
getCellPoint(size_t n) {
    return &(this->triangles[n * 6]);
}


const sf::Vertex*        WorldRenderer::
getCellPoint(size_t n) const {
    return this->getCellPoint(n);
}


sf::Vertex*        WorldRenderer::
getCellPointAt(size_t x, size_t y) {
    return &(this->triangles[this->world.getWidth()  * y + x]);
}


const sf::Vertex*        WorldRenderer::
getCellPointAt(size_t x, size_t y) const {
    return this->getCellPointAt(x, y);
}





////////////////////////////////////////////////////////////////
//  UPDATE DISPLAY
////////////////////////////////////////////////////////////////
void                    WorldRenderer::
update()
{
    size_t i = 0;
    for ( const Cell& cell : this->world )
    {
        sf::Vertex* originPoint = this->getCellPoint(i);
        sf::Color color = this->noCell_col;

        if ( cell.isAlive() )
            color = this->aliveCell_col;
        else if ( cell.wasVisited() )
            color = this->visitedCell_col;

        if ( originPoint->color != color ) {
            originPoint->color = color;
            (++originPoint)->color = color;
            (++originPoint)->color = color;
            (++originPoint)->color = color;
            (++originPoint)->color = color;
            (++originPoint)->color = color;
        }

        ++i;
    }
}





////////////////////////////////////////////////////////////////
//  WORLD COORDINATES TO CELL CONVERSION
////////////////////////////////////////////////////////////////
sf::Vector2<size_t>                WorldRenderer::
graphicsToDataCoords(const sf::Vector2f& coords) const
{
    return {
        static_cast<size_t>(std::floor(coords.x / cellSize)),
        static_cast<size_t>(std::floor(coords.y / cellSize))
    };
}



size_t                          WorldRenderer::
graphicsCoordsToCellNumber(const sf::Vector2f& coords) const {
    auto c = this->graphicsToDataCoords(coords);
    return world.getWidth() * c.y + c.x;
}
