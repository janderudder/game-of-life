/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef GRAPHICS_WORLDRENDERER_HPP
#define GRAPHICS_WORLDRENDERER_HPP
#include "data/World.hpp"
#include <SFML/Graphics.hpp>
#include <cstdint>
using std::size_t;

class WorldRenderer
    : public sf::Drawable
{
    const World&        mWorld;
    float               mCellSize;
    sf::FloatRect       mBounds;
    sf::VertexArray     mLines              =   sf::VertexArray(sf::PrimitiveType::Lines);
    sf::VertexArray     mTriangles          =   sf::VertexArray(sf::PrimitiveType::Triangles);
    bool                mDoDrawLines        =   true;
    sf::Color           mNoCellColor        =   sf::Color::Transparent;
    sf::Color           mAliveCellColor     =   sf::Color::Black;
    sf::Color           mVisitedCellColor   =   sf::Color(255, 231, 158);
    sf::Color           mLinesColor         =   sf::Color(158, 150, 150);


    virtual void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates::Default) const override;

public:
    explicit WorldRenderer(const World&, float = 32.f);


    // --- Geometry
    const sf::FloatRect& getBounds() const;
    const float& getCellSize() const;


    // --- Draw switch
    void drawLines(bool);


    // --- Colors
    void noCellColor(const sf::Color&);
    void aliveCellColor(const sf::Color&);
    void visitedCellColor(const sf::Color&);
    void linesColor(const sf::Color&);


    // --- Update graphics
    void update();


    // --- 2D world coords to cell
    sf::Vector2<size_t> graphicsToDataCoords(const sf::Vector2f&) const;
    size_t graphicsCoordsToCellNumber(const sf::Vector2f&) const;


    // --- Cell to points
    sf::Vertex* getCellPoint(size_t);
    const sf::Vertex* getCellPoint(size_t) const;

    sf::Vertex* getCellPointAt(size_t, size_t);
    const sf::Vertex* getCellPointAt(size_t, size_t) const;


};

#endif // GRAPHICS_WORLDRENDERER_HPP

