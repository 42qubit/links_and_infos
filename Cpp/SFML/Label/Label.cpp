/*
 * Label.cpp
 *
 *  Created on: 06.04.2017
 *      Author: Gregor
 */

#include <exception>

#include <SFML/Graphics.hpp>

#include "Label.hpp"

using namespace std;
using namespace sf;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

Label::Label(RenderWindow *_pmWindow, Vector2f _pos, string _message, string _fontPath) :
	pmWindow(_pmWindow),
	font(), text(),
	pos(_pos), size(), padding(Vector2f(5, 5)),
	message(_message)
{
	if(!font.loadFromFile(_fontPath))
		throw invalid_argument("Invalid font-path.");
	text.setFont(font);
	text.setString(message);
	text.setPosition(pos+padding);

	background.setPosition( Vector2f(text.getGlobalBounds().left, text.getGlobalBounds().top) - padding );
	background.setSize( Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height) + padding+padding );
	background.setFillColor(Color::Transparent);
};



void Label::draw() {
	pmWindow->draw(background);
	pmWindow->draw(text);
};



void Label::setMessage(string _message) {
	message = _message;
};

void Label::setForegroundColor(Color _color) {
	text.setFillColor(_color);
};

void Label::setBackgroundColor(Color _color) {
	background.setFillColor(_color);
};



Font *Label::getFont() {
	return &font;
};

Text *Label::getText() {
	return &text;
};

Vector2f Label::getPos() {
	return pos;
};

Vector2f Label::getSize() {
	return size;
};

string Label::getMessage() {
	return message;
};


