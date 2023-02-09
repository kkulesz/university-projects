#ifndef _GUI_H_
#define _GUI_H_

#include "factory_manager.h"
#include "button.h"

class Interface{
public:
    void mainLoop();
    Interface();
    ~Interface();
private:
    sf::RenderWindow* window_;
    sf::Font font_;

    /* colors of buttons */
    sf::Color acceptanceColor_ = sf::Color::Green;
    sf::Color denyColor_ = sf::Color::Red;

    FactoryManager factoryManager_;

    Button* carFactoryButton_;
    Button* frameFactoryButton_;
    Button* engineFactoryButton_;
    Button* batteryFactoryButton_;

    sf::Text stateMessage_;
    sf::Text actionMessage_;

    void drawButtons_();
    /* draws stateMessege_ and actionMessege_ */
    void drawTexts_();
    /* attaches textures and locates buttons */
    void setButtons_();
    /* calls all MousePressed events*/
    void mousePressedEvents_();
    /* chooses specyfic function depending on which button has been pressed */
    void checkButtons_();
    /* calls all MouseReleased enevts*/
    void mouseReleasedEvents_();
    /* resets all buttons fill color to white*/
    void resetColors_();
    /* updates stateMessege_ which prints state of the Warehouse*/
    void updateStateMessage_();

    void setActionMessage_( std::string newMessege );

    void actionOfCarFactoryButton_();
    void actionOfFrameFactoryButton_();
    void actionOfEngineFactoryButton_();
    void actionOfBatteryFactoryButton_();


};


#endif
