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
    target.draw(mTriangles, states);

    if ( mDoDrawLines )
        target.draw(mLines, states);
}





////////////////////////////////////////////////////////////////
//  CONSTRUCTOR
////////////////////////////////////////////////////////////////
WorldRenderer::
WorldRenderer(const World& w, float cellSize)
    : mWorld     ( w )
    , mCellSize  ( cellSize )
    , mBounds    { 0, 0, w.getWidth() * cellSize, w.getHeight() * cellSize }
{
    auto width = mCellSize * mWorld.getWidth();
    auto height = mCellSize * mWorld.getHeight();


    // Triangles
    for (size_t y=0;  y < mWorld.getHeight();  ++y)
    for (size_t x=0;  x < mWorld.getWidth();  ++x) {
        mTriangles.append(sf::Vertex(sf::Vector2f( x * mCellSize, y * mCellSize )));
        mTriangles.append(sf::Vertex(sf::Vector2f( x * mCellSize + mCellSize, y * mCellSize )));
        mTriangles.append(sf::Vertex(sf::Vector2f( x * mCellSize, y * mCellSize + mCellSize )));
        mTriangles.append(sf::Vertex(sf::Vector2f( x * mCellSize, y * mCellSize + mCellSize )));
        mTriangles.append(sf::Vertex(sf::Vector2f( x * mCellSize + mCellSize, y * mCellSize )));
        mTriangles.append(sf::Vertex(sf::Vector2f( x * mCellSize + mCellSize, y * mCellSize + mCellSize )));
    }


    // Vertical lines
    for (size_t i=0;  i < mWorld.getWidth() + 1;  ++i) {
        mLines.append(sf::Vertex(sf::Vector2f(i * mCellSize, 0)));
        mLines.append(sf::Vertex(sf::Vector2f(i * mCellSize, height)));
    }

    // Horizontal lines
    for (size_t i=0;  i < mWorld.getHeight() + 1;  ++i) {
        mLines.append(sf::Vertex(sf::Vector2f(0, i * mCellSize)));
        mLines.append(sf::Vertex(sf::Vector2f(width, i * mCellSize)));
    }


    // Default empty cells color
    for (size_t i=0;  i < mTriangles.getVertexCount();  ++i)
        mTriangles[i].color = mNoCellColor;

    // Default mLines color
    for (size_t i=0;  i < mLines.getVertexCount();  ++i)
        mLines[i].color = mLinesColor;

}




////////////////////////////////////////////////////////////////
//  GEOMETRY
////////////////////////////////////////////////////////////////
const sf::FloatRect&        WorldRenderer::
getBounds() const {
    return mBounds;
}



const float&                WorldRenderer::
getCellSize() const {
    return mCellSize;
}




////////////////////////////////////////////////////////////////
//  DRAW LINES SWITCH
////////////////////////////////////////////////////////////////
void        WorldRenderer::
drawLines(bool b) {
    mDoDrawLines = b;
}




////////////////////////////////////////////////////////////////
//  SET COLORS
////////////////////////////////////////////////////////////////
void        WorldRenderer::
noCellColor(const sf::Color& color) {
    mNoCellColor = color;
    this->update();
}


void        WorldRenderer::
aliveCellColor(const sf::Color& color) {
    mAliveCellColor = color;
    this->update();
}


void        WorldRenderer::
visitedCellColor(const sf::Color& color) {
    mVisitedCellColor = color;
    this->update();
}



void        WorldRenderer::
linesColor(const sf::Color& color) {
    for (size_t i=0;  i < mLines.getVertexCount();  ++i)
        mLines[i].color = color;
}





////////////////////////////////////////////////////////////////
//  CELL NUMBER -> POINTER TO VERTEX (FIRST CELL'S VERTEX)
////////////////////////////////////////////////////////////////
sf::Vertex*        WorldRenderer::
getCellPoint(size_t n) {
    return &(mTriangles[n * 6]);
}


const sf::Vertex*        WorldRenderer::
getCellPoint(size_t n) const {
    return this->getCellPoint(n);
}


sf::Vertex*        WorldRenderer::
getCellPointAt(size_t x, size_t y) {
    return &(mTriangles[mWorld.getWidth()  * y + x]);
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
    for ( const Cell& cell : mWorld )
    {
        sf::Vertex* originPoint = this->getCellPoint(i);
        sf::Color color = mNoCellColor;

        if ( cell.isAlive() )
            color = mAliveCellColor;
        else if ( cell.wasVisited() )
            color = mVisitedCellColor;

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
        static_cast<size_t>(std::floor(coords.x / mCellSize)),
        static_cast<size_t>(std::floor(coords.y / mCellSize))
    };
}



size_t                          WorldRenderer::
graphicsCoordsToCellNumber(const sf::Vector2f& coords) const {
    auto c = this->graphicsToDataCoords(coords);
    return mWorld.getWidth() * c.y + c.x;
}

