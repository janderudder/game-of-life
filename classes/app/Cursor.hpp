/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef CURSOR_HPP
#define CURSOR_HPP
#include <SFML/Graphics.hpp>
#include "helpers/ProjectPath.hpp"
#include "helpers/Resource.hpp"
using Texture = Resource<sf::Texture>;

class Cursor
    : public sf::Drawable
{
    sf::RenderWindow&   mWindow;
    Texture             mCrosshairTexture           =   makeResource<sf::Texture>(ProjectPath::Get("resources/images/crosshair.png"));
    sf::Sprite          mCrosshairSprite            =   sf::Sprite(*this->mCrosshairTexture);
    bool                mDrawCrosshair              =   false;

    virtual void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates::Default) const override;

public:
    enum Mode : char {
        Normal, Crosshair
    };

    explicit Cursor(sf::RenderWindow&) noexcept;

    void setMode(Mode);
    void onWindowResize(const sf::Vector2u&);

    Mode getMode() const                    { return this->mDrawCrosshair ? Mode::Crosshair : Mode::Normal; }

};


#endif // CURSOR_HPP
