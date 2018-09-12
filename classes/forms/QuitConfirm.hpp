/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef QUITCONFIRM_FORM_HPP
#define QUITCONFIRM_FORM_HPP
#include "forms/Form.hpp"
#include <SFML/Graphics.hpp>
#include "helpers/Resource.hpp"
#include "helpers/sf_Vector_traits.hpp"

class QuitConfirm
    : public Form
{
    sf::RectangleShape          mRect        =   sf::RectangleShape();
    sf::Text                    mText        =   sf::Text();
    const sf::Font&             mFont;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override {
        if ( this->isDisplayed() ) {
            states.transform *= this->getTransform();
            target.draw(mRect, states);
            target.draw(mText, states);
        }
    }

public:
    explicit QuitConfirm(const sf::Font& aFont) noexcept
        : mFont  ( aFont )
    {
        mRect.setOutlineThickness(6.f);
        mRect.setSize(sf::Vector2f(512 - mRect.getOutlineThickness() * 2, 256 - mRect.getOutlineThickness() * 2));
        mRect.setOutlineColor(sf::Color::Black);
        mRect.setFillColor(sf::Color::White);

        this->setOrigin(-mRect.getOutlineThickness(), -mRect.getOutlineThickness());

        mText.setFont(this->mFont);
        mText.setCharacterSize(22);
        mText.setFillColor(sf::Color::Black);
        mText.setString("Press Enter to quit.");

        mText.setOrigin(mText.getLocalBounds().width / 2.f, mText.getLocalBounds().height / 2.f);
        mText.setPosition( mRect.getSize() / 2.f );
    }


    virtual const sf::FloatRect getLocalBounds() const override
    {
        return mRect.getLocalBounds();
    }


    virtual sf::FloatRect getGlobalBounds() const override
    {
        return this->getTransform().transformRect(this->mRect.getLocalBounds());
    }


};

#endif // QUITCONFIRM_FORM_HPP
