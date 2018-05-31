#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <SFML/Graphics.hpp>

class Camera
{
    sf::View                    view;
    const sf::RenderWindow&     window;
    sf::Vector2f                speed           =   { 350.f, 350.f };
    int                         zoom            =   0;

public:
    explicit Camera(const sf::RenderWindow& w) noexcept
        : view      { w.getDefaultView() }
        , window    { w }
    { }


    const sf::View& getView() const {
        return this->view;
    }

    operator const sf::View&() const {
        return this->view;
    }


    void onWindowResize()
    {
        auto center = window.mapCoordsToPixel(this->view.getCenter(), this->view);

        view.setSize(static_cast<sf::Vector2f>(window.getSize()));

        // Reapply zoom
        if ( this->zoom > 0 ) {
            for (int i=0; i < zoom;  ++i)
                this->view.zoom(.9f);
        }
        else if ( this->zoom < 0 ) {
            for (int i=0; i > zoom; --i)
                this->view.zoom(1.1f);
        }
        
        this->view.setCenter(window.mapPixelToCoords(center, this->view));
    }


    void centerOn(float x, float y) {
        this->view.setCenter(x, y);
    }

    void centerOn(const sf::Vector2f& pos) {
        this->view.setCenter(pos);
    }

    void move(const sf::Vector2f& v) {
        view.move(v);
    }

    void move(float x, float y) {
        view.move(sf::Vector2f(x, y));
    }

    void zoomIn() {
        this->zoom += 1;
        this->view.zoom(.9f);
    }
    
    void zoomOut() {
        this->zoom -= 1;
        this->view.zoom(1.1f);
    }

    void resetZoom() {
        auto center = this->view.getCenter();
        view = this->window.getDefaultView();
        this->view.setCenter(center);
    }

    const sf::Vector2f& getSpeed() const {
        return this->speed;
    }

    void setSpeed(const sf::Vector2f& s) {
        this->speed = s;
    }

};

#endif // CAMERA_HPP
