#include <iostream>
#include "gui.h"

#define HEIGHT 768
#define WIDTH 1024

Interface::Interface(){
    window_ = new sf::RenderWindow( sf::VideoMode( WIDTH, HEIGHT ), "title", sf::Style::Close | sf::Style::Titlebar);

    font_.loadFromFile( "src/fonts/SulphurPoint-Regular.otf" );
    stateMessage_.setFont( font_);
    stateMessage_.setPosition( sf::Vector2f(400.0f, 100.0f) );
    stateMessage_.setCharacterSize( 100 );
    stateMessage_.setFillColor( sf::Color(0,0,0) );//BLACK
    updateStateMessage_();

    actionMessage_.setFont( font_ );
    actionMessage_.setPosition( sf::Vector2f( 200.0f, 20.0f) );
    actionMessage_.setCharacterSize( 40 );
    actionMessage_.setFillColor( sf::Color(0,0,0) );//BLACK

    setButtons_();
}

Interface::~Interface(){
    delete carFactoryButton_;
    delete frameFactoryButton_;
    delete engineFactoryButton_;
    delete batteryFactoryButton_;
    delete window_;
}

void Interface::mainLoop(){
    while( window_->isOpen() ){
        sf::Event evnt;

        while( window_->pollEvent(evnt) ){
            switch( evnt.type){

            case sf::Event::KeyPressed:
                if( evnt.key.code == sf::Keyboard::Escape){
                    window_->close();
                }
                break;

            case sf::Event::Closed:
                window_->close();
                break;

            case sf::Event::MouseButtonPressed:
                mousePressedEvents_();
                break;

            case sf::Event::MouseButtonReleased:
                mouseReleasedEvents_();
                break;

            default:
                break;
            }
        }
        window_->clear( sf::Color(150,150,150) );// GREY
        this->drawButtons_();
        this->drawTexts_();
        window_->display();
    }
}

void Interface::setButtons_(){
    float XPosition = 20.0f;
    float YPosition = 20.0f;
    sf::Vector2f buttonSize( 150.0f, 150.0f );
    carFactoryButton_ = new Button( "src/images/car.jpeg", buttonSize, sf::Vector2f( XPosition, YPosition + 0.0f ));
    frameFactoryButton_ = new Button( "src/images/frame.jpg", buttonSize, sf::Vector2f( XPosition, YPosition + 190.0f));
    engineFactoryButton_ = new Button( "src/images/engine.jpeg", buttonSize, sf::Vector2f( XPosition, YPosition + 380.0f));
    batteryFactoryButton_ = new Button( "src/images/battery.jpg", buttonSize, sf::Vector2f( XPosition, YPosition + 570.0f));
}

void Interface::drawButtons_(){
    carFactoryButton_->draw( window_ );
    frameFactoryButton_->draw( window_);
    engineFactoryButton_->draw( window_);
    batteryFactoryButton_->draw( window_);
}

void Interface::drawTexts_(){
    window_->draw( stateMessage_ );
    window_->draw( actionMessage_ );
}

void Interface::mousePressedEvents_(){
    setActionMessage_("");//clears actionMessege_
    checkButtons_();
    updateStateMessage_();
}

void Interface::checkButtons_(){
    if( carFactoryButton_->isClicked( window_ ) ){
        actionOfCarFactoryButton_();
    }
    else if( frameFactoryButton_->isClicked( window_ ) ){
        actionOfFrameFactoryButton_();
    }
    else if( engineFactoryButton_->isClicked( window_ ) ){
        actionOfEngineFactoryButton_();
    }
    else if( batteryFactoryButton_->isClicked( window_ ) ){
        actionOfBatteryFactoryButton_();
    }

}

void Interface::actionOfCarFactoryButton_(){
    if( factoryManager_.produceCar() ){//if every part is available in warehouse
        setActionMessage_( "Car produced" );
        carFactoryButton_->setColor( acceptanceColor_ );
    }else{//if isnt
        setActionMessage_( "Not enough parts to produce a car.");
        carFactoryButton_->setColor( denyColor_ );
    }
}

void Interface::actionOfFrameFactoryButton_(){
    frameFactoryButton_->setColor( acceptanceColor_ );
    factoryManager_.produceFrame();
    setActionMessage_( "Frame produced" );
}

void Interface::actionOfEngineFactoryButton_(){
    engineFactoryButton_->setColor( acceptanceColor_ );
    factoryManager_.produceEngine();
    setActionMessage_( "Engine produced" );
}

void Interface::actionOfBatteryFactoryButton_(){
    batteryFactoryButton_->setColor( acceptanceColor_ );
    factoryManager_.produceBattery();
    setActionMessage_( "Battery produced" );
}

void Interface::mouseReleasedEvents_(){
    //updateStateMessage_();
    resetColors_();
}

void Interface::resetColors_(){
    carFactoryButton_->setColor( sf::Color(255,255,255) ); /*WHITE*/
    frameFactoryButton_->setColor( sf::Color(255,255,255) );
    engineFactoryButton_->setColor( sf::Color(255,255,255) );
    batteryFactoryButton_->setColor( sf::Color(255,255,255) );
}


void Interface::updateStateMessage_(){
    std::string stateString = "Cars: " + std::to_string( factoryManager_.getCarNumber() ) +
                            "\nFrames: " + std::to_string( factoryManager_.getFrameNumber() ) +
                            "\nEngines: " + std::to_string ( factoryManager_.getEngineNumber() ) +
                            "\nBatteries: " + std::to_string ( factoryManager_.getBatteryNumber() );
    stateMessage_.setString( stateString );
}

void Interface::setActionMessage_( std::string newMessage){
    actionMessage_.setString( newMessage );
}
