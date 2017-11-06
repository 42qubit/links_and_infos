/*
 * clickable.cpp
 *
 *  Created on: 13.03.2017
 *      Author: Gregor
 */

#include <string>

#include <SFML/Graphics.hpp>

#include "clickable.hpp"

using namespace std;
using namespace sf;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

Button::Button(sf::RenderWindow *_pmWindow, Vector2f _pos, Vector2f _size, string _filename, void (*_command) (Event _event, Button *_button)) :
	pmWindow(_pmWindow),
	command(_command),
	pos(_pos), size(_size),
	texture(), sprite()
{
	this->texture.loadFromFile(_filename);
	this->sprite.setTexture(texture);
	this->sprite.setPosition(_pos);
};



void Button::draw() {
	pmWindow->draw(sprite);
};



void Button::handleEvent(sf::Event event) {
	if(event.type == Event::MouseButtonReleased) {
		command(event, this);
	}
};



bool Button::isMouseInside() {
	if(Mouse::getPosition(*pmWindow).x >= pos.x &&
	   Mouse::getPosition(*pmWindow).y >= pos.y &&
	   Mouse::getPosition(*pmWindow).x <= (pos+size).x &&
	   Mouse::getPosition(*pmWindow).y <= (pos+size).y)
		return true;
	else
		return false;
};

bool Button::isPointInside(Vector2f _point) {
	if(sprite.getGlobalBounds().contains(_point))
		return true;
	else
		return false;
};



void Button::move(Vector2f _difference) {
	sprite.move(-_difference);
	pos -= _difference;
};


