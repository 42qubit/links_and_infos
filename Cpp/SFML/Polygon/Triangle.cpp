/*
 * Triangle.cpp
 *
 *  Created on: 29.03.2017
 *      Author: Gregor
 */

#include "SFML/Graphics.hpp"

#include "Triangle.hpp"

using namespace sf;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

Triangle::Triangle() :
	pmWindow(),
	color()
{};



void Triangle::init(RenderWindow *_pmWindow, Vector2f _points[], Color _color) {

	this->pmWindow = _pmWindow;

	for(int i=0; i<3; i++)
		this->points[i] = Vector2f(_points[i].x, _points[i].y);
	this->color = _color;
};



Vector2f Triangle::getPoint(int _index) {

	if(_index>=0 && _index<3)
		return Vector2f(points[_index].x, points[_index].y);
	else
		throw "Wrong Index";
};



void Triangle::draw() {

	VertexArray a(Triangles, 3);

	for(int i=0; i<3; i++) {
		a[i].position = points[i];
		a[i].color = color;
	}

	pmWindow->draw(a);
};


