#include "Hub.h"
#include <string>
Hub::Hub(State::Context context) : context(context)
{
	FontHolder& fonts = *(context.fonts); 
	fonts.load(Fonts::PixeloidMono, "fonts/PixeloidMono.ttf"); 

	TextureHolder& textures = *(context.textures); 
	textures.load(Textures::Heart, "textures/heart.png"); 

	hpText.setFont(fonts.get(Fonts::PixeloidMono)); 
	hpText.setString("x");
	hpText.setCharacterSize(40);
	hpText.setOrigin(hpText.getLocalBounds().getSize() / 2.f); 
	hpText.setPosition(40, 40);
	hpText.setColor(sf::Color::Black); 

	hpCount.setFont(fonts.get(Fonts::PixeloidMono));
	hpCount.setString(std::to_string(static_cast<int>(0)));
	hpCount.setCharacterSize(40);
	hpCount.setOrigin(hpCount.getLocalBounds().getSize() / 2.f);
	hpCount.setPosition(70, 40);
	hpCount.setColor(sf::Color::Black);

	heart.setTexture(textures.get(Textures::Heart)); 
	//heart.setOrigin(heart.getLocalBounds().getSize() / 2.f); 
	heart.setPosition(110, hpCount.getOrigin().y);

	timeText.setFont(fonts.get(Fonts::PixeloidMono));
	timeText.setString("Time: " );
	timeText.setCharacterSize(40);
	timeText.setOrigin(timeText.getLocalBounds().getSize() / 2.f);
	timeText.setPosition(500, 40);
	timeText.setColor(sf::Color::Black); 

	timeCount.setFont(fonts.get(Fonts::PixeloidMono));
	timeCount.setString(std::to_string(static_cast<int>(0)));
	timeCount.setCharacterSize(40);
	timeCount.setOrigin(timeCount.getLocalBounds().getSize() / 2.f);
	timeCount.setPosition(540, 40);
	timeCount.setColor(sf::Color::Black); 

	pointText.setFont(fonts.get(Fonts::PixeloidMono));
	pointText.setString("Point: ");
	pointText.setCharacterSize(40);
	pointText.setOrigin(pointText.getLocalBounds().getSize() / 2.f);
	pointText.setPosition(840, 40);
	pointText.setColor(sf::Color::Black);

	pointCount.setFont(fonts.get(Fonts::PixeloidMono));
	pointCount.setString(std::to_string(static_cast<int>(0)));
	pointCount.setCharacterSize(40);
	pointCount.setOrigin(pointCount.getLocalBounds().getSize() / 2.f);
	pointCount.setPosition(940, 40);
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
	hpText.setPosition(offset + 40, 40);
	hpCount.setPosition(offset + 70, 40);
	heart.setPosition(offset + 150, hpCount.getOrigin().y);
	
	timeText.setPosition(offset + 500, 40);
	timeCount.setPosition(offset + 560, 40);

	pointText.setPosition(offset + 840, 40); 
	pointCount.setPosition(offset + 940, 40); 
}

void Hub::draw()
{
	sf::RenderWindow& window = *(context.window);
	window.draw(hpText); 
	window.draw(hpCount);
	window.draw(heart);

	window.draw(timeText);
	window.draw(timeCount); 

	window.draw(pointText); 
	window.draw(pointCount); 
	
}


