#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "fun.h"

const int WIDTH = 1200;
const int HEIGHT = 800;

const int DEFAULT_K = 10;
const int DEFAULT_VELOCITY = 100;
const int DEFAULT_ANGLE = 45;


void printParameters(int K, int V, int alpha){
	std::cout<<"K="<<K<<" V="<<V<<" alpha="<<alpha<<std::endl;
}
void refreshPixels(sf::Uint8* pixelArray, int32_t width, int32_t height){
	int32_t size = 4*width*height;
	while( --size ){
		pixelArray[size] = 0xff; //white
	}
}

void printOptions(){
	std::cout	<<"UP 	- zwiększ V\n"
				<<"DOWN- zmniejsz V\n"
				<<"LEFT- zwiększ kąt\n"
				<<"RIGHT-zmniejsz kąt\n"
				<<"[K]	- zwiększ K\n"
				<<"[J] - zmniejsz K\n"
				<<"ENTER-odśwież obraz\n"
				<<"======================\n";
}

int main( /*int argc, char** argv */){
	printOptions();

	
	int K = DEFAULT_K;
	int V = DEFAULT_VELOCITY;
	int alpha = DEFAULT_ANGLE;

	int32_t width = WIDTH;
	int32_t height = HEIGHT;
	sf::Uint8 *pixelArray = new sf::Uint8[4*width*height];
	refreshPixels(pixelArray, width, height);



	sf::Texture texture;
	texture.create(width, height);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0,0);

	std::string windowTitle = "Bouncing ball";
	sf::RenderWindow window( sf::VideoMode( width, height ), windowTitle, sf::Style::Close | sf::Style::Titlebar);
	
	bool reload = true;

    while(window.isOpen()) {
		if(reload == true){
			/*
				OBLICZAM
			*/
			//std::cout<<V<<std::endl;
			//std::cout<<pixelArray<<std::endl;
			//std::cout<< fun( pixelArray, width, height, K, V, alpha) << std::endl;
			fun( pixelArray, width, height, K, V, alpha);
			/*
				RYSUJE
			*/
			texture.update(pixelArray);
			window.clear(sf::Color::Black);
			window.draw(sprite);
			window.display();


			/*
				WCZYTUJE ŚWIEŻĄ BITMAPE
			*/
			refreshPixels(pixelArray, width, height);
			
			reload = false;
		}
		/*
		CZEKAM NA INPUT UZYTKOWNIKA
		*/
		sf::Event event;
		while( window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window.close();
			}
	
			if( event.key.code == sf::Keyboard::Escape){
				window.close();
			}
			/* PARAMETER K*/
			
			if( event.key.code == sf::Keyboard::K){
				if( K <= 99){
					K += 1;
				}
			}
			if( event.key.code == sf::Keyboard::J){
				if( K >= 1){
					K -= 1;
				}
			}
			/* VELOCITY V*/
			if( event.key.code == sf::Keyboard::Up){
				V += 10;
			}
			if( event.key.code == sf::Keyboard::Down){
				V -= 10;
			}
			/* ANGLE ALPHA*/
			if( event.key.code == sf::Keyboard::Left){
				alpha += 1;
				alpha %=360;
			}
			if( event.key.code == sf::Keyboard::Right){
				alpha -= 1;
				alpha %= 360;
			}
			/* RELOAD*/
			//if( event.key.code == sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
			if( event.key.code == sf::Keyboard::Return){
			
				reload = true;
				printParameters(K, V, alpha);
			}

		}
	}

	

	return 0;

}
