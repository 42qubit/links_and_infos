/*
 * map.cpp
 *
 *  Created on: 04.02.2017
 *      Author: Gregor
 */

#include <iostream>

#include <SFML/Graphics.hpp>

#include "../Clickable/clickable.hpp"
#include "../Polygon/Polygon.hpp"
#include "map.hpp"

using namespace std;
using namespace sf;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

Map::Map(RenderWindow *_pmWindow, Vector2i _pos, Vector2i _size, string _image, Vector2i _viewstart, MapType _type) :

	pmWindow(_pmWindow),

	isMapMoving(false),
	isSpriteMoving(false),
	actualSprite(),

	mouseOldPos(), mouseOldPosOnMap(),
	zoomIndex(0),

	mapGeo(), mapName(), mapPolit(),
	map(),
	mapView(),

	pos(_pos),
	size(_size),
	rootSize(Vector2f(_pmWindow->getSize())),
	imageSize()

{
	mapGeo.loadFromFile(_image); // "geo_karte.gif"
	mapName.loadFromFile("name_karte.gif");
	mapPolit.loadFromFile("polit_karte.gif");
	setMapType(_type);

	mapView.setCenter(Vector2f(_viewstart.x + size.x/2.f, _viewstart.y + size.y/2.f));
	mapView.setSize(sf::Vector2f(size.x, size.y));
	mapView.setViewport(FloatRect( pos.x/rootSize.x, pos.y/rootSize.y, size.x/rootSize.x, size.y/rootSize.y) );
};



void Map::handleEvent(Event _event) {

    Vector2f mouseNewPos = getMousePosOnWindow();
	Vector2f mouseNewPosOnMap = getMousePosOnMap();
    Vector2f difference;

    for(unsigned int i=0; i<sprites.size(); i++) {
    	if(sprites[i].isPointInside(mouseNewPosOnMap))
    		sprites[i].handleEvent(_event);
    }

    for(unsigned int i=0; i<polygons.size(); i++) {
    	if(polygons[i].isPointInside(mouseNewPosOnMap))
    		polygons[i].handleEvent(_event);
    }

	switch(_event.type) {


		case Event::MouseButtonPressed:

			for(unsigned int i=0; i<sprites.size(); i++) {
				if(sprites[i].isPointInside(mouseNewPosOnMap)) {
					isSpriteMoving = true;
					actualSprite = i;
					break;
				}
			}

			if(!isSpriteMoving)
				isMapMoving = true;

			break;


		case Event::MouseButtonReleased:

			isMapMoving = false;
			isSpriteMoving = false;
			break;


		case Event::MouseMoved:

			// Sprite is moving

			if(Mouse::isButtonPressed(Mouse::Button::Left) && isSpriteMoving) {
				difference = mouseOldPosOnMap - mouseNewPosOnMap;

				if(sprites[actualSprite].sprite.getGlobalBounds().left - difference.x < 0)
					difference.x = 0;

				if(sprites[actualSprite].sprite.getGlobalBounds().top - difference.y < 0)
					difference.y = 0;

				if(sprites[actualSprite].sprite.getGlobalBounds().left+sprites[actualSprite].sprite.getGlobalBounds().width - difference.x > imageSize.x)
					difference.x = 0;

				if(sprites[actualSprite].sprite.getGlobalBounds().top+sprites[actualSprite].sprite.getGlobalBounds().height - difference.y > imageSize.y)
					difference.y = 0;

				sprites[actualSprite].move(difference);
			}

			// Map is moving

			else if(Mouse::isButtonPressed(Mouse::Button::Left) && isMapMoving) {

				difference = (mouseOldPos - mouseNewPos) * zoomList[zoomIndex];

				if( mapView.getCenter().x - (size.x/2)*zoomList[zoomIndex] + difference.x < 0  && difference.x < 0)
					difference.x = 0;

				if( mapView.getCenter().y - (size.y/2)*zoomList[zoomIndex] + difference.y < 0  &&  difference.y < 0)
					difference.y = 0;

				if( mapView.getCenter().x + (size.x/2)*zoomList[zoomIndex] + difference.x > imageSize.x  &&  difference.x > 0)
					difference.x = 0;

				if( mapView.getCenter().y + (size.y/2)*zoomList[zoomIndex] + difference.y > imageSize.y  &&  difference.y > 0)
					difference.y = 0;

				mapView.move(difference);
			}

			mouseOldPos = mouseNewPos;
			mouseOldPosOnMap = mouseNewPosOnMap;
			break;


		case Event::MouseWheelScrolled:

			// Map is zoomed

			if(_event.mouseWheelScroll.delta > 0) {
				if(zoomIndex == 7)
					break;
				mapView.zoom(1.f / zoomList[zoomIndex]);
				zoomIndex++;
				mapView.zoom(zoomList[zoomIndex]);
			}

			else if(_event.mouseWheelScroll.delta < 0) {
				if(zoomIndex == 0)
					break;
				mapView.zoom(1.f / zoomList[zoomIndex]);
				zoomIndex--;
				mapView.zoom(zoomList[zoomIndex]);
			}

			break;


		default:
			break;
	}
};



void Map::draw() {
    pmWindow->setView(mapView);
    pmWindow->draw(map);

    for(unsigned int i=0; i<polygons.size(); i++)
    	polygons.at(i).draw();

    for(unsigned int i=0; i<sprites.size(); i++)
    	sprites.at(i).draw();

    pmWindow->setView(pmWindow->getDefaultView());
};



bool Map::isMouseInside() {
	if(Mouse::getPosition(*pmWindow).x >= pos.x &&
	   Mouse::getPosition(*pmWindow).y >= pos.y &&
	   Mouse::getPosition(*pmWindow).x <= (pos+size).x &&
	   Mouse::getPosition(*pmWindow).y <= (pos+size).y)
		return true;
	else
		return false;
};



void Map::setMapType(MapType _type) {

	switch(_type) {
		case GEOGRAPHY:
			map.setTexture(mapGeo); break;
		case NAMES:
			map.setTexture(mapName); break;
		case POLITICS:
			map.setTexture(mapPolit); break;
		default:
			break;
	}

	map.setPosition(0.f, 0.f);
	imageSize = Vector2f(map.getTexture()->getSize());
};



void Map::addSprite(Button sprite) {
	sprites.push_back(sprite);
};



Vector2f Map::getMousePosOnMap() {
	return Vector2f(pmWindow->mapPixelToCoords(Mouse::getPosition(*pmWindow), mapView).x , // / (1178.f/750.f),
					pmWindow->mapPixelToCoords(Mouse::getPosition(*pmWindow), mapView).y ); // / (1178.f/750.f));
};



Vector2f Map::getMousePosOnWindow() {
	return Vector2f(Mouse::getPosition(*pmWindow).x, Mouse::getPosition(*pmWindow).y);
};


