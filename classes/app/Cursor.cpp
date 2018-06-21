#include "Cursor.hpp"
#include "helpers/sf_Vector_traits.hpp"

void
Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if ( mDrawCrosshair )
        target.draw(this->mCrosshairSprite);
}




Cursor::Cursor(sf::RenderWindow& window) noexcept
    : mWindow   { window }
{
    this->mCrosshairSprite.setOrigin(
        mCrosshairSprite.getLocalBounds().width / 2.f
        , mCrosshairSprite.getLocalBounds().height / 2.f
    );

    this->mCrosshairSprite.scale(.5f, .5f);
}



void
Cursor::setMode(Mode mode)
{
    if ( mode == Mode::Crosshair ) {
        mDrawCrosshair = true;
        mWindow.setMouseCursorGrabbed(true);
        mWindow.setMouseCursorVisible(false);
    }

    else {
        mDrawCrosshair = false;
        mWindow.setMouseCursorGrabbed(false);
        mWindow.setMouseCursorVisible(true);
    }
}



void
Cursor::onWindowResize(const sf::Vector2u& size)
{
    this->mCrosshairSprite.setPosition( static_cast<sf::Vector2f>(size) / 2.f );
}
