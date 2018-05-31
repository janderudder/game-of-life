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
