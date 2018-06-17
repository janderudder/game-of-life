/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef QUITCONFIRM_FORM_HPP
#define QUITCONFIRM_FORM_HPP
#include "forms/Form.hpp"
#include <SFML/Graphics.hpp>
#include "Resource.hpp"
#include "helpers/sf_Vector_traits.hpp"

class QuitConfirm
    : public Form
{
    sf::RectangleShape          rect        =   sf::RectangleShape();
    sf::Text                    text        =   sf::Text();
    Resource<sf::Font>          font;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override {
        if ( this->displayed ) {
            states.transform *= this->getTransform();
            target.draw(this->rect, states);
            target.draw(this->text, states);
        }
    }

public:
    explicit QuitConfirm(const Resource<sf::Font>& fontRes) noexcept
        : font  ( fontRes )
    {
        this->rect.setOutlineThickness(6.f);
        this->rect.setSize(sf::Vector2f(512 - rect.getOutlineThickness() * 2, 256 - rect.getOutlineThickness() * 2));
        this->rect.setOutlineColor(sf::Color::Black);
        this->rect.setFillColor(sf::Color::White);

        this->setOrigin(-rect.getOutlineThickness(), -rect.getOutlineThickness());

        this->text.setFont(*(this->font));
        this->text.setCharacterSize(22);
        this->text.setFillColor(sf::Color::Black);
        this->text.setString("Press Enter to quit.");

        this->text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
        this->text.setPosition( rect.getSize() / 2.f );
    }


    virtual const sf::FloatRect getLocalBounds() const override
    {
        return this->rect.getLocalBounds();
    }


    virtual sf::FloatRect getGlobalBounds() const override
    {
        return this->getTransform().transformRect(this->rect.getLocalBounds());
    }


};

#endif // QUITCONFIRM_FORM_HPP
