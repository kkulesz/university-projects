#include "button.h"

Button::Button( const std::string texturePath, const sf::Vector2f size, sf::Vector2f position ):
        size_(size), position_(position)
{
    shape_ = new sf::RectangleShape( size );
    shape_->setPosition( position );
    texture_ = new sf::Texture;
    texture_->loadFromFile( texturePath );
    shape_->setTexture( texture_ );
    shape_->setOutlineThickness(-5);
    shape_->setOutlineColor( sf::Color::Black );
}

Button::~Button(){
    delete texture_;
    delete shape_;
}

void Button::draw( sf::RenderWindow* window){
    window->draw( *shape_ );
}

bool Button::isClicked( sf::RenderWindow* window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition( *window );
    //returns true if mouse is between corners of the shape
    return ( mousePosition.x > position_.x ) && ( mousePosition.x < position_.x + size_.x ) &&
            (  mousePosition.y > position_.y ) && ( mousePosition.y < position_.y + size_.y );
}

void Button::setColor( sf::Color newColor ){
    shape_->setFillColor( newColor );
}
