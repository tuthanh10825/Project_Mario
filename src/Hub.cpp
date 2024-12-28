#include "Hub.h"
#include <string>
Hub::Hub(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts): window(window) 
	, textures(textures)
	, fonts(fonts)
{
	fonts.load(Fonts::PixeloidMono, "fonts/PixeloidMono.ttf"); 

	textures.load(Textures::WoodenBox, "textures/WoodenBoard.png");
	textures.load(Textures::Heart, "textures/heart.png"); 

	woodenBox.setTexture(textures.get(Textures::WoodenBox));
	woodenBox.setPosition(0, 0);


	hpText.setFont(fonts.get(Fonts::PixeloidMono)); 
	hpText.setString("x");
	hpText.setCharacterSize(40);
	hpText.setOrigin(hpText.getLocalBounds().getSize() / 2.f); 
	hpText.setPosition(60, 80);
	hpText.setColor(sf::Color::Black); 

	hpCount.setFont(fonts.get(Fonts::PixeloidMono));
	hpCount.setString(std::to_string(static_cast<int>(0)));
	hpCount.setCharacterSize(40);
	hpCount.setOrigin(hpCount.getLocalBounds().getSize() / 2.f);
	hpCount.setPosition(90, 80);
	hpCount.setColor(sf::Color::Black);

	heart.setTexture(textures.get(Textures::Heart)); 
	//heart.setOrigin(heart.getLocalBounds().getSize() / 2.f); 
	heart.setPosition(120, 75);

	timeText.setFont(fonts.get(Fonts::PixeloidMono));
	timeText.setString("Time: " );
	timeText.setCharacterSize(40);
	timeText.setOrigin(timeText.getLocalBounds().getSize() / 2.f);
	timeText.setPosition(500, 80);
	timeText.setColor(sf::Color::Black); 

	timeCount.setFont(fonts.get(Fonts::PixeloidMono));
	timeCount.setString(std::to_string(static_cast<int>(0)));
	timeCount.setCharacterSize(40);
	timeCount.setOrigin(timeCount.getLocalBounds().getSize() / 2.f);
	timeCount.setPosition(540, 80);
	timeCount.setColor(sf::Color::Black); 

	pointText.setFont(fonts.get(Fonts::PixeloidMono));
	pointText.setString("Point: ");
	pointText.setCharacterSize(40);
	pointText.setOrigin(pointText.getLocalBounds().getSize() / 2.f);
	pointText.setPosition(800, 80);
	pointText.setColor(sf::Color::Black);

	pointCount.setFont(fonts.get(Fonts::PixeloidMono));
	pointCount.setString(std::to_string(static_cast<int>(0)));
	pointCount.setCharacterSize(40);
	pointCount.setOrigin(pointCount.getLocalBounds().getSize() / 2.f);
	pointCount.setPosition(900, 80);
	pointCount.setColor(sf::Color::Black);

}

void Hub::setHP(int hp)
{
	hpCount.setString(std::to_string(static_cast<int>(hp)));
}

void Hub::setTime(float time)
{
	timeCount.setString(std::to_string(static_cast<int>(time)));
}

void Hub::setPoint(int point)
{
	pointCount.setString(std::to_string(static_cast<int>(point)));
}

void Hub::updateView(const sf::View& worldView)
{
	float offset = worldView.getCenter().x - (worldView.getSize().x / 2.f);
	woodenBox.setPosition(offset, 0);
	hpText.setPosition(offset + 60, 80);
	hpCount.setPosition(offset + 90, 80);
	heart.setPosition(offset + 120, 75);
	
	timeText.setPosition(offset + 500, 80);
	timeCount.setPosition(offset + 560, 80);

	pointText.setPosition(offset + 800, 80); 
	pointCount.setPosition(offset + 900, 80); 
}

void Hub::draw()
{
	window.draw(woodenBox);

	window.draw(hpText); 
	window.draw(hpCount);
	window.draw(heart);

	window.draw(timeText);
	window.draw(timeCount); 

	window.draw(pointText); 
	window.draw(pointCount); 
	
}


