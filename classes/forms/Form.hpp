/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef FORM_HPP
#define FORM_HPP
#include <SFML/Graphics.hpp>

class Form
    : public sf::Drawable
    , public sf::Transformable
{
protected:
    bool                    displayed;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;

public:
    explicit Form(bool display = false) noexcept : displayed { display } { }
    virtual ~Form() { }

    void setDisplay(bool b)     { this->displayed = b;      }
    void display()              { this->displayed = true;   }
    void hide()                 { this->displayed = false;  }
    void toggleDisplay()        { this->displayed = ! this->displayed; }

    bool isDisplayed() const    { return this->displayed; }

    virtual const sf::FloatRect  getLocalBounds() const = 0;
    virtual sf::FloatRect        getGlobalBounds() const = 0;

};

#endif // FORM_HPP
