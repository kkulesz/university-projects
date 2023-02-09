#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SFML/Graphics.hpp>
#include <string>

class Button{
public:
    Button( const std::string texturePath, const sf::Vector2f size, const sf::Vector2f position );
    ~Button();

    //bool setTexture( const std::string texturePath );
    void draw( sf::RenderWindow* window );
    bool isClicked( sf::RenderWindow* window );
    void setColor( sf::Color newColor );

    sf::Vector2f getPosition(){ return position_; }
    sf::Vector2f getSize(){ return size_; }
private:
    sf::Texture* texture_;
    sf::RectangleShape* shape_;
    sf::Vector2f size_;
    sf::Vector2f position_;

};

#endif
