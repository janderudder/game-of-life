/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <SFML/Graphics.hpp>

class Camera
{
    sf::View                    mView;
    const sf::RenderWindow&     mWindow;
    sf::Vector2f                mSpeed           =   { 350.f, 350.f };
    int                         mZoom            =   0;

public:
    explicit Camera(const sf::RenderWindow& w) noexcept
        : mView      { w.getDefaultView() }
        , mWindow    { w }
    { }


    const sf::View& getView() const {
        return this->mView;
    }

    operator const sf::View&() const {
        return this->mView;
    }


    void onWindowResize()
    {
        auto center = mWindow.mapCoordsToPixel(this->mView.getCenter(), this->mView);

        mView.setSize(static_cast<sf::Vector2f>(mWindow.getSize()));

        // Reapply mZoom
        if ( this->mZoom > 0 ) {
            for (int i=0; i < mZoom;  ++i)
                this->mView.zoom(.9f);
        }
        else if ( this->mZoom < 0 ) {
            for (int i=0; i > mZoom; --i)
                this->mView.zoom(1.1f);
        }

        this->mView.setCenter(mWindow.mapPixelToCoords(center, this->mView));
    }


    void centerOn(float x, float y) {
        this->mView.setCenter(x, y);
    }

    void centerOn(const sf::Vector2f& pos) {
        this->mView.setCenter(pos);
    }

    void move(const sf::Vector2f& v) {
        mView.move(v);
    }

    void move(float x, float y) {
        mView.move(sf::Vector2f(x, y));
    }

    void zoomIn() {
        this->mZoom += 1;
        this->mView.zoom(.9f);
    }

    void zoomOut() {
        this->mZoom -= 1;
        this->mView.zoom(1.1f);
    }

    void resetZoom() {
        auto center = this->mView.getCenter();
        mView = this->mWindow.getDefaultView();
        this->mView.setCenter(center);
        this->mZoom = 0;
    }

    const sf::Vector2f& getSpeed() const {
        return this->mSpeed;
    }

    void setSpeed(const sf::Vector2f& s) {
        this->mSpeed = s;
    }

};

#endif // CAMERA_HPP
