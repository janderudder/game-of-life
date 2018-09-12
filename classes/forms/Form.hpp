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
    bool    mIsDisplayed;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;

public:
    explicit Form(bool display = false) noexcept : mIsDisplayed { display } { }
    virtual ~Form() { }

    void setDisplay(bool b)             { mIsDisplayed = b;      }
    void display()                      { mIsDisplayed = true;   }
    void hide()                         { mIsDisplayed = false;  }
    void toggleDisplay()                { mIsDisplayed = !mIsDisplayed; }

    inline bool isDisplayed() const     { return mIsDisplayed; }

    virtual const sf::FloatRect  getLocalBounds() const = 0;
    virtual sf::FloatRect        getGlobalBounds() const = 0;

};

#endif // FORM_HPP
