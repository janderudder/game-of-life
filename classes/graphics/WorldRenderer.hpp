#ifndef GRAPHICS_WORLDRENDERER_HPP
#define GRAPHICS_WORLDRENDERER_HPP
#include "data/World.hpp"
#include <SFML/Graphics.hpp>
#include <cstdint>
using std::size_t;

class WorldRenderer
    : public sf::Drawable
{
    World const&        world;
    float               cellSize;
    sf::FloatRect       bounds;
    sf::VertexArray     lines               =   sf::VertexArray(sf::PrimitiveType::Lines);
    sf::VertexArray     triangles           =   sf::VertexArray(sf::PrimitiveType::Triangles);
    bool                drawLines_b         =   true;
    sf::Color           noCell_col          =   sf::Color::Transparent;
    sf::Color           aliveCell_col       =   sf::Color::Black;
    sf::Color           visitedCell_col     =   sf::Color(109, 205, 109);

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
