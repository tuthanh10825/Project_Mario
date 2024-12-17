#include "Hub.h"
#include <string>
Hub::Hub(State::Context context) : context(context), hp(3), time(0)
{
	FontHolder& fonts = *(context.fonts); 
	fonts.load(Fonts::PixeloidMono, "fonts/PixeloidMono.ttf"); 

	TextureHolder& textures = *(context.textures); 
	textures.load(Textures::Heart, "textures/heart.png"); 

	hpText.setFont(fonts.get(Fonts::PixeloidMono)); 
	hpText.setString("x" + std::to_string(hp));
	hpText.setCharacterSize(40);
	hpText.setOrigin(hpText.getLocalBounds().getSize() / 2.f); 
	hpText.setPosition(40, 40);
	hpText.setColor(sf::Color::Black); 

	heart.setTexture(textures.get(Textures::Heart)); 
	//heart.setOrigin(heart.getLocalBounds().getSize() / 2.f); 
	heart.setPosition(hpText.getOrigin().x + hpText.getLocalBounds().getSize().x / 2.f + 5, hpText.getOrigin().y);

	timeText.setFont(fonts.get(Fonts::PixeloidMono));
	timeText.setString("Time: " );
	timeText.setCharacterSize(40);
	timeText.setOrigin(timeText.getLocalBounds().getSize() / 2.f);
	timeText.setPosition(500, 40);
	timeText.setColor(sf::Color::Black); 

	timeCount.setFont(fonts.get(Fonts::PixeloidMono));
	timeCount.setString(std::to_string(static_cast<int>(time)));
	timeCount.setCharacterSize(40);
	timeCount.setOrigin(timeCount.getLocalBounds().getSize() / 2.f);
	timeCount.setPosition(540, 40);
	timeCount.setColor(sf::Color::Black); 
}

void Hub::setHP(int hp)
{
	this->hp = hp; 
	hpText.setString("x" + std::to_string(hp)); 

}

void Hub::update(sf::Time dt)
{
	time += dt.asSeconds(); 
	timeCount.setString(std::to_string(static_cast<int>(time)));
	float offset = (context.window)->getView().getCenter().x - ((context.window)->getView().getSize().x / 2.f); 

	hpText.setPosition(offset + 40, 40);
	heart.setPosition(offset + hpText.getOrigin().x + hpText.getLocalBounds().getSize().x / 2.f + 40, hpText.getOrigin().y);
	timeText.setPosition(offset + 500, 40);
	timeCount.setPosition(offset + 560, 40);
}

void Hub::draw()
{
	sf::RenderWindow& window = *(context.window);
	window.draw(hpText); 
	window.draw(timeText);
	window.draw(heart); 
	window.draw(timeCount); 
}
